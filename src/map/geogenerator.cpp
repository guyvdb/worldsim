#include "geogenerator.h"

#include <array>
#include <limits>


#include <numbers/poisson.h>
#include <numbers/simplexnoise.h>
//#include <numbers/round.h>

#include "renderer.h"
#include "heatmaprenderer.h"


namespace map {


  GeoGenerator::~GeoGenerator() {
  }


  std::vector<double> GeoGenerator::SamplePoints() {
    // create a sampling of points from blue noise
    auto kxMin = std::array<double,2>{{0,0}};
    auto kxMax = std::array<double,2>{{this->m_config.Bounds.Width,this->m_config.Bounds.Height}};
    const auto samples = num::PoissonDiskSampling(this->m_config.SeedPointMaxRadius, kxMin, kxMax);

    // convert the samples into a vector x0,y0,x1,y1,x2......
    std::vector<double> points;
    points.reserve(samples.size() * 2);
    for(auto &v : samples) {
      points.push_back(v[0]);
      points.push_back(v[1]);
    }
    return points;
  }


  XYPoint *GeoGenerator::FindOrCreatePoint(double x, double y) {
    if(this->m_pointIndex.Exists(x,y)) {
      return this->m_pointIndex.Get(x,y);
    }

    XYPoint *p = new XYPoint(x,y);
    this->m_map.Add(p);
    this->m_pointIndex.Put(x,y,p);
    return p;
  }

  Center* GeoGenerator::FindOrCreateCenter(double x, double y) {
    // alread exists
    if(this->m_centerIndex.Exists(x,y)) {
      return this->m_centerIndex.Get(x,y);
    }

    // create a new one
    Center *c = new Center(this->FindOrCreatePoint(x,y));
    this->m_map.Add(c);
    this->m_centerIndex.Put(c->P->Location.X, c->P->Location.Y, c);
    return c;
  }


  Edge * GeoGenerator::CreateEdge(double ax, double ay, double bx, double by) {
    Center* c0 =  FindOrCreateCenter(ax, ay);
    Center* c1 = FindOrCreateCenter(bx, by);
    Edge* e = new Edge(c0, c1, 0x0, 0x0);
    this->m_map.Add(e);
    return e;
  }

  void GeoGenerator::IndexPoints(std::vector<double> &points) {
    long id = 0;
    for(std::size_t i =0; i < points.size(); i+= 2) {
      XYPoint *p = new XYPoint(points[i], points[i+1]);
      p->Id = id;
      id++;
      this->m_pointIndex.Put(points[i], points[i+1], p);
    }
  }

  void GeoGenerator::CreateGraph(delaunator::Delaunator& d) {


    for(std::size_t i=0; i<d.triangles.size(); i+=3) {
      double ax, ay, bx, by, cx, cy;
      ax = d.coords[2 * d.triangles[i]];
      ay = d.coords[2 * d.triangles[i] + 1];

      bx = d.coords[2 * d.triangles[i + 1]];
      by = d.coords[2 * d.triangles[i + 1] + 1];

      cx = d.coords[2 * d.triangles[i + 2]];
      cy = d.coords[2 * d.triangles[i + 2] + 1];

      //if(this->ValidTriangle(ax,ay,bx, by, cx,cy)) {
        Edge *e1 = this->CreateEdge(ax, ay, bx, by);
        Edge *e2 = this->CreateEdge(bx, by, cx, cy);
        Edge *e3 = this->CreateEdge(cx, cy, ax, ay);

        this->m_map.Add(e1);
        this->m_map.Add(e2);
        this->m_map.Add(e3);

      //} else {

      //}

    }
  }

  void GeoGenerator::Generate(std::string filename, long seed) {
    //Delaunay Triangulation
    std::cout << "Create points";
    std::vector<double> points = this->SamplePoints();
    delaunator::Delaunator d(points);
    std::cout << " complete" << std::endl;

//    std::cout << "Index points";
//    this->IndexPoints(points);
//    std::cout << " complete" << std::endl;

    // Create the graph
    std::cout << "Create graph";
    this->CreateGraph(d);
    std::cout << " complete" << std::endl;

    std::cout << "Render";
    Renderer r;
    r.Render(filename,this->m_config.Bounds, &this->m_map);
    std::cout << " complete" << std::endl;
  }

}


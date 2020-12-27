#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <numbers/vector.h>



namespace map {
  class Edge;
  class Corner;


  class XYPoint {
    public:
      XYPoint(double x, double y) : Location(num::Vector(x,y)) {}
      XYPoint(num::Vector pos) : Location(pos) {}
      num::Vector Location;
      long Id;
  };


  /*

  public class Center {
      public var index:int;

      public var point:Point;  // location
      public var water:Boolean;  // lake or ocean
      public var ocean:Boolean;  // ocean
      public var coast:Boolean;  // land polygon touching an ocean
      public var border:Boolean;  // at the edge of the map
      public var biome:String;  // biome type (see article)
      public var elevation:Number;  // 0.0-1.0
      public var moisture:Number;  // 0.0-1.0

      public var neighbors:Vector.<Center>;
      public var borders:Vector.<Edge>;
      public var corners:Vector.<Corner>;
    };
    */

  class Center {
    public:
      Center(XYPoint *p) : P(p) {}
      XYPoint *P;
      std::vector<Center*> Neighbors;
      std::vector<Edge*> Borders;
      std::vector<Corner*> Corners;
  };



  /*

  package graph {
    import flash.geom.Point;

    public class Corner {
      public var index:int;

      public var point:Point;  // location
      public var ocean:Boolean;  // ocean
      public var water:Boolean;  // lake or ocean
      public var coast:Boolean;  // touches ocean and land polygons
      public var border:Boolean;  // at the edge of the map
      public var elevation:Number;  // 0.0-1.0
      public var moisture:Number;  // 0.0-1.0

      public var touches:Vector.<Center>;
      public var protrudes:Vector.<Edge>;
      public var adjacent:Vector.<Corner>;

      public var river:int;  // 0 if no river, or volume of water in river
      public var downslope:Corner;  // pointer to adjacent corner most downhill
      public var watershed:Corner;  // pointer to coastal corner, or null
      public var watershed_size:int;
    };
  }

  */

  class Corner {
    public:
      Corner();
      int Index;

      num::Vector Point;


      std::vector<Center*> Touches;
      std::vector<Edge*> Protrudes;
      std::vector<Corner*>Adjacent;

  };



  /*
  package graph {
    import flash.geom.Point;

    public class Edge {
      public var index:int;
      public var d0:Center, d1:Center;  // Delaunay edge
      public var v0:Corner, v1:Corner;  // Voronoi edge
      public var midpoint:Point;  // halfway between v0,v1
      public var river:int;  // volume of water, or 0
    };
  }

    */
  class Edge {
    public:
      Edge(Center *d0, Center *d1, Corner *v0, Corner *v1);

      int Index;
      // Delaunay edges
      Center* D0;
      Center* D1;

      // Voronoi edges
      Corner* V0;
      Corner* V1;

      num::Vector Midpoint; // midpoint of v0, v1

  };

}
#endif // GEOMETRY_H





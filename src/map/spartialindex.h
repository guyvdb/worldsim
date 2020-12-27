#ifndef POINTINDEX_H
#define POINTINDEX_H

#include <iostream>
#include <map>
#include <numbers/vector.h>


namespace map {

  template <class T>
  class SpartialIndex {
    public:
      bool Exists(double x, double y) {
        std::array<double,2> key{x,y};
        return this->m_index.find(key) != this->m_index.end();
      }

      void Put(double x, double y, T t) {
        std::array<double,2> key{x,y};
        this->m_index[key] = t;
      }

      T Get(double x, double y) {
        std::array<double,2> key{x,y};
        return this->m_index[key];
      }
    private:
      std::map<std::array<double,2>, T> m_index;
  };



/*
  template <class T>
  class YIndex {
    public:
      bool Has(double y) {
        return this->m_yIndex.find(y) != this->m_yIndex.end();
      }

      T Get(double y) {
        return this->m_yIndex[y];
      }

      void Put(double y, T t) {
        std::cout << "YIndex: put value at " << y << std::endl;

        std::cout << "existing value: " << (this->m_yIndex.find(y) == this->m_yIndex.end()) << std::endl;

        this->m_yIndex[y] = t;
      }
    private:
      std::map<double, T> m_yIndex;
  };
  */

/*
  template <class T>
  class PointIndex{
    public:
      ~PointIndex() {
        for(auto& p : this->m_xIndex) {
          delete p.second;
        }
      }

      bool Has(num::Vector p) {
        return  this->Has(p.X, p.Y);
      }

      bool Has(double x, double y) {
        if(!this->HasYIndex(x)) {
          return false;
        }
        YIndex<T> *idx = this->GetYIndex(x);
        return idx->Has(y);
      }

      T Get(num::Vector p) {
        return this->Get(p.X, p.Y);
      }

      T Get(double x, double y) {
        YIndex<T> *idx = this->m_xIndex[x];
        return idx->Get(y);
      }

      void Put(num::Vector p, T t) {
        this->Put(p.X, p.Y, t);
      }

      void Put(double x, double y, T t) {
        YIndex<T>* idx;

        std::cout << "put value at x,y: " << x << "," << y;


        if(!this->HasYIndex(y)) {
          std::cout << " - no y index. creating it." << std::endl;
          idx = new YIndex<T>();
          this->m_xIndex[x] = idx;
        } else {
          std::cout << " - using exiting y index." << std::endl;
          idx = this->m_xIndex[x];
        }
        idx->Put(y, t);
      }

    private:
      bool HasYIndex(double x) {
        return this->m_xIndex.find(x) != this->m_xIndex.end();
      }

      YIndex<T>* GetYIndex(double x) {
        return this->m_xIndex[x];
      }

      std::map<double, YIndex<T>*> m_xIndex;


  };
  */

}

#endif // POINTINDEX_H

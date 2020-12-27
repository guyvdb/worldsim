#include "map.h"
#include <iostream>


namespace map {

  Map::Map(){
  }

  Map::~Map() {

    std::cout << "Free edges";
    for(auto& e : this->Edges) {
      delete e;
    }
    std::cout << " complete" << std::endl;

    std::cout << "Free centers";
    for(auto& c : this->Centers) {
      delete c;
    }
    std::cout << " complete" << std::endl;

    std::cout << "Free corners";
    for(auto& c : this->Corners) {
      delete c;
    }
    std::cout << " complete" << std::endl;

    std::cout << "Free points";
    for(auto& p : this->Points) {
      delete p;
    }
    std::cout << " complete" << std::endl;

  }
}


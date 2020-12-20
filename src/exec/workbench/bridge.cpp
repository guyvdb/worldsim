#include "bridge.h"
#include <iostream>


Bridge::Bridge(QObject *parent) : QObject(parent)/*, m_planetGenerator(0x0)*/ {

}


void Bridge::hello() {
  std::cout << "Bridge: hello" << std::endl;
}

void Bridge::render() {
  std::cout << "Bridge: render image" << std::endl;
}

void Bridge::buildMap(){
//  if(this->m_planetGenerator != 0x0) {
//    delete this->m_planetGenerator;
//  }


  //this->m_planetGenerator = new map::PlanetGenerator(config);
}

bool Bridge::haveMap() {
  //return this->m_planetGenerator != 0x0;
}

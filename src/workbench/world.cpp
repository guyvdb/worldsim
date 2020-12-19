#include "world.h"
#include <iostream>


World::World(QObject *parent) : QObject(parent) {

}


void World::hello() {
  std::cout << "Hello from World" << std::endl;
}

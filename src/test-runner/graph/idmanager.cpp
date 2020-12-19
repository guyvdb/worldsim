#include <catch2.hpp>
#include <filesystem>
#include <iostream>

#include <cstdio>

#include <utils.h>
#include <graph/store/store.h>
#include <graph/storeable.h>
#include <graph/id/idmanager.h>
#include <graph/entity.h>
//#include <entityencoder.h>
#include <graph/type/base.h>

TEST_CASE("Check Byte Order","[bytes]") {

  // what is 1 as a 4 byte array of char
  char buf[4];
  std::uint32_t data = 1;

  // 32 bit
  buf[0] = (char)(data >> 24);
  buf[1] = (char)(data >> 16);
  buf[2] = (char)(data >> 8);
  buf[3] = (char)(data);

  std::printf("uint32_t = 1 -> 0x%X 0x%X 0x%X 0x%X\n", (int)buf[0],(int)buf[1],(int)buf[2],(int)buf[3]);

  // 16 bit
  buf[0] = (char)(data >>8);
  buf[1] = (char)(data);

  std::printf("uint16_t = 1 -> 0x%X 0x%X\n", (int)buf[0],(int)buf[1]);


  buf[0] = 0x0;
  buf[1] = 0x0;
  buf[2] = 0x0;
  buf[3] = 0xD;

  data = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3];
  std::printf("0x0 0x0 0x0 0xD = %d\n", data);


}

TEST_CASE("The id manager should recycle id's","[graph][id-manager]") {

  RemoveTestDirectory();

  // Params to open manager
  std::filesystem::path datadir(CreateTestDirectory());

  // Params to open store
  std::size_t pagesize = 1024;
  std::size_t recordsize = 16;
  std::filesystem::path filename = CreateFilePath("entity.db");


  // Create & open store
  graph::store::Store *store = new graph::store::Store(filename.c_str(), pagesize, recordsize, graph::Storeable::Concept::EntityConcept);
  REQUIRE(store->Open());

  // Create and open the manager
  graph::id::IdManager *manager = new graph::id::IdManager(datadir);
  manager->Register(store, graph::Storeable::Concept::EntityConcept);
  REQUIRE(manager->Open());

  // The entity store is empty and there was no data file so
  // the id manager should have done a store scan and set next id to 1
  graph::type::gid id = manager->NextGraphId(graph::Storeable::Concept::EntityConcept);
  REQUIRE(id == 1);

  // call next id 10 times
  for(int i=0;i<10;i++) {
    manager->NextGraphId(graph::Storeable::Concept::EntityConcept);
  }
  // the next id should now be 12
  id = manager->NextGraphId(graph::Storeable::Concept::EntityConcept);
  REQUIRE(id == 12);

  // close the manager this will store the data file
  manager->Close();


// What should the data file look like now?
//      *   <header><index><data>
//      *   <header> = <magic(2)><type-count(2)>
//      *   <index>=<index-item>,<index-item>...type-count items
//      *   <index-item>=<type-id(1)><counter(4)><id-count(2)><file-offset(4)>
//      *   <data>=<data-item>,<data-item>,...id-count items
//      *   <data-item>=<id(4)>
//  
//    MAGIC               WRITE: start tell=0, data=0xA 0xB , size=2, end tell=2
//    TYPE COUNT          WRITE: start tell=2, data=0x0 0x1 , size=2, end tell=4
//    TYPE ID             WRITE: start tell=4, data=0x1 , size=1, end tell=5
//    COUNTER             WRITE: start tell=5, data=0x0 0x0 0x0 0xD , size=4, end tell=9
//    ID COUNT            WRITE: start tell=9, data=0x0 0x0 , size=2, end tell=11
//    OFFSET (FAKE)       WRITE: start tell=11, data=0xFF 0xFF 0xFF 0xFF , size=4, end tell=15
//    OFFSET (REAL)       WRITE: start tell=11, data=0x0 0x0 0x0 0xF , size=4, end tell=15
//
//  ┌────────┬─────────────────────────┬─────────────────────────┬────────┬────────┐
//  │00000000│ 0a 0b 00 01 01 00 00 00 ┊ 0d 00 00 00 00 00 0f    │_•0••000┊_00000• │
//  └────────┴─────────────────────────┴─────────────────────────┴────────┴────────┘



  //  // closing the manager should save its state
  //

    // If we open the manager again it should read its state from its
    // data file. If we then call next id we should get 13
    delete  manager;
    manager = new graph::id::IdManager(datadir);
    manager->Register(store, graph::Storeable::Concept::EntityConcept);

    REQUIRE(manager->Open());

    id = manager->NextGraphId(graph::Storeable::Concept::EntityConcept);
    REQUIRE(id == 13); // lucky 13


    manager->Close();



  // close the store
  store->Close();

  delete manager;
  delete store;
}

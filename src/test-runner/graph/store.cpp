#include <catch2.hpp>
#include <utils.h>
#include <store/store.h>
#include <filesystem>
#include <entity.h>
//#include <entityencoder.h>
#include <storeable.h>


TEST_CASE("The store should store and retreive pages","[graph][store]") {
}

/*TEST_CASE("The store should store and retreive records","[graph][store]") {

  RemoveTestDirectory();

  std::size_t pagesize = 1024;
  std::size_t recordsize = 16;
  std::filesystem::path filename = CreateFilePath("entity.db");


  graph::Encoder *factory = new graph::EntityEncoder();

  graph::Store *store = new graph::Store(filename.c_str(), pagesize, recordsize, factory, graph::Storeable::Concept::CEntity);

  REQUIRE(store->Open());

  graph::Entity *t = new graph::Entity(1);
  t->SetFlag(0x0);
  t->SetRootOutRelId(RandomGraphId());
  t->SetRootAttributesBucketId(RandomGraphId());

  REQUIRE(store->WriteRecord(t));


  store->Close();

  delete t;
  delete store;

}*/

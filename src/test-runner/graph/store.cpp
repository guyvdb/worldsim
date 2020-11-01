#include <catch2.hpp>
#include <utils.h>
#include <store.h>
#include <filesystem>
#include <entity.h>
#include <storeable.h>


TEST_CASE("The store should store and retreive pages","[graph][store]") {
}

TEST_CASE("The store should store and retreive records","[graph][store]") {

  RemoveTestDirectory();

  std::size_t pagesize = 1024;
  std::size_t recordsize = 16;
  std::filesystem::path filename = CreateFilePath("entity.db");


  graph::ObjectFactory *factory = new graph::EntityFactory();

  graph::Store *store = new graph::Store(filename.c_str(), pagesize, recordsize, factory);

  REQUIRE(store->Open());

  graph::Entity *t = new graph::Entity(1);
  t->SetFlag(0x0);
  t->SetInRelId(RandomGraphId());
  t->SetOutRelId(RandomGraphId());
  t->SetPropId(RandomGraphId());

  REQUIRE(store->WriteRecord(t));





  store->Close();

  delete t;
  delete store;

}

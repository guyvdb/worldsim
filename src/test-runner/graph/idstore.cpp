#include <catch2.hpp>
#include <utils.h>
#include <store.h>
#include <filesystem>
#include <iostream>


TEST_CASE("The id store should initialise when empty","[graph][store]") {

  std::size_t pagesize = 1024;
  std::size_t recordsize = 16;
  std::filesystem::path filename = CreateFilePath("id.db");



  INFO("[ID STORE] Filename: " + filename.native());
  graph::IdStore *store = new graph::IdStore(filename,pagesize,recordsize);

  INFO("[ID STORE] Will Open");
  REQUIRE(store->Open());
  INFO("[ID STORE] Is Open");
  INFO("[ID STORE] Will Close");
  store->Close();
  INFO("[ID STORE] Is Closed");
  delete store;

}

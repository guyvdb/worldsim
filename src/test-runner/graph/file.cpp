#include <catch2.hpp>
#include <filesystem>
#include <iostream>


#include <utils.h>
#include <file.h>



TEST_CASE("Should open a file, creating it if needed","[graph][file]") {
  std::filesystem::path fn(CreateTestDirectory());
  fn /= "file.dat";
  graph::File *f = new graph::File(fn);

  REQUIRE(f->Open());
  f->Close();
  delete f;

}

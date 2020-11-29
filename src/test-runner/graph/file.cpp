#include <catch2.hpp>
#include <filesystem>
#include <iostream>
#include <cstdint>

#include <utils.h>
#include <file.h>

graph::File* CreateTestFile() {
  RemoveTestDirectory();
  std::filesystem::path fn(CreateTestDirectory());
  fn /= "file.dat";
  graph::File *f = new graph::File(fn);
  return f;
}

TEST_CASE("Should open a file, creating it if needed","[graph][file]") {
  graph::File *f = CreateTestFile();
  REQUIRE(f != 0x0);

  REQUIRE(f->Open());
  f->Close();
  delete f;

}


TEST_CASE("Should read/write uint values", "[graph][file]") {
  graph::File *f = CreateTestFile();
  REQUIRE(f != 0x0);
  REQUIRE(f->Open());


  // write values to the file
  std::uint8_t uint8v, uint8r;
  std::uint16_t uint16v, uint16r;
  std::uint32_t uint32v, uint32r;
  std::uint64_t uint64v, uint64r;


  uint8v =  134;
  uint16v = 63789;
  uint32v = 0xFFAABBCC;
  uint64v = 0xAABBCCDDEEFF1122;

  // total of 8+16+32+64 bits = 120 bits / 8 = 15 bytes
  REQUIRE(f->Write(uint8v));
  REQUIRE(f->Write(uint16v));
  REQUIRE(f->Write(uint32v));
  REQUIRE(f->Write(uint64v));

  REQUIRE(f->Size() == 15);

  REQUIRE(f->Seek(0));

  REQUIRE(f->Read(&uint8r));
  REQUIRE(f->Read(&uint16r));
  REQUIRE(f->Read(&uint32r));
  REQUIRE(f->Read(&uint64r));

  REQUIRE(uint8v == uint8r);
  REQUIRE(uint16v == uint16r);
  REQUIRE(uint32v == uint32r);
  REQUIRE(uint64v == uint64r);


  f->Close();
  delete f;
}

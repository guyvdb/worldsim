#include <catch2.hpp>
#include <filesystem>
#include <iostream>
#include <cstdint>
#include <vector>
#include <utils.h>
#include <file.h>

graph::File* CreateTestFile() {
  RemoveTestDirectory();
  std::filesystem::path fn(CreateTestDirectory());
  fn /= "file.dat";
  graph::File *f = new graph::File(fn);
  return f;
}

graph::ExtendedFile* CreateTestExtendedFile() {
  RemoveTestDirectory();
  std::filesystem::path fn(CreateTestDirectory());
  fn /= "file.dat";
  graph::ExtendedFile *f = new graph::ExtendedFile(fn);
  return f;
}

TEST_CASE("File should open a file, creating it if needed","[graph][file]") {
  graph::File *f = CreateTestFile();
  REQUIRE(f != 0x0);

  REQUIRE(f->Open());
  f->Close();
  delete f;
}

TEST_CASE("File should read/write uint values", "[graph][file]") {
  graph::ExtendedFile *f = CreateTestExtendedFile();
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
  REQUIRE(f->WriteInt(uint8v));
  REQUIRE(f->WriteInt(uint16v));
  REQUIRE(f->WriteInt(uint32v));
  REQUIRE(f->WriteInt(uint64v));

  REQUIRE(f->Size() == 15);

  REQUIRE(f->Seek(0));

  REQUIRE(f->ReadInt(&uint8r));
  REQUIRE(f->ReadInt(&uint16r));
  REQUIRE(f->ReadInt(&uint32r));
  REQUIRE(f->ReadInt(&uint64r));

  REQUIRE(uint8v == uint8r);
  REQUIRE(uint16v == uint16r);
  REQUIRE(uint32v == uint32r);
  REQUIRE(uint64v == uint64r);


  f->Close();
  delete f;
}


TEST_CASE("File should grow when read/written past EOF","[graph][file][file-grow]") {
  graph::File *f = CreateTestFile();
  REQUIRE(f != 0x0);
  REQUIRE(f->Open());


  // see to position 64 (2 pages) and read a third page
  std::vector<std::uint8_t> buf;
  buf.reserve(32);
  std::fill(buf.begin(), buf.end(), 0x0);

  std::cout << "file pos = " << f->Tell() << std::endl;

  REQUIRE(f->Read(64,buf.data(),32));

  std::cout << "file pos = " << f->Tell() << std::endl;



  f->Close();
  delete f;
}

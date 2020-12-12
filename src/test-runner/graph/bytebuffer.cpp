#include <catch2.hpp>
#include <buffer.h>
#include <type/base.h>
#include <iostream>


TEST_CASE("ByteBuffer should encode/decode values", "[graph][buffer]") {

  std::uint8_t i8 = 132;                    // 0
  std::uint16_t i16 = 32878;                // 1 2
  std::uint32_t i32 = 984838222;            // 3 4 5 6
  //std::uint64_t i64 = 948484838232432;      // 7 8 9 10 11 12 13 14

  graph::ByteBuffer *b = new graph::ByteBuffer(15);
  b->Set(0,i8);
  b->Set(1,i16);
  b->Set(3,i32);
  //b->Set(7,i64);

  REQUIRE(b->GetUint8(0) == i8);
  REQUIRE(b->GetUint16(1) == i16);
  REQUIRE(b->GetUint32(3) == i32);
 // REQUIRE(b->GetUint64(7) == i64);

  delete b;

}


/*
TEST_CASE("The byte buffer should encode/decode values", "[graph][bytebuffer]") {

  graph::ByteBuffer *b = new graph::ByteBuffer();

  graph::gid to = 115781;
  graph::gid from = 25874254;

  graph::tid totype = 35899;


  b->Push(to)->Push(from)->Push(totype);


  graph::tid totype_r = b->PopUInt16();
  graph::gid from_r = b->PopUInt32();
  graph::gid to_r = b->PopUInt32();

  REQUIRE(to == to_r);
  REQUIRE(from == from_r);
  REQUIRE(totype == totype_r);


  delete b;
}


TEST_CASE("The byte buffer should create a stream of bytes and decode them", "[graph][bytebuffer]") {

  uint8_t flag = 0x1;
  uint32_t prop = 0x0A0B0C0D;
  uint32_t inrel = 0x01020304;
  uint32_t outrel = 0x02040608;

  std::vector<char> expected {0x1,0x0A,0x0B,0x0C,0x0D,0x01,0x02,0x03,0x04,0x02,0x04,0x06,0x08};

  SECTION("Create stream of bytes") {
    graph::ByteBuffer *b = new graph::ByteBuffer();
    b->Push(flag)->Push(prop)->Push(inrel)->Push(outrel);

    char *ptr = b->Data();
    for(auto e : expected) {
      REQUIRE(e == *ptr);
      ptr++;
    }
    delete b;
  }

  SECTION("Decode stream of bytes") {
    std::size_t len = (std::size_t)expected.size();
    graph::ByteBuffer *b = new graph::ByteBuffer(expected.data(), len);

    uint32_t outrel_r = b->PopUInt32();
    uint32_t inrel_r = b->PopUInt32();
    uint32_t prop_r = b->PopUInt32();
    uint8_t flag_r = b->PopUInt8();

    REQUIRE(flag == flag_r);
    REQUIRE(prop == prop_r);
    REQUIRE(inrel == inrel_r);
    REQUIRE(outrel == outrel_r);

  }



}
*/

#include <catch2.hpp>
//#include <bytebuffer.h>
#include <types.h>

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

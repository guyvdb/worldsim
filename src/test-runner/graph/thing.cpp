#include <catch2.hpp>
#include <utils.h>
#include <thing.h>

TEST_CASE("Thing should encode and decode from a byte stream","[graph][thing]") {


  graph::gid id = RandomGraphId();
  graph::gid propid = RandomGraphId();
  graph::gid inrel = RandomGraphId();
  graph::gid outrel = RandomGraphId();


  graph::Thing *t1 = new graph::Thing(id,propid,inrel,outrel);

  graph::ByteBuffer *b = t1->Buffer();

  graph::Thing *t2 = new graph::Thing(id,b);


  REQUIRE(t1->Id() == t2->Id());
  REQUIRE(t1->PropId() == t2->PropId());
  REQUIRE(t1->InRelId() == t2->InRelId());
  REQUIRE(t1->OutRelId() == t2->OutRelId());



  delete t1;
  delete t2;
  delete b;

  REQUIRE(true);
}

#include <catch2.hpp>
#include <utils.h>
#include <entity.h>

TEST_CASE("Thing should encode and decode from a byte stream","[graph][thing]") {


  graph::gid id = RandomGraphId();
  graph::gid propid = RandomGraphId();
  graph::gid inrel = RandomGraphId();
  graph::gid outrel = RandomGraphId();

  graph::Entity *t1 = new graph::Entity(id,propid,inrel,outrel);
  graph::Entity *t2 = new graph::Entity(id, t1->Data());


  REQUIRE(t1->GetId() == t2->GetId());
  REQUIRE(t1->PropId() == t2->PropId());
  REQUIRE(t1->InRelId() == t2->InRelId());
  REQUIRE(t1->OutRelId() == t2->OutRelId());



  delete t1;
  delete t2;

  REQUIRE(true);
}

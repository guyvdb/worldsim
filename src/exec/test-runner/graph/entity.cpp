#include <catch2.hpp>
#include <utils.h>
#include <graph/entity.h>
#include <graph/type/buffer.h>

TEST_CASE("Entity should encode and decode from a byte stream","[graph][entity]") {


  graph::type::gid id = RandomGraphId();
  graph::type::gid attribid = RandomGraphId();
  graph::type::gid inRelid = RandomGraphId();
  graph::type::gid outRelId = RandomGraphId();

  graph::Entity *t1 = new graph::Entity(id,attribid,outRelId,inRelid);
  graph::Entity *t2 = new graph::Entity(id, new graph::type::ByteBuffer(t1->Buffer()));

  REQUIRE(t1->Buffer()->Equal(t2->Buffer()));


  REQUIRE(t1->GetGraphId() == t2->GetGraphId());
  REQUIRE(t1->GetRootAttributesBucketId() == t2->GetRootAttributesBucketId());
  REQUIRE(t1->GetRootOutRelationId() == t2->GetRootOutRelationId());
  REQUIRE(t1->GetRootInRelationId() == t2->GetRootInRelationId());

  delete t1;
  delete t2;

  REQUIRE(true);
}

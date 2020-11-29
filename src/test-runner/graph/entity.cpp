#include <catch2.hpp>
#include <utils.h>
#include <entity.h>

TEST_CASE("Thing should encode and decode from a byte stream","[graph][thing]") {


  graph::gid id = RandomGraphId();
  graph::gid attribid = RandomGraphId();
  graph::gid relid = RandomGraphId();



  std::cout << "1\n";

  graph::Entity *t1 = new graph::Entity(id,attribid, relid);

  std::cout << "2\n";
  graph::Entity *t2 = new graph::Entity(id, t1->Buffer());

  std::cout << "T1 ID=";
  std::cout << t1->GetGraphId();
  //std::cout << ", "
std::cout << std::endl;

  std::cout << "3\n";

  std::cout << "--T1--\n";
  std::cout << "Id=" << t1->GetGraphId() << "\n";
  std::cout << "Prop=" << t1->AttributeId() << "\n";
  std::cout << "InRel=" << t1->RelationId() << "\n";


  std::cout << "--T2--\n";
  std::cout << "Id=" << t2->GetGraphId() << "\n";
  std::cout << "Prop=" << t2->AttributeId() << "\n";
  std::cout << "InRel=" << t2->RelationId() << "\n";


  REQUIRE(t1->GetGraphId() == t2->GetGraphId());
  REQUIRE(t1->AttributeId() == t2->AttributeId());
  REQUIRE(t1->RelationId() == t2->RelationId());

  std::cout << "4\n";

  delete t1;
  delete t2;

  REQUIRE(true);
}

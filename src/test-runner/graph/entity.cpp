#include <catch2.hpp>
#include <utils.h>
#include <entity.h>

TEST_CASE("Thing should encode and decode from a byte stream","[graph][thing]") {


  graph::gid id = RandomGraphId();
  graph::gid propid = RandomGraphId();
  graph::gid inrel = RandomGraphId();
  graph::gid outrel = RandomGraphId();


  std::cout << "1\n";

  graph::Entity *t1 = new graph::Entity(id,propid,inrel,outrel);

  std::cout << "2\n";
  graph::Entity *t2 = new graph::Entity(id, t1->Buffer());

  std::cout << "T1 ID=";
  std::cout << t1->GetId();
  //std::cout << ", "
std::cout << std::endl;

  std::cout << "3\n";

  std::cout << "--T1--\n";
  std::cout << "Id=" << t1->GetId() << "\n";
  std::cout << "Prop=" << t1->PropId() << "\n";
  std::cout << "InRel=" << t1->InRelId() << "\n";
  std::cout << "OutRel=" << t1->OutRelId() << "\n";

  std::cout << "--T2--\n";
  std::cout << "Id=" << t2->GetId() << "\n";
  std::cout << "Prop=" << t2->PropId() << "\n";
  std::cout << "InRel=" << t2->InRelId() << "\n";
  std::cout << "OutRel=" << t2->OutRelId() << "\n";


  REQUIRE(t1->GetId() == t2->GetId());
  REQUIRE(t1->PropId() == t2->PropId());
  REQUIRE(t1->InRelId() == t2->InRelId());
  REQUIRE(t1->OutRelId() == t2->OutRelId());

  std::cout << "4\n";

  delete t1;
  delete t2;

  REQUIRE(true);
}

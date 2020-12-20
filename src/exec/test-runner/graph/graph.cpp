#include <catch2.hpp>
#include <utils.h>
#include <graph/graph.h>
#include <graph/config.h>
#include <iostream>

TEST_CASE("Should open a graph","[graph][graph-db]") {
  RemoveTestDirectory();
  std::string datadir(CreateTestDirectory());
  graph::Config config(datadir, datadir);
  graph::Graph *g = new graph::Graph(config);
  REQUIRE(g->Open());
  g->Close();
  delete g;
}


TEST_CASE("Should create a transaction","[graph][graph-db][tx]") {
  RemoveTestDirectory();
  std::string datadir(CreateTestDirectory());
  graph::Config config(datadir, datadir);
  graph::Graph *g = new graph::Graph(config);
  REQUIRE(g->Open());
  g->Close();
  delete g;
}

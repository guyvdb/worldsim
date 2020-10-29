#include <catch2.hpp>

#include "../utils.h"
#include <iostream>
#include <log.h>




TEST_CASE("The log should create a log file in the log directory", "[graph][log]") {


  // Create a new tempory directory
  RemoveTestDirectory();
  const char * dir = CreateTestDirectory();

  std::cout << "LOG DIR: " << dir << std::endl;

  // Create a log
  graph::Log *log = new graph::Log(dir);

  // Open the log
  REQUIRE(log->Open());
  REQUIRE(log->Close());

  delete log;

  //INFO("This is a log message");

  //SECTION("Log Should Open") {
  //  REQUIRE(0 == 0);
  //}



}

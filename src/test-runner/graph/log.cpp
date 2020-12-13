#include <catch2.hpp>

#include "../utils.h"
#include <iostream>
#include <wal/writeaheadlog.h>
//#include <tx/transactionlog.h>




TEST_CASE("The log should create a log file in the log directory", "[graph][log]") {


  // Create a new tempory directory
  //RemoveTestDirectory();
  const char * dir = CreateTestDirectory();


  // Create a log
  graph::tx::TransactionLog *log = new graph::tx::TransactionLog(dir);

  // Open the log
  REQUIRE(log->Open());
  REQUIRE(log->Close());

  delete log;

  //INFO("This is a log message");

  //SECTION("Log Should Open") {
  //  REQUIRE(0 == 0);
  //}



}

#include <catch2.hpp>
#include <utils.h>
#include <filesystem>
#include <tx/transactionlog.h>
#include <iostream>


graph::tx::TransactionLog* CreateTestTransactionLog() {
  RemoveTestDirectory();
  std::filesystem::path fn(CreateTestDirectory());
  graph::tx::TransactionLog *l = new graph::tx::TransactionLog(fn.c_str());
  return l;

}

TEST_CASE("Should open a transaction log","[graph][txlog]") {
  /*
  graph::TransactionLog *log = CreateTestTransactionLog();
  graph::txid id;

  // First time opening it has no data
  REQUIRE(log->Open());
  REQUIRE(log->TransactionBegin(&id));
  std::cout << "Log id=" << id << std::endl;
  REQUIRE(log->TransactionEnd(graph::RolledBack));
  REQUIRE(log->TransactionRelease());

  log->Close();


  // Second time opening it should extract last txno.
  REQUIRE(log->Open());
  REQUIRE(log->TransactionBegin(&id));
  std::cout << "Log id=" << id << std::endl;


  // write some data to the log
  std::uint8_t data[] = {0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};
  log->TransactionAppend(graph::Storeable::Type::Entity, graph::Create,1, data, sizeof(data));

  // Commit
  REQUIRE(log->TransactionEnd(graph::Committed));
  REQUIRE(log->TransactionRelease());



  log->Close();


  delete log;
  */
}






/*
 *       bool TransactionBegin(txid *id);
      bool TransactionAppend(Storeable::Type type, TransactionOp op, const std::uint8_t *data, std::size_t len);
      bool TransactionEnd(TransactionStatus status);
      bool TransactionRelease();*/

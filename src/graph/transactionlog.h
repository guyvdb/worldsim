#ifndef TRANSACTIONLOG_H
#define TRANSACTIONLOG_H

#include <types.h>
//#include <cstdio>
#include <gerror.h>
#include <file.h>
#include <mutex>
#include <vector>
#include <storeable.h>
#include <buffer.h>

#define LOG_NAME "transaction.log"

#define FRAME_HEADER_MAGIC0 0xCC
#define FRAME_HEADER_MAGIC1 0xDD
#define FRAME_FOOTER_MAGIC0 0xAA
#define FRAME_FOOTER_MAGIC1 0xBB

#define FRAME_FOOTER_SIZE 14 // footer is 14 bytes long
namespace graph {



  /*
   The transaction log is comprised of sections which are:

   <header><record><record>...<record><footer>

   The header contains a magic number, a transaction number,
   a timestamp and a record count.

   A record contains a type code, a length and length bytes data.

   A footer contains a start pointer which points to the header, a checksum
   and a magic number.

   The log is append only and a mutex controlls read/write access to it.

   */

  // Frame Header: | magic | txno | timestamp | record count | <first record> ...
  // Frame Record: | type | opcode | record len | data... | ... <next record>
  // Frame Footer: | start of frame pointer | checksum | magic

  enum TransactionStatus : std::uint8_t {
    Committed,
    RolledBack
  };

  enum TransactionOp : std::uint8_t {
    NoOp,
    Create,
    Update,
    Delete
  };

  class FrameRecord {
    public:
      FrameRecord(gid id, Storeable::Concept concept, TransactionOp op, ByteBuffer *buffer) : m_id(id), m_concept(concept), m_op(op), m_buffer(buffer) {}

      gid Id() { return this->m_id; }
      Storeable::Concept Type() { return  this->m_concept; }
      TransactionOp Op() { return this->m_op; }
      ByteBuffer *Buf() { return this->m_buffer; }
      //std::size_t Size() { return this->m_data.size(); }
      //const char* Data() { return (const char*) this->m_data.data(); }
    private:
      gid m_id;
      Storeable::Concept m_concept;
      TransactionOp m_op;
      ByteBuffer *m_buffer;
  };

  struct FrameHeader {
      char Magic[2];
      txid TxNo;
      std::uint64_t Timestamp;
      std::uint16_t RecordCount;
  };

  struct FrameFooter {
    long FrameStart;
    TransactionStatus TxStatus;
    uint32_t CRC;
    char Magic[2];
  };


  class TransactionLog {
    public:
      TransactionLog(const char *logdir);
      ~TransactionLog();
      bool Open();
      bool Close();
      void Lock();
      void Release();
      txid FrameStart();
      bool FrameAppend(gid id, Storeable::Concept type, TransactionOp op, ByteBuffer *buffer);
      bool FrameEnd();
    private:
      bool LastTransactionNumber(txid *result);
      long LastFrameStartAddress();

      bool Validate();
      bool RollRequired();
      bool Roll();

      const char *m_logdir;
      File *m_file;
      bool m_isopen;
      ErrorNo m_lastError;
      txid m_counter;
      std::mutex m_mutex;
      std::vector<FrameRecord*> m_transactionData;
      std::uint64_t m_framepointer;
      //long m_maxSize;
  };
}
#endif // TRANSACTIONLOG_H







// ========= OLD

/*
 * This is the write ahead log. The log needs to store:
 *   deletes - keep a copy of the graph id's
 *   inserts - keep a copy of the new values
 *   updates - keep a copy of the old and new values
 * The log should write a checkpoint after all pages are
 * successfully flushed to the disk from the cache. Once
 * a checkpoint has been reached, the log can be truncated
 * at that point.
 *
 * On startup the log is read backwards to ensure that a checkpoint
 * is the last transaction in the log.
 *
 * If a checkpoint is not the last transaction in the log, a recovery
 * needs to be undertaken.
 */

/* Log OPCODE's
 *
 * NEW_ENTITYID
 * NEW_RELATIONID
 * NEW_ENTITY_TYPEID
 * NEW_ENTITY_PROPERTYID
 * NEW_RELATION_PROPERTYID
 * NEW_RELATION_TYPEID
 *
 * NEW_ENTITY
 * NEW_ENTITY_TYPE
 * NEW_ENTITY_PROPERTY
 *
 * NEW_RELATION
 * NEW_RELATION_TYPE
 * NEW_RELATION_PROPERTY
 *
 * UPDATE_ENTITY
 * UPDATE_ENTITY_TYPE
 * UPDATE_ENTITY_PROPERTY
 *
 * UPDATE_RELATION
 * UPDATE_RELATION_TYPE
 * UPDATE_RELATION_PROPERTY
 *
 * DELETE_ENTITY
 * DELETE_ENTITY_TYPE
 * DELETE_ENTITY_PROPERTY
 *
 * DELETE_RELATION
 * DELETE_TYPE
 * DELETE_RELATION_PROPERTY
 *
 *
 */

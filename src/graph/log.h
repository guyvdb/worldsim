#ifndef LOG_H
#define LOG_H

#include <types.h>
#include <cstdio>
#include <gerror.h>

#define LOG_NAME "transaction.log"

namespace graph {


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


  class LogFrameHeader {

  };

  class LogFrameFooter {

  };


  // The changes that make up a transaction are called TxRecords and are grouped
  // together in the TxFrame. The TxFrame constitutes the complete record of change.
  // The frame holds n records.
  //
  // Frame Header: | magic | txno | timestamp | record count | <first record> ...
  // Frame Record: | type | opcode | record len | data... | ... <next record>
  // Frame Footer: | start of frame pointer |
  class LogFrame {


  };

  // A TxRecord represents a change of an object. Type is the type of object. It can
  // be one of Thing, Relation, Property, ThingType, RelationType, PropertyType, Id
  //
  // The opcode is what is happening to the type. The action can be create, update, delete

  struct LogRecord {

  };

  class Log {
    public:
      Log(const char *logdir);

      // Open the log
      bool Open();

      // Close the log
      bool Close();

      // Write a transaction to the log

      // Start a checkpoint


      // End a checkpoint

    private:
      const char *m_logdir;
      std::FILE *m_file;
      bool m_isopen;
      ErrorNo m_lastError;


  };
}
#endif // LOG_H

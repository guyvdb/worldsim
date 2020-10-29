#ifndef TX_H
#define TX_H

#include <vector>


#include <gerror.h>
#include <types.h>
#include <thing.h>
#include <relation.h>

namespace graph {

//  class LogManager;
  //class CacheManager;
  class Thing;
  class Relation;
  class TransactionManager;



  // StorableRef stores a pointer to storable and mantains flags for the state of the object
  class StorableRef {
    public:
      StorableRef(Storeable *storeable);
      ~StorableRef();
    private:
      Storeable *m_storable;
  };

  // All storable objects that are created during the lifecycle of the transaction belong
  // to the transaction. The transaction tracks all object and their modifications.
  // On committing or rolling back a transaction, all changes are written to the log,
  // then written to the cache. Finally, the storable objects are disposed and the transaction
  // is also disposed of

  class Tx {
    public:

      friend TransactionManager;

      // Commit a readwrite transaction to disk and free its resources
      bool Commit();

      // Free a readwrite transactions resources without commiting to disk
      void Rollback();

      // Free a readonly transactions resources
      void Finished();




      ErrorNo LastError();


      Thing *FindEntityById(gid id);
      Relation *FindRelationById(gid id);

      Thing *NewThing();
      Relation *NewRelation();

    protected:

      Tx(TransactionManager *manager, bool readonly);
      ~Tx();

      // Get the next id for the given storable type
      gid NextGraphId(Storeable::Type type);
      
    private:
      void ReleaseModifiedResource();

      bool m_readonly;
      TransactionManager *m_transactionManager;
      ErrorNo m_lastError;
      std::vector<Storeable*> *m_modified;

      gid m_counter;
  };
}
#endif // TX_H

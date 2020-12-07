#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <map>

#include <types.h>
#include <storeable.h>

namespace graph {

  class Entity;
  class AttributeDefinition;
  class AttributeBucket;
  class Relation;
  class Attribute;
  class AttributeCollection;
  class TransactionManager;
  class CacheManager;


  class Transaction {
    public:
     // friend TransactionManager;

      enum TransactionState : int {
        Created,
        Started,
        RolledBack,
        Committed
      };
      Transaction();
      ~Transaction();
      bool Commit();
      void Rollback();
      bool ReadOnly() { return this->m_readonly; }
      TransactionState State() { return m_state; }
      ErrorNo LastError();

      bool IsReadable();
      bool IsWriteable();

      AttributeDefinition *CreateAttributeDefinition();
      AttributeDefinition *FindAttributeDefinitionById(gid id);

      AttributeBucket *CreateAttributeBucket();
      AttributeBucket *FindAttributeBucketById(gid id);


      //Entity *CopyEntity(Entity *src);
      Entity *CreateEntity(gid type);
      Entity *FindEntityById(gid id);

      AttributeCollection *LoadAttributes(StoreableWithAttributes *storeable);



      Relation *CreateRelation(gid type);
      Relation *FindRelationById(gid id);
      Attribute *CreateAttribute(tid type);


      void SetTransactionManager(TransactionManager *manager) {this->m_transactionManager = manager; }
      void ChangeState(TransactionState state) {this->m_state = state;}
      void SetReadOnly(bool value) { this->m_readonly = value; }
      void SetTxId(txid id) { this->m_txid = id; }
      std::vector<Storeable*> ModifiedObjects();
    private:
      void ReleaseResources();
      TransactionManager *TxMan() { return this->m_transactionManager; }
      CacheManager *CacheMan();

      // Allocate a new id via the id manager
      StoreableId AllocateId(Storeable::Concept concept);

      // Allow the id manager to reclaim an id that was not used
      bool ReclaimId(StoreableId id);

      bool m_readonly;
      TransactionManager *m_transactionManager;
      ErrorNo m_lastError;
      txid m_txid;
      TransactionState m_state;      

      std::vector<Storeable*> m_allocatedObjects;
      std::vector<StoreableId> m_allocatedIds;

      std::vector<AttributeCollection*> m_attributeCollections;
      std::map<StoreableWithAttributes*, AttributeCollection*> m_attributeCollectionIndex;


  };
}
#endif // TRANSACTION_H

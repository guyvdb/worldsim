#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <map>
#include <grapherrors.h>
#include <type/base.h>
#include <storeable.h>
#include <tx/transactioncache.h>
#include <type/type.h>

namespace graph {


  class Entity;
  class AttributeDefinition;
  class AttributeBucket;
  class Relation;
  class Attribute;
  class AttributeCollection;

  namespace cache {
    class CacheManager;
  }

  namespace tx {
    class TransactionManager;
    class Transaction {
      public:
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
        AttributeDefinition *FindAttributeDefinitionById(type::gid id);
        AttributeBucket *CreateAttributeBucket();
        AttributeBucket *FindAttributeBucketById(type::gid id);

        Entity *CreateEntity(std::string type);
        Entity *CreateEntity(type::gid type);
        Entity *FindEntity(type::gid id);

        type::Type *CreateType();
        type::Type *FindType(type::gid id);
        type::Type *FindType(std::string name);


        AttributeCollection *LoadAttributes(StoreableWithAttributes *storeable);
        Relation *CreateRelation(type::gid type);
        Relation *FindRelationById(type::gid id);
        Attribute *CreateAttribute(type::gid type);
        void SetTransactionManager(TransactionManager *manager) {this->m_transactionManager = manager; }
        void ChangeState(TransactionState state) {this->m_state = state;}
        void SetReadOnly(bool value) { this->m_readonly = value; }
        void SetTxId(type::txid id) { this->m_txid = id; }
        std::vector<Storeable*> ModifiedObjects();
      private:
        void ReleaseResources();
        TransactionManager *TxMan() { return this->m_transactionManager; }
        cache::CacheManager *CacheMan();
        // Allocate a new id via the id manager
        StoreableId AllocateId(Storeable::Concept concept);
        // Allow the id manager to reclaim an id that was not used
        bool ReclaimId(StoreableId id);
        bool m_readonly;
        TransactionManager *m_transactionManager;
        TransactionCacheManager m_transactionCacheManager;
        ErrorNo m_lastError;
        type::txid m_txid;
        TransactionState m_state;
        std::vector<StoreableId> m_allocatedIds;
        std::vector<AttributeCollection*> m_attributeCollections;
        std::map<StoreableWithAttributes*, AttributeCollection*> m_attributeCollectionIndex;
    };

  }
}
#endif // TRANSACTION_H

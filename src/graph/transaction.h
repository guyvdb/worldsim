#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <map>

#include "type/errors.h"
#include "type/base.h"
#include "type/factory.h"

#include "storeable.h"
#include "tx/transactioncache.h"
#include "class.h"
#include "propdef.h"

namespace graph {


  class Entity;
  class Relation;

  namespace cache {
    class CacheManager;
  }

  namespace tx {
    class TransactionManager;
  }
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
        graph::type::ErrorNo LastError();
        bool IsReadable();
        bool IsWriteable();

        Entity *CreateEntity();
        Entity *CreateEntity(std::string clazz);
        Entity *CreateEntity(type::gid clazz);
        Entity *CreateEntity(Class *clazz);
        Entity *FindEntity(type::gid id);

        Relation *CreateRelation();
        Relation *CreateRelation(std::string clazz);
        Relation *CreateRelation(type::gid clazz);
        Relation *CreateRelation(Class *clazz);
        Relation *FindRelation(type::gid id);

        // Protect theres ????
        Class *CreateClass(Storeable::Concept concept, std::string name, Class *superclass=0x0);
        Class *FindClass(type::gid id);
        Class *FindClass(std::string name);

        Inheritance *CreateInheritance(type::gid superclass, type::gid subclass);
        Inheritance *FindInheritance(type::gid id);

        PropDef *CreatePropDef();
        PropDef *FindPropDef(type:: gid id);

        void SetTransactionManager(tx::TransactionManager *manager) {this->m_transactionManager = manager; }
        void ChangeState(TransactionState state) {this->m_state = state;}
        void SetReadOnly(bool value) { this->m_readonly = value; }
        void SetTxId(type::txid id) { this->m_txid = id; }
        std::vector<Storeable*> ModifiedObjects();

      protected:
        // Only the registry should be able to create Classes, Inheritances and PropTypes
      private:
        Relation *FactoryCreateRelation(type::gid id, type::gid superclazz);
        Entity *FactoryCreateEntity(type::gid id, type::gid superclazz);
        void ReleaseResources();
        tx::TransactionManager *TxMan() { return this->m_transactionManager; }
        cache::CacheManager *CacheMan();
        // Allocate a new id via the id manager
        StoreableId AllocateId(Storeable::Concept concept);
        // Allow the id manager to reclaim an id that was not used
        bool ReclaimId(StoreableId id);
        bool m_readonly;
        tx::TransactionManager *m_transactionManager;
        tx::TransactionCacheManager m_transactionCacheManager;
        graph::type::ErrorNo m_lastError;
        type::txid m_txid;
        TransactionState m_state;
        std::vector<StoreableId> m_allocatedIds;        
    };


}
#endif // TRANSACTION_H

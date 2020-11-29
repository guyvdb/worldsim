#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>


#include <gerror.h>
#include <types.h>
//#include <entity.h>
//#include <entitytype.h>
//#include <relation.h>
//#include <relationtype.h>
//#include <attribute.h>
//#include <attributetype.h>

#include <storeable.h>

namespace graph {
  class Entity;
  class EntityType;
  class Relation;
  class RelationType;
  class Attribute;
  class AttributeType;
  class TransactionManager;


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


      EntityType *CreateEntityType();
      Entity *CopyEntity(Entity *src);
      Entity *CreateEntity(gid type);
      Entity *FindEntityById(gid id);

      RelationType *CreateRelationType();
      Relation *CreateRelation(gid type);
      Relation *FindRelationById(gid id);

      AttributeType *CreateAttributeType();
      Attribute *CreateAttribute(gid type);



      void SetTransactionManager(TransactionManager *manager) {this->m_transactionManager = manager; }
      void ChangeState(TransactionState state) {this->m_state = state;}
      void SetReadOnly(bool value) { this->m_readonly = value; }
      void SetTxId(txid id) { this->m_txid = id; }


      std::vector<Storeable*>* CreatedObjects() { return &this->m_createdObjects; }

    private:


      void ReleaseResources();




      // Allocate a new id via the id manager
      StoreableId AllocateId(Storeable::Concept concept);

      // Allow the id manager to reclaim an id that was not used
      bool ReclaimId(StoreableId id);




     // gid NextGraphId(Storeable::Type type);
      bool m_readonly;
      TransactionManager *m_transactionManager;
      ErrorNo m_lastError;
      //gid m_counter; // temp
      txid m_txid;
      TransactionState m_state;
      //std::vector<Relation*> m_allocatedRelations;
      std::vector<Storeable*> m_createdObjects;
      std::vector<Storeable*> m_updatedObjects;
      std::vector<Storeable*> m_deletedObjects;
      std::vector<StoreableId> m_allocatedIds;
      //std::vector<Relation*> m_modifiedRelations;

  };
}
#endif // TRANSACTION_H

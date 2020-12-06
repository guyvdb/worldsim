#include "entity.h"

#include <iostream>
#include <cstdio>
#include <transaction.h>
#include <relation.h>


namespace graph {


  Entity::Entity() : StoreableWithAttributes(InvalidGraphId, Storeable::EntitySize) {
    this->Load(ROOT_OUT_REL_ID_OFFSET, InvalidGraphId);
    this->Load(ROOT_IN_REL_ID_OFFSET, InvalidGraphId);
  }


  Entity::Entity(gid id) : StoreableWithAttributes(id, Storeable::EntitySize) {
    this->Load(ROOT_OUT_REL_ID_OFFSET, InvalidGraphId);
    this->Load(ROOT_IN_REL_ID_OFFSET, InvalidGraphId);
  }


  // The entity takes ownership of the buffer
  Entity::Entity(gid id, ByteBuffer *buffer) : StoreableWithAttributes(id, buffer) {
    // Load of in and out rel id is within buffer
  }

  Entity::Entity(gid id, gid attribid, gid outRelId, gid inRelid) : StoreableWithAttributes(id, Storeable::EntitySize) {
    this->Load(ROOT_ATTRIB_BUCKET_ID_OFFSET, attribid);
    this->Load(ROOT_OUT_REL_ID_OFFSET, outRelId);
    this->Load(ROOT_IN_REL_ID_OFFSET, inRelid);

    std::cout << "Entity() constructed: outrelid(set)=" << outRelId;
    std::cout << ", outrelid(get)=" << this->GetRootOutRelationId();
    std::cout << ", inrelid(set)=" << inRelid;
    std::cout << ", inrelid(get)=" << this->GetRootInRelationId() << std::endl;


  }

  Entity::~Entity()  {
  }

  gid Entity::GetRootOutRelationId() {
    return this->GetUint32(ROOT_OUT_REL_ID_OFFSET);
  }

  void Entity::SetRootOutRelId(gid id) {
    this->Update(ROOT_OUT_REL_ID_OFFSET, id);
  }

  gid Entity::GetRootInRelationId() {
    return this->GetUint32(ROOT_IN_REL_ID_OFFSET);
  }

  void Entity::SetRootInRelationId(gid id) {
    this->Update(ROOT_IN_REL_ID_OFFSET, id);
  }

  AttributeCollection* Entity::Attributes() {
    if (this->m_transaction == 0x0){
      std::cout << "[ENTITY] Error - no transaction attached." << std::endl;
      return 0x0;
    }

    return this->m_transaction->LoadAttributes(this);
  }

  void Entity::AddInRelation(Relation *r) {
    if(!this->IsWriteable()) {
      std::cout << "[ENTITY] Error - cannot add relation. Entity is not writeable." << std::endl;
      return;
    }

    // add this relation id to our in relation chain
    if(this->GetRootInRelationId() == InvalidGraphId) {
      // Relation list is empty -- set r as root
      this->Update(ROOT_IN_REL_ID_OFFSET, r->GetGraphId());
    } else {
      // Relation list is not empty -- find the tail
      Relation *child = this->Tx()->FindRelationById(this->GetRootInRelationId());
      if(child == 0x0) {
        std::cout << "[ENTITY] Error - cannot find root in relation." << std::endl;
        return;
      }

      // Are we the from or the to entity?
      if(r->GetFromEntityId() == this->GetGraphId()) {
        // we are the from entity
        while(child->GetNextFromInRelationId() != InvalidGraphId) {
          child = this->Tx()->FindRelationById(child->GetNextFromInRelationId());
          if(child == 0x0) {
            std::cout << "[ENTITY] Error - cannot find root in relation." << std::endl;
            return;
          }
        }

        // we are at the last from in relation in the chain
        child->SetNextFromInRelationId(this->GetGraphId());
        // done

      } else {
        // we are the to entity
        while(child->GetNextToInRelationId() != InvalidGraphId) {
          child = this->Tx()->FindRelationById(child->GetNextToInRelationId());
          if(child == 0x0) {
            std::cout << "[ENTITY] Error - cannot find root in relation." << std::endl;
            return;
          }
        }

        child->SetNextToInRelationId(this->GetGraphId());
      }
    }
  }

  void Entity::AddOutRelation(Relation *r) {
    if(!this->IsWriteable()) {
      std::cout << "[ENTITY] Error - cannot add relation. Entity is not writeable." << std::endl;
      return;
    }

    // add this relation id to our out relation chain
    if(this->GetRootOutRelationId() == InvalidGraphId) {
      // Relation list is empty -- set r as root
      this->Update(ROOT_OUT_REL_ID_OFFSET, r->GetGraphId());
    } else {
      // Relation list is not empty -- find the tail
      Relation *child = this->Tx()->FindRelationById(this->GetRootOutRelationId());
      if(child == 0x0) {
        std::cout << "[ENTITY] Error - cannot find root out relation." << std::endl;
        return;
      }

      // Are we the from or the to entity?
      if(r->GetFromEntityId() == this->GetGraphId()) {
        // we are the from entity
        while(child->GetNextFromOutRelationId() != InvalidGraphId) {
          child = this->Tx()->FindRelationById(child->GetNextFromOutRelationId());
          if(child == 0x0) {
            std::cout << "[ENTITY] Error - cannot find root out relation." << std::endl;
            return;
          }
        }

        // we are at the last from out relation in the chain
        child->SetNextFromOutRelationId(this->GetGraphId());
        // done

      } else {
        // we are the to entity
        while(child->GetNextToOutRelationId() != InvalidGraphId) {
          child = this->Tx()->FindRelationById(child->GetNextToOutRelationId());
          if(child == 0x0) {
            std::cout << "[ENTITY] Error - cannot find root out relation." << std::endl;
            return;
          }
        }

        child->SetNextToOutRelationId(this->GetGraphId());
      }
    }
  }

  Relation* Entity::CreateRelation(Entity *to, tid relType) {
    // we are the from entity and the passed in entity is the to entity
    if(!this->IsWriteable()) {
      std::cout << "[ENTITY] Error - entity is not writeable." << std::endl;
      return 0x0;
    }


    Relation *r = this->Tx()->CreateRelation(relType);

    // set the entity ids on the relation
    r->SetFromEntityId(this->GetGraphId());
    r->SetToEntityId(to->GetGraphId());

    // now set the relation id on the from entity chain and the to entity chain

    // from is an out relation
    this->AddOutRelation(r);

    // to is an in relation
    to->AddInRelation(r);

    // return the relation
    return r;
  }


  EntityCollection::EntityCollection() {
  }

  EntityCollection::~EntityCollection() {
  }

  void EntityCollection::Add(Entity *entity) {
    this->m_entities.push_back(entity);
  }

  Entity* EntityCollection::operator[](std::size_t index){
    if(index < this->m_entities.size() && index >= 0) {
      return this->m_entities[index];
    }
    return 0x0;
  }



}

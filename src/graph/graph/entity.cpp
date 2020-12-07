#include "entity.h"

#include <iostream>
#include <cstdio>
#include <transaction.h>
#include <relation.h>


namespace graph {


  Entity::Entity() : StoreableWithAttributes(InvalidGraphId, Storeable::EntitySize) {
    this->Load(ROOT_OUT_REL_ID_OFFSET, InvalidGraphId);
    this->Load(ROOT_IN_REL_ID_OFFSET, InvalidGraphId);
    this->m_inRelations = new RelationCollection();
    this->m_outRelations = new RelationCollection();
  }


  Entity::Entity(gid id) : StoreableWithAttributes(id, Storeable::EntitySize) {
    this->Load(ROOT_OUT_REL_ID_OFFSET, InvalidGraphId);
    this->Load(ROOT_IN_REL_ID_OFFSET, InvalidGraphId);
    this->m_inRelations = new RelationCollection();
    this->m_outRelations = new RelationCollection();
  }


  // The entity takes ownership of the buffer
  Entity::Entity(gid id, ByteBuffer *buffer) : StoreableWithAttributes(id, buffer) {
    // Load of in and out rel id is within buffer
    this->m_inRelations = new RelationCollection();
    this->m_outRelations = new RelationCollection();
  }

  Entity::Entity(gid id, gid attribid, gid outRelId, gid inRelid) : StoreableWithAttributes(id, Storeable::EntitySize) {
    this->Load(ROOT_ATTRIB_BUCKET_ID_OFFSET, attribid);
    this->Load(ROOT_OUT_REL_ID_OFFSET, outRelId);
    this->Load(ROOT_IN_REL_ID_OFFSET, inRelid);
    this->m_inRelations = new RelationCollection();
    this->m_outRelations = new RelationCollection();
  }

  Entity::~Entity()  {
    delete this->m_inRelations;
    delete this->m_outRelations;
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

  RelationCollection *Entity::InRelations() {
    if(!this->m_inRelations->IsLoaded()) {
      // load the collection
    }

    return this->m_inRelations;
  }

  RelationCollection *Entity::OutRelations() {
    if (!this->IsReadable()) {
      std::cout << "[ENTITY] Error - entity is not readable." << std::endl;
      return 0x0;
    }

    if(!this->m_outRelations->IsLoaded()) {
      if(this->GetRootOutRelationId() != InvalidGraphId) {
        std::cout << "FindRelationById - 1\n";
        Relation *r = this->Tx()->FindRelationById(this->GetRootOutRelationId());
        if(r != 0x0) {
          r->SetTransaction(this->Tx());
          this->m_outRelations->Add(r);
          while(r->GetPrevOutRelationId() != InvalidGraphId) {
            std::cout << "FindRelationById - 2\n";
            r = this->Tx()->FindRelationById(r->GetPrevOutRelationId());
            if(r != 0x0) {
              r->SetTransaction(this->Tx());
              this->m_outRelations->Add(r);
            }
          }
        }
      }
      this->m_outRelations->SetLoaded(true);
    }
    return this->m_outRelations;
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
      std::cout << "FindRelationById - 3\n";
      Relation *child = this->Tx()->FindRelationById(this->GetRootInRelationId());
      if(child == 0x0) {
        std::cout << "[ENTITY] Error - cannot find root in relation." << std::endl;
        return;
      }

      // Are we the from or the to entity?
      if(r->GetFromEntityId() == this->GetGraphId()) {
        // we are the from entity
        while(child->GetNextOutRelationId() != InvalidGraphId) {
          std::cout << "FindRelationById - 4\n";
          child = this->Tx()->FindRelationById(child->GetNextOutRelationId());
          if(child == 0x0) {
            std::cout << "[ENTITY] Error - cannot find root in relation." << std::endl;
            return;
          }
        }

        // we are at the last from in relation in the chain
        child->SetNextOutRelationId(this->GetGraphId());
        // done

      } else {
        // we are the to entity
        while(child->GetNextInRelationId() != InvalidGraphId) {
          std::cout << "FindRelationById - 5\n";
          child = this->Tx()->FindRelationById(child->GetNextInRelationId());
          if(child == 0x0) {
            std::cout << "[ENTITY] Error - cannot find root in relation." << std::endl;
            return;
          }
        }

        child->SetNextInRelationId(this->GetGraphId());
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
      std::cout << "RootOutRelationId=" << this->GetRootOutRelationId() << std::endl;

      // Relation list is not empty -- find the tail
      std::cout << "FindRelationById - 6\n";
      Relation *child = this->Tx()->FindRelationById(this->GetRootOutRelationId());
      if(child == 0x0) {
        std::cout << "[ENTITY] Error - cannot find root out relation." << std::endl;
        return;
      }

      // Are we the from or the to entity?
      if(r->GetFromEntityId() == this->GetGraphId()) {

        std::cout << "GetNextOutRelationId=" << child->GetNextOutRelationId() << std::endl;

        // we are the from entity
        while(child->GetNextOutRelationId() != InvalidGraphId) {
          std::cout << "FindRelationById - 7, childid=" << child->GetGraphId() << std::endl;
          child = this->Tx()->FindRelationById(child->GetNextOutRelationId());
          if(child == 0x0) {
            std::cout << "[ENTITY] Error - cannot find root out relation." << std::endl;
            return;
          }
        }

        // we are at the last from out relation in the chain
        child->SetNextOutRelationId(this->GetGraphId());
        // done

      } else {
        // we are the to entity
        while(child->GetPrevInRelationId() != InvalidGraphId) {
          std::cout << "FindRelationById - 8\n";
          child = this->Tx()->FindRelationById(child->GetPrevInRelationId());
          if(child == 0x0) {
            std::cout << "[ENTITY] Error - cannot find root out relation." << std::endl;
            return;
          }
        }

        child->SetPrevInRelationId(this->GetGraphId());
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

#include "entity.h"

#include <iostream>
#include <cstdio>
#include <transaction.h>
#include <relation.h>


namespace graph {

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Entity::Entity() : StoreableWithAttributes(NullGraphId, Storeable::EntitySize) {
    this->Load(ROOT_OUT_REL_ID_OFFSET, NullGraphId);
    this->Load(ROOT_IN_REL_ID_OFFSET, NullGraphId);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Entity::Entity(gid id) : StoreableWithAttributes(id, Storeable::EntitySize) {
    this->Load(ROOT_OUT_REL_ID_OFFSET, NullGraphId);
    this->Load(ROOT_IN_REL_ID_OFFSET, NullGraphId);
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  // The entity takes ownership of the buffer
  Entity::Entity(gid id, ByteBuffer *buffer) : StoreableWithAttributes(id, buffer) {
    // Load of in and out rel id is within buffer
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Entity::Entity(gid id, gid attribid, gid outRelId, gid inRelid) : StoreableWithAttributes(id, Storeable::EntitySize) {
    this->Load(ROOT_ATTRIB_BUCKET_ID_OFFSET, attribid);
    this->Load(ROOT_OUT_REL_ID_OFFSET, outRelId);
    this->Load(ROOT_IN_REL_ID_OFFSET, inRelid);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Entity::~Entity()  {
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  gid Entity::GetRootOutRelationId() {
    return this->GetUint32(ROOT_OUT_REL_ID_OFFSET);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Entity::SetRootOutRelId(gid id) {
    this->Update(ROOT_OUT_REL_ID_OFFSET, id);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  gid Entity::GetRootInRelationId() {
    return this->GetUint32(ROOT_IN_REL_ID_OFFSET);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Entity::SetRootInRelationId(gid id) {
    this->Update(ROOT_IN_REL_ID_OFFSET, id);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  std::vector<Relation*> Entity::InRelations() {
    std::vector<Relation*> v;
    if(this->IsReadable()) {
      if(this->GetRootInRelationId() != NullGraphId) {
        Relation *r = this->Tx()->FindRelationById(this->GetRootInRelationId());
        if(r != 0x0) {
          v.push_back(r);
          while(r->GetNextInRelationId() != NullGraphId) {
            r = this->Tx()->FindRelationById(r->GetNextInRelationId());
            if(r != 0x0) {
              v.push_back(r);
            } else {
              break;
            }
          }
        }
      }
    } else {
      std::cout << "[ENTITY] Error - failed to load out relations. Entity is not readable." << std::endl;
    }
    return v;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  std::vector<Relation*>Entity::OutRelations() {
    std::vector<Relation*> v;
    if(this->IsReadable()) {
      if(this->GetRootOutRelationId() != NullGraphId) {
        Relation *r = this->Tx()->FindRelationById(this->GetRootOutRelationId());
        if(r != 0x0) {
          v.push_back(r);
          while(r->GetNextOutRelationId() != NullGraphId) {
            r = this->Tx()->FindRelationById(r->GetNextOutRelationId());
            if(r != 0x0) {
              v.push_back(r);
            } else {
              break;
            }
          }
        }
      }
    } else {
      std::cout << "[ENTITY] Error - failed to load out relations. Entity is not readable." << std::endl;
    }
    return v;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  AttributeCollection* Entity::Attributes() {
    if (this->m_transaction == 0x0){
      std::cout << "[ENTITY] Error - no transaction attached." << std::endl;
      return 0x0;
    }
    return this->m_transaction->LoadAttributes(this);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Entity::LinkInRelation(Relation *r) {
    if(!this->IsWriteable()) {
      std::cout << "[ENTITY] Error - cannot link relation. Entity is not writeable." << std::endl;
      return false;
    }

    if(this->GetRootInRelationId() == NullGraphId) {
      // link on root
      this->SetRootInRelationId(r->GetGraphId());
      return true;
    } else {
      // link at end of chain
      std::vector<Relation*> v = this->InRelations();
      // should be the last one in v
      Relation *c = v.back();
      if(c->GetNextInRelationId() == NullGraphId) {
        c->SetNextInRelationId(r->GetGraphId());
        r->SetPrevInRelationId(c->GetGraphId());
        return true;
      } else {
        std::cout << "[ENTITY] Error - the last element of InRelations does not have a NULL pointer to next element." << std::endl;
        return false;
      }
    }
  }

  /* ----------------------------------------------------------------------------------------
   * The out relations are in a double linked list:
   *
   * Root -> r1 -> r2 -> r3 -> rn -> 0x0  (next id)
   *         rn -> r3 -> r2 -> r1 -> 0x0  (prev id)
   *
   * If there are no out relations for this entity, the relation is linked to the root
   * located on the entity. If the entity has at least one relation linked then the new
   * relation is linked at the end of the chain
   * --------------------------------------------------------------------------------------*/
  bool Entity::LinkOutRelation(Relation *r) {
    if(!this->IsWriteable()) {
      std::cout << "[ENTITY] Error - cannot link relation. Entity is not writeable." << std::endl;
      return false;
    }

    if(this->GetRootOutRelationId() == NullGraphId) {
      // link on root
      this->SetRootOutRelId(r->GetGraphId());
      return true;
    } else {
      // link at end of chain
      std::vector<Relation*> v = this->OutRelations();
      // should be the last one in v
      Relation *c = v.back();
      if(c->GetNextOutRelationId() == NullGraphId) {
        c->SetNextOutRelationId(r->GetGraphId());
        r->SetPrevOutRelationId(c->GetGraphId());
        return true;
      } else {
        std::cout << "[ENTITY] Error - the last element of OutRelations does not have a NULL pointer to next element." << std::endl;
        return false;
      }
    }
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Relation* Entity::CreateRelation(Entity *to, gid type) {
    // we are the from entity and the passed in entity is the to entity
    if(!this->IsWriteable()) {
      std::cout << "[ENTITY] Error - entity is not writeable." << std::endl;
      return 0x0;
    }


    Relation *r = this->Tx()->CreateRelation(type);

    // set the entity ids on the relation
    r->SetFromEntityId(this->GetGraphId());
    r->SetToEntityId(to->GetGraphId());

    // now set the relation id on the from entity chain and the to entity chain

    // from is an out relation
    this->LinkOutRelation(r);

    // to is an in relation
    to->LinkInRelation(r);

    // return the relation
    return r;
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
//  EntityCollection::EntityCollection() {
//  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
//  EntityCollection::~EntityCollection() {
//  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
//  void EntityCollection::Add(Entity *entity) {
//    this->m_entities.push_back(entity);
//  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
//  Entity* EntityCollection::operator[](std::size_t index){
//    if(index < this->m_entities.size() && index >= 0) {
//      return this->m_entities[index];
//    }
//    return 0x0;
//  }



}

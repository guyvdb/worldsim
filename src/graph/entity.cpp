#include "entity.h"

#include <iostream>
#include <cstdio>
#include <transaction.h>
#include <relation.h>


namespace graph {

  /*graph::Storeable *EntityFactoryFunc(type::gid id, type::ByteBuffer*buffer) {

    // if buffer is null
  }*/

  Storeable * Entity::FactoryFunc(type::gid id, type::ByteBuffer *buffer) {
    if(id == type::NullGraphId) {
      return new Entity();
    } else if(buffer == 0x0) {
      return new Entity(id);
    } else {
      return new Entity(id, buffer);
    }
  }

  type::FactoryFunc Entity::GetFactoryFunc() {
    return Entity::FactoryFunc;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Entity::Entity() : StoreableWithProps(type::NullGraphId, Storeable::EntitySize) {
    this->Load(ROOT_OUT_REL_ID_OFFSET, type::NullGraphId);
    this->Load(ROOT_IN_REL_ID_OFFSET, type::NullGraphId);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Entity::Entity(type::gid id) : StoreableWithProps(id, Storeable::EntitySize) {
    this->Load(ROOT_OUT_REL_ID_OFFSET, type::NullGraphId);
    this->Load(ROOT_IN_REL_ID_OFFSET, type::NullGraphId);
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  // The entity takes ownership of the buffer
  Entity::Entity(type::gid id, graph::type::ByteBuffer *buffer) : StoreableWithProps(id, buffer) {
    // Load of in and out rel id is within buffer
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Entity::Entity(type::gid id, type::gid attribid, type::gid outRelId, type::gid inRelid) : StoreableWithProps(id, Storeable::EntitySize) {
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
  type::gid Entity::GetRootOutRelationId() {
    return this->GetUint32(ROOT_OUT_REL_ID_OFFSET);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Entity::SetRootOutRelId(type::gid id) {
    this->Update(ROOT_OUT_REL_ID_OFFSET, id);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  type::gid Entity::GetRootInRelationId() {
    return this->GetUint32(ROOT_IN_REL_ID_OFFSET);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Entity::SetRootInRelationId(type::gid id) {
    this->Update(ROOT_IN_REL_ID_OFFSET, id);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  std::vector<Relation*> Entity::InRelations() {
    std::vector<Relation*> v;
    if(this->IsReadable()) {
      if(this->GetRootInRelationId() != type::NullGraphId) {
        Relation *r = this->Tx()->FindRelation(this->GetRootInRelationId());
        if(r != 0x0) {
          v.push_back(r);
          while(r->GetNextInRelationId() != type::NullGraphId) {
            r = this->Tx()->FindRelation(r->GetNextInRelationId());
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
      if(this->GetRootOutRelationId() != type::NullGraphId) {
        Relation *r = this->Tx()->FindRelation(this->GetRootOutRelationId());
        if(r != 0x0) {
          v.push_back(r);
          while(r->GetNextOutRelationId() != type::NullGraphId) {
            r = this->Tx()->FindRelation(r->GetNextOutRelationId());
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
  bool Entity::LinkInRelation(Relation *r) {
    if(!this->IsWriteable()) {
      std::cout << "[ENTITY] Error - cannot link relation. Entity is not writeable." << std::endl;
      return false;
    }

    if(this->GetRootInRelationId() == type::NullGraphId) {
      // link on root
      this->SetRootInRelationId(r->GetGraphId());
      return true;
    } else {
      // link at end of chain
      std::vector<Relation*> v = this->InRelations();
      // should be the last one in v
      Relation *c = v.back();
      if(c->GetNextInRelationId() == type::NullGraphId) {
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

    if(this->GetRootOutRelationId() == type::NullGraphId) {
      // link on root
      this->SetRootOutRelId(r->GetGraphId());
      return true;
    } else {
      // link at end of chain
      std::vector<Relation*> v = this->OutRelations();
      // should be the last one in v
      Relation *c = v.back();
      if(c->GetNextOutRelationId() == type::NullGraphId) {
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
  Relation* Entity::CreateRelation(Entity *to, type::gid type) {
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
}

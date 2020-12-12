#include "relation.h"

#include <iostream>
#include <entity.h>

namespace graph {



  Relation::Relation(type::gid id) : StoreableWithAttributes(id, Storeable::RelationSize) {
    //std::cout << "Create Relation(gid id)\n";
    this->Load(FROM_ENTITY_ID_OFFSET, type::NullGraphId);
    this->Load(TO_ENTITY_ID_OFFSET, type::NullGraphId);
    this->Load(NEXT_OUT_REL_ID_OFFSET, type::NullGraphId);
    this->Load(PREV_OUT_REL_ID_OFFSET, type::NullGraphId);
    this->Load(NEXT_IN_REL_ID_OFFSET, type::NullGraphId);
    this->Load(PREV_IN_REL_ID_OFFSET, type::NullGraphId);
    this->m_fromEntity = 0x0;
    this->m_toEntity = 0x0;

//    std::cout << "NEW REL(" << id << ") -- ";
//    std::cout << "FROM_ENTITY_ID_OFFSET=" << this->GetUint32(FROM_ENTITY_ID_OFFSET);
//    std::cout << ", TO_ENTITY_ID_OFFSET=" << this->GetUint32(TO_ENTITY_ID_OFFSET);
//    std::cout << ", NEXT_OUT_REL_ID_OFFSET=" << this->GetUint32(NEXT_OUT_REL_ID_OFFSET);
//    std::cout << ", PREV_OUT_REL_ID_OFFSET=" << this->GetUint32(PREV_OUT_REL_ID_OFFSET);
//    std::cout << ", NEXT_IN_REL_ID_OFFSET=" << this->GetUint32(NEXT_IN_REL_ID_OFFSET);
//    std::cout << ", PREV_IN_REL_ID_OFFSET=" << this->GetUint32(PREV_IN_REL_ID_OFFSET);
//    std::cout << std::endl;


  }

  Relation::Relation(type::gid id, ByteBuffer *buffer) : StoreableWithAttributes(id, buffer) {
//    std::cout << "Create Relation(gid id, ByteBuffer *buffer)\n";
//    std::cout << "NEW REL(" << id << ") -- ";
//    std::cout << "FROM_ENTITY_ID_OFFSET=" << this->GetUint32(FROM_ENTITY_ID_OFFSET);
//    std::cout << ", TO_ENTITY_ID_OFFSET=" << this->GetUint32(TO_ENTITY_ID_OFFSET);
//    std::cout << ", NEXT_OUT_REL_ID_OFFSET=" << this->GetUint32(NEXT_OUT_REL_ID_OFFSET);
//    std::cout << ", PREV_OUT_REL_ID_OFFSET=" << this->GetUint32(PREV_OUT_REL_ID_OFFSET);
//    std::cout << ", NEXT_IN_REL_ID_OFFSET=" << this->GetUint32(NEXT_IN_REL_ID_OFFSET);
//    std::cout << ", PREV_IN_REL_ID_OFFSET=" << this->GetUint32(PREV_IN_REL_ID_OFFSET);
//    std::cout << std::endl;

    // values loaded from buffer
    this->m_fromEntity = 0x0;
    this->m_toEntity = 0x0;
  }


  Relation::~Relation() {
  }

  Entity *Relation::From() {
    if(!this->IsReadable()) {
      std::cout << "[RELATION] Error - relation is not readable." << std::endl;
      return 0x0;
    }

    if(this->m_fromEntity == 0x0) {
      this->m_fromEntity = this->Tx()->FindEntity(this->GetFromEntityId());
      if(this->m_fromEntity != 0x0) {
        this->m_fromEntity->SetTransaction(this->Tx());
      }
    }
    return this->m_fromEntity;
  }

  Entity *Relation::To() {
    if(!this->IsReadable()) {
      std::cout << "[RELATION] Error - relation is not readable." << std::endl;
      return 0x0;
    }

    if(this->m_toEntity == 0x0) {
      this->m_toEntity = this->Tx()->FindEntity(this->GetToEntityId());
      if(this->m_toEntity != 0x0) {
        this->m_toEntity->SetTransaction(this->Tx());
      }
    }
    return this->m_toEntity;
  }

  type::gid Relation::GetFromEntityId() {
    return this->GetUint32(FROM_ENTITY_ID_OFFSET);
  }

  void Relation::SetFromEntityId(type::gid id) {
    this->Update(FROM_ENTITY_ID_OFFSET, id);
  }

  type::gid Relation::GetToEntityId() {
    return this->GetUint32(TO_ENTITY_ID_OFFSET);
  }

  void Relation::SetToEntityId(type::gid id) {
    this->Update(TO_ENTITY_ID_OFFSET, id);
  }

  type::gid Relation::GetNextOutRelationId() {
    return this->GetUint32(NEXT_OUT_REL_ID_OFFSET);
  }

  void Relation::SetNextOutRelationId(type::gid id) {
    this->Update(NEXT_OUT_REL_ID_OFFSET, id);
  }

  type::gid Relation::GetPrevOutRelationId() {
    return this->GetUint32(PREV_OUT_REL_ID_OFFSET);
  }

  void Relation::SetPrevOutRelationId(type::gid id) {
    this->Update(PREV_OUT_REL_ID_OFFSET, id);
  }

  type::gid Relation::GetNextInRelationId() {
    return this->GetUint32(NEXT_IN_REL_ID_OFFSET);
  }

  void Relation::SetNextInRelationId(type::gid id) {
    this->Update(NEXT_IN_REL_ID_OFFSET, id);
  }

  type::gid Relation::GetPrevInRelationId() {
    return this->GetUint32(PREV_IN_REL_ID_OFFSET);
  }

  void Relation::SetPrevInRelationId(type::gid id) {
    this->Update(PREV_IN_REL_ID_OFFSET,id);
  }




}

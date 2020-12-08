#include "relation.h"

#include <iostream>
#include <entity.h>

namespace graph {



  Relation::Relation(gid id) : StoreableWithAttributes(id, Storeable::RelationSize) {
    //std::cout << "Create Relation(gid id)\n";
    this->Load(FROM_ENTITY_ID_OFFSET, NullGraphId);
    this->Load(TO_ENTITY_ID_OFFSET, NullGraphId);
    this->Load(NEXT_OUT_REL_ID_OFFSET, NullGraphId);
    this->Load(PREV_OUT_REL_ID_OFFSET, NullGraphId);
    this->Load(NEXT_IN_REL_ID_OFFSET, NullGraphId);
    this->Load(PREV_IN_REL_ID_OFFSET, NullGraphId);
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

  Relation::Relation(gid id, ByteBuffer *buffer) : StoreableWithAttributes(id, buffer) {
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
      this->m_fromEntity = this->Tx()->FindEntityById(this->GetFromEntityId());
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
      this->m_toEntity = this->Tx()->FindEntityById(this->GetToEntityId());
      if(this->m_toEntity != 0x0) {
        this->m_toEntity->SetTransaction(this->Tx());
      }
    }
    return this->m_toEntity;
  }

  gid Relation::GetFromEntityId() {
    return this->GetUint32(FROM_ENTITY_ID_OFFSET);
  }

  void Relation::SetFromEntityId(gid id) {
    this->Update(FROM_ENTITY_ID_OFFSET, id);
  }

  gid Relation::GetToEntityId() {
    return this->GetUint32(TO_ENTITY_ID_OFFSET);
  }

  void Relation::SetToEntityId(gid id) {
    this->Update(TO_ENTITY_ID_OFFSET, id);
  }

  gid Relation::GetNextOutRelationId() {
    return this->GetUint32(NEXT_OUT_REL_ID_OFFSET);
  }

  void Relation::SetNextOutRelationId(gid id) {
    this->Update(NEXT_OUT_REL_ID_OFFSET, id);
  }

  gid Relation::GetPrevOutRelationId() {
    return this->GetUint32(PREV_OUT_REL_ID_OFFSET);
  }

  void Relation::SetPrevOutRelationId(gid id) {
    this->Update(PREV_OUT_REL_ID_OFFSET, id);
  }

  gid Relation::GetNextInRelationId() {
    return this->GetUint32(NEXT_IN_REL_ID_OFFSET);
  }

  void Relation::SetNextInRelationId(gid id) {
    this->Update(NEXT_IN_REL_ID_OFFSET, id);
  }

  gid Relation::GetPrevInRelationId() {
    return this->GetUint32(PREV_IN_REL_ID_OFFSET);
  }

  void Relation::SetPrevInRelationId(gid id) {
    this->Update(PREV_IN_REL_ID_OFFSET,id);
  }




}

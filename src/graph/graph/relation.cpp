#include "relation.h"

#include <iostream>

namespace graph {



  Relation::Relation(gid id) : StoreableWithAttributes(id, Storeable::RelationSize) {
    this->Load(FROM_ENTITY_ID_OFFSET, InvalidGraphId);
    this->Load(TO_ENTITY_ID_OFFSET, InvalidGraphId);
    this->Load(NEXT_FROM_IN_REL_ID_OFFSET, InvalidGraphId);
    this->Load(NEXT_FROM_OUT_REL_ID_OFFSET, InvalidGraphId);
    this->Load(NEXT_TO_IN_REL_ID_OFFSET, InvalidGraphId);
    this->Load(NEXT_TO_OUT_REL_ID_OFFSET, InvalidGraphId);
  }

  Relation::Relation(gid id, ByteBuffer *buffer) : StoreableWithAttributes(id, buffer) {
    // values loaded from buffer
  }


  Relation::~Relation() {
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

  gid Relation::GetNextFromInRelationId() {
    return this->GetUint32(NEXT_FROM_IN_REL_ID_OFFSET);
  }

  void Relation::SetNextFromInRelationId(gid id) {
    this->Update(NEXT_FROM_IN_REL_ID_OFFSET, id);
  }

  gid Relation::GetNextFromOutRelationId() {
    return this->GetUint32(NEXT_FROM_OUT_REL_ID_OFFSET);
  }

  void Relation::SetNextFromOutRelationId(gid id) {
    this->Update(NEXT_FROM_OUT_REL_ID_OFFSET, id);
  }

  gid Relation::GetNextToInRelationId() {
    return this->GetUint32(NEXT_TO_IN_REL_ID_OFFSET);
  }

  void Relation::SetNextToInRelationId(gid id) {
    this->Update(NEXT_TO_IN_REL_ID_OFFSET, id);
  }

  gid Relation::GetNextToOutRelationId() {
    return this->GetUint32(NEXT_TO_OUT_REL_ID_OFFSET);
  }

  void Relation::SetNextToOutRelationId(gid id) {
    this->Update(NEXT_TO_OUT_REL_ID_OFFSET,id);
  }



  RelationCollection::RelationCollection() {

  }

  RelationCollection::~RelationCollection() {

  }

  void RelationCollection::Add(Relation *relation) {
    this->m_relations.push_back(relation);
  }

  Relation* RelationCollection::operator[](std::size_t index) {
    if(index < this->m_relations.size() && index >=0) {
      return this->m_relations[index];
    }
    return 0x0;
  }

}

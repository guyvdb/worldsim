#include "storeable.h"

#include <transaction.h>

namespace graph {

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Storeable::Storeable(gid id, std::size_t size) : m_graphid(id), m_transaction(0x0), m_dirty(false) {
    this->m_buffer = new ByteBuffer(size);
    for(std::size_t i =0; i < size; i++) {
      this->m_buffer->Append(0x0);
    }
  }


  /* ----------------------------------------------------------------------------------------
   * The storeable takes ownership of the buffer and will free it on destruction
   * --------------------------------------------------------------------------------------*/
  Storeable::Storeable(gid id, ByteBuffer *buffer) : m_graphid(id), m_buffer(buffer), m_transaction(0x0), m_dirty(false) {
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Storeable::~Storeable() {
    delete this->m_buffer;
  }

  std::string Storeable::ConceptToString(Concept concept) {
    switch(concept) {
    case NotStoreableConcept:
      return "NotStoreable";
    case EntityConcept:
      return "Entity";
    case RelationConcept:
      return "Relation";
    case AttributeBucketConcept:
      return "AttributeBucket";
    case AttributeDefinitionConcept:
      return "AttributeDefinition";
    case IdConcept:
      return "Id";
    case TestConcept:
      return "Test";
    default:
      return "Unknown";
    }
  }

  std::string Storeable::GetConceptString() {
    return Storeable::ConceptToString(this->GetConcept());
  }

  /*
   *         CNotStoreable,
        CEntity,
        CRelation,
        CAttributeBucket,
        CAttributeDefinition,
        CId,
        CTest
        */

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Storeable::Set(stateid action, int offset, std::uint8_t value) {
    if(action == StateUpdated) {
      this->m_dirty = true;
    }
    this->m_buffer->Set(offset, value);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Storeable::Set(stateid action, int offset, std::uint16_t value) {
    if(action == StateUpdated) {
      this->m_dirty = true;
    }
    this->m_buffer->Set(offset, value);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Storeable::Set(stateid action, int offset, std::uint32_t value) {
    if(action == StateUpdated) {
      this->m_dirty = true;
    }
    this->m_buffer->Set(offset, value);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Storeable::Set(stateid action, int offset, std::uint64_t value) {
    if(action == StateUpdated) {
      this->m_dirty = true;
    }
    this->m_buffer->Set(offset, value);
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  uint8_t Storeable::GetUint8(int offset) {
    return this->m_buffer->GetUint8(offset);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  uint16_t Storeable::GetUint16(int offset) {
    return this->m_buffer->GetUint16(offset);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  uint32_t Storeable::GetUint32(int offset) {
    return this->m_buffer->GetUint32(offset);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  uint64_t Storeable::GetUint64(int offset) {
    return this->m_buffer->GetUint64(offset);
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  std::uint8_t Storeable::GetFlag() {
    return this->GetUint8(FLAG_OFFSET);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Storeable::SetFlag(std::uint8_t flag) {
    this->Load(FLAG_OFFSET, flag);
  }



  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Transaction* Storeable::GetTransaction() {
    return this->m_transaction;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Storeable::SetTransaction(Transaction *tx) {
    this->m_transaction = tx;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Storeable::IsReadable() {
    if(this->m_transaction == 0x0 || !this->m_transaction->IsReadable()) {
      return false;
    }

    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Storeable::IsWriteable() {
    if(!this->IsReadable() || !this->m_transaction->IsWriteable()) {
      return false;
    }
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  StoreableWithType::StoreableWithType(gid id, std::size_t size) : Storeable(id, size) {

  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  StoreableWithType::StoreableWithType(gid id, ByteBuffer *buffer) : Storeable(id, buffer) {

  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  StoreableWithType::~StoreableWithType() {

  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  gid StoreableWithType::GetTypeId(){
    return this->GetUint32(TYPEID_OFFSET);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void StoreableWithType::SetTypeId(gid type) {
    this->Update(TYPEID_OFFSET, type);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  StoreableWithAttributes::StoreableWithAttributes(gid id, std::size_t size) : StoreableWithType(id, size) {
    this->Load(ROOT_ATTRIB_BUCKET_ID_OFFSET, NullGraphId);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  StoreableWithAttributes::StoreableWithAttributes(gid id, ByteBuffer *buffer) : StoreableWithType(id,buffer) {
    // root attrib bucket id will be loaded via buffer
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  StoreableWithAttributes::~StoreableWithAttributes() {

  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  gid StoreableWithAttributes::GetRootAttributesBucketId() {
    return this->GetUint32(ROOT_ATTRIB_BUCKET_ID_OFFSET);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void StoreableWithAttributes::SetRootAttributesBucketId(gid id){
    this->Update(ROOT_ATTRIB_BUCKET_ID_OFFSET, id);
  }






}

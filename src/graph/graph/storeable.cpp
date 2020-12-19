#include "storeable.h"

#include <transaction.h>

namespace graph {

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Storeable::Storeable(type::gid id, std::size_t size) : m_graphid(id), m_transaction(0x0), m_dirty(false) {
    this->m_buffer = new graph::type::ByteBuffer(size);
    for(std::size_t i =0; i < size; i++) {
      this->m_buffer->Append(0x0);
    }
  }


  /* ----------------------------------------------------------------------------------------
   * The storeable takes ownership of the buffer and will free it on destruction
   * --------------------------------------------------------------------------------------*/
  Storeable::Storeable(type::gid id, graph::type::ByteBuffer *buffer) : m_graphid(id), m_buffer(buffer), m_transaction(0x0), m_dirty(false) {
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Storeable::~Storeable() {
    delete this->m_buffer;
  }

  std::string Storeable::ConceptToString(Concept concept) {
    switch(concept) {
    case NoConcept:
      return "NotStoreable";
    case EntityConcept:
      return "Entity";
    case RelationConcept:
      return "Relation";
    case ClassConcept:
      return "Class";
    case InheritanceConcept:
      return "Inheritance";
    case PropDefConcept:
      return "PropDef";
    case IdConcept:
      return "Id";
    case TestConcept:
      return "Test";
    default:
      return "Unknown";
    }
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  std::string Storeable::GetConceptString() {
    return Storeable::ConceptToString(this->GetConcept());
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Storeable::Set(type::stateid action, int offset, std::uint8_t value) {
    if(action == StateUpdated) {
      this->m_dirty = true;
    }
    this->m_buffer->Set(offset, value);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Storeable::Set(type::stateid action, int offset, std::uint16_t value) {
    if(action == StateUpdated) {
      this->m_dirty = true;
    }
    this->m_buffer->Set(offset, value);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Storeable::Set(type::stateid action, int offset, std::uint32_t value) {
    if(action == StateUpdated) {
      this->m_dirty = true;
    }
    this->m_buffer->Set(offset, value);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Storeable::Set(type::stateid action, int offset, std::uint64_t value) {
    if(action == StateUpdated) {
      this->m_dirty = true;
    }
    this->m_buffer->Set(offset, value);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Storeable::Set(type::stateid action, int offset, type::FixedString value) {
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
  type::FixedString Storeable::GetFixedString(int offset) {
    return this->m_buffer->GetFixedString(offset);
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
  StoreableWithClass::StoreableWithClass(type::gid id, std::size_t size) : Storeable(id, size) {

  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  StoreableWithClass::StoreableWithClass(type::gid id, graph::type::ByteBuffer *buffer) : Storeable(id, buffer) {

  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  StoreableWithClass::~StoreableWithClass() {

  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  type::gid StoreableWithClass::GetClassId(){
    return this->GetUint32(CLASS_ID_OFFSET);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void StoreableWithClass::SetClassId(type::gid type) {
    this->Update(CLASS_ID_OFFSET, type);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  StoreableWithAttributes::StoreableWithAttributes(type::gid id, std::size_t size) : StoreableWithClass(id, size) {
    this->Load(ROOT_ATTRIB_BUCKET_ID_OFFSET, type::NullGraphId);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  StoreableWithAttributes::StoreableWithAttributes(type::gid id, graph::type::ByteBuffer *buffer) : StoreableWithClass(id,buffer) {
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
  type::gid StoreableWithAttributes::GetRootAttributesBucketId() {
    return this->GetUint32(ROOT_ATTRIB_BUCKET_ID_OFFSET);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void StoreableWithAttributes::SetRootAttributesBucketId(type::gid id){
    this->Update(ROOT_ATTRIB_BUCKET_ID_OFFSET, id);
  }






}

#include "type.h"
#include <tx/transaction.h>

namespace graph {

  namespace type {

    Type::Type(gid id) : Storeable(id, Storeable::TypeSize) {
      this->Load(ROOT_SUBCLASS_ID_OFFSET, NullGraphId);
      this->Load(SUPERCLASS_ID_OFFSET, NullGraphId);
    }

    Type::Type(gid id, ByteBuffer *buffer) : Storeable(id, buffer) {

    }


    Storeable::Concept Type::GetTargetConcept() {
      return (Storeable::Concept)this->m_buffer->GetUint8(CONCEPT_ID_OFFSET);
    }

    void Type::SetTargetConcept(Storeable::Concept concept) {
      // concept can only be entity or relation
      if(concept != Storeable::Concept::EntityConcept && concept != Storeable::Concept::RelationConcept) {
        std::cout << "[TYPE] Error - dynamic types can only be set on entity or relation." << std::endl;
        return;
      }
      this->m_buffer->Set(CONCEPT_ID_OFFSET, (std::uint8_t)concept);
    }

    std::string Type::GetName() {
      FixedString s(this->m_buffer,NAME_OFFSET);
      return s.GetValue();
    }

    void Type::SetName(std::string name) {
      FixedString s(name);
      s.WriteValue(this->m_buffer, NAME_OFFSET);
    }

    gid Type::GetSuperclassId() {
      return (gid)this->m_buffer->GetUint32(SUPERCLASS_ID_OFFSET);
    }

    void Type::SetSuperclassId(gid id) {
      this->m_buffer->Set(SUPERCLASS_ID_OFFSET, (std::uint32_t)id);
    }

    gid Type::GetRootSubclassId() {
      return (gid)this->m_buffer->GetUint32(ROOT_SUBCLASS_ID_OFFSET);
    }

    void Type::SetRootSubclassId(gid id) {
      this->m_buffer->Set(ROOT_SUBCLASS_ID_OFFSET, (std::uint32_t)id);
    }

    void Type::AddSubclass(Type *subclass) {
      std::cout << "TODO - link heirachy: " << this->GetName() << " -> " << subclass->GetName() << std::endl;
    }

    type::Type *Type::Superclass() {
      if(!this->IsReadable()) {
        std::cout << "[TYPE] Error - type is not readable." << std::endl;
        return 0x0;
      }
      return this->Tx()->FindType(this->GetSuperclassId());
    }
  }
}

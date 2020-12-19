#include "inheritance.h"
#include <class.h>
#include <transaction.h>

namespace graph {

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
    Inheritance::Inheritance(type::gid id) : graph::Storeable(id, Storeable::InheritanceSize) {

      // This is really not needed as the bytebuffer is set to rec size of 0x0 bytes
      /*
      this->Load(SUPERCLASS_ID_OFFSET, type::NullGraphId);
      this->Load(ROOT_SUBCLASS_ID_OFFSET, type::NullGraphId);
      this->Load(SUPERCLASS_NEXT_HEIRACHY_ID_OFFSET, type::NullGraphId);
      this->Load(SUPERCLASS_PREV_HEIRACHY_ID_OFFSET, type::NullGraphId);
      this->Load(SUBCLASS_NEXT_ID_OFFSET, type::NullGraphId);
      this->Load(SUBCLASS_PREV_ID_OFFSET, type::NullGraphId);
      */
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Inheritance::Inheritance(type::gid id, type::ByteBuffer *buffer) : Storeable(id, buffer) {

    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    type::gid Inheritance::GetSuperclassId() {
// return this->GetUint32(ROOT_OUT_REL_ID_OFFSET);
      return this->GetUint32(SUPERCLASS_ID_OFFSET);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void Inheritance::SetSuperclassId(type::gid id) {
      this->Update(SUPERCLASS_ID_OFFSET, id);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    type::gid Inheritance::GetSubclassId() {
      return this->GetUint32(SUBCLASS_ID_OFFSET);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void Inheritance::SetSubclassId(type::gid id) {
      this->Update(SUBCLASS_ID_OFFSET, id);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    type::gid Inheritance::GetNextInheritanceId() {
      return this->GetUint32(NEXT_INHERITANCE_ID_OFFSET);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void Inheritance::SetNextInheritanceId(type::gid id) {
      this->Update(NEXT_INHERITANCE_ID_OFFSET, id);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    type::gid Inheritance::GetPrevInheritanceId() {
      return this->GetUint32(PREV_INHERITANCE_ID_OFFSET);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void Inheritance::SetPrevInheritanceId(type::gid id) {
      this->Update(PREV_INHERITANCE_ID_OFFSET, id);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Class *Inheritance::GetSuperclass() {
      if(!this->IsReadable()) {
        std::cout << "[INHERITANCE] Error - is not readable." << std::endl;
        return 0x0;
      }
      return this->Tx()->FindClass(this->GetSuperclassId());
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Class *Inheritance::GetSubclass() {
      if(!this->IsReadable()) {
        std::cout << "[INHERITANCE] Error - is not readable." << std::endl;
        return 0x0;
      }
      return this->Tx()->FindClass(this->GetSubclassId());
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Inheritance *Inheritance::GetNextInheritance() {
      if(!this->IsReadable()) {
        std::cout << "[INHERITANCE] Error - is not readable." << std::endl;
        return 0x0;
      }

      if(this->GetNextInheritanceId() == type::NullGraphId) {
        return 0x0;
      }

      return this->Tx()->FindInheritance(this->GetNextInheritanceId());
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Inheritance *Inheritance::GetPrevInheritance() {
      if(!this->IsReadable()) {
        std::cout << "[INHERITANCE] Error - is not readable." << std::endl;
        return 0x0;
      }

      if(this->GetPrevInheritanceId() == type::NullGraphId) {
        return 0x0;
      }

      return this->Tx()->FindInheritance(this->GetPrevInheritanceId());
    }


}




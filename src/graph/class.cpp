#include "class.h"
#include <transaction.h>


namespace graph {


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
    Class::Class(type::gid id) : Storeable(id, Storeable::ClassSize) {
      this->Load(ROOT_INHERITANCE_ID_OFFSET, type::NullGraphId);
      this->Load(SUPERCLASS_ID_OFFSET, type::NullGraphId);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Class::Class(type::gid id, type::ByteBuffer *buffer) : Storeable(id, buffer) {

    }


    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Storeable::Concept Class::GetTargetConcept() {
      return (Storeable::Concept)this->GetUint8(CONCEPT_ID_OFFSET);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void Class::SetTargetConcept(Storeable::Concept concept) {
      // concept can only be entity or relation
      if(concept != Storeable::Concept::EntityConcept && concept != Storeable::Concept::RelationConcept) {
        std::cout << "[TYPE] Error - dynamic types can only be set on entity or relation." << std::endl;
        return;
      }
      this->Update(CONCEPT_ID_OFFSET, (std::uint8_t)concept);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    std::string Class::GetName() {
      return this->GetFixedString(NAME_OFFSET).StdString();
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void Class::SetName(std::string name) {
      this->Update(NAME_OFFSET,type::FixedString(name));
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    type::gid Class::GetSuperclassId() {
      return (type::gid)this->GetUint32(SUPERCLASS_ID_OFFSET);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void Class::SetSuperclassId(type::gid id) {
      this->Update(SUPERCLASS_ID_OFFSET, (std::uint32_t)id);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    type::gid Class::GetRootInheritanceId() {
      return (type::gid)this->GetUint32(ROOT_INHERITANCE_ID_OFFSET);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void Class::SetRootInheritanceId(type::gid id) {
      this->Update(ROOT_INHERITANCE_ID_OFFSET, (std::uint32_t)id);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    type::gid Class::GetRootPropDefId() {
      return (type::gid)this->GetUint32(ROOT_PROPDEF_ID_OFFSET);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void Class::SetRootPropDefId(type::gid id) {
      this->Update(ROOT_PROPDEF_ID_OFFSET, (std::uint32_t)id);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Inheritance *Class::AddSubclass(Class *subclass) {
      if(!this->IsWriteable()) {
        std::cout << "[TYPE] Error - class is not writeable." << std::endl;
        return 0x0;
      }

      // we need to create a new inheritance relationship and
      // link it into the chain
      Inheritance *h = this->Tx()->CreateInheritance(this->GetGraphId(), subclass->GetGraphId());
      if(this->GetRootInheritanceId() == type::NullGraphId) {
        this->SetRootInheritanceId(h->GetGraphId());
      } else {
        std::vector<Inheritance*> v = this->GetInheritances();
        Inheritance *last = v.back();
        if(last->GetNextInheritanceId() == type::NullGraphId) {
          last->SetNextInheritanceId(h->GetGraphId());
          h->SetPrevInheritanceId(last->GetGraphId());
        } else {
          std::cout << "[CLASS] Error - failed to link inheritance. Last inheritance does not have next null graph id." << std::endl;
        }
      }
      return h;
    }


    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    PropDef* Class::AddPropDef(type::FixedString name, type::DataType datatype, bool required) {
      if(!this->IsWriteable()) {
        std::cout << "[CLASS] Error - class is not writeable." << std::endl;
        return 0x0;
      }

      PropDef *d = this->Tx()->CreatePropDef();
      d->SetName(name);
      d->SetPropertyDataType(datatype);
      d->SetRequiredFlag(required);
      d->SetClassId(this->GetGraphId());

      if(!this->LinkPropDef(d)) {
        std::cout << "[CLASS] Error - failed to link propdef." << std::endl;
        return 0x0;
      }
      return d;
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool Class::LinkPropDef(PropDef *def) {

      if(!this->IsWriteable()) {
        std::cout << "[CLASS] Error - cannot link propdef. Class is not writeable." << std::endl;
        return false;
      }

      if(this->GetRootPropDefId() == type::NullGraphId) {
        // link on root
        this->SetRootPropDefId(def->GetGraphId());
        return true;
      } else {
        std::vector<PropDef*> defs = this->PropDefs();
        PropDef* last = defs.back();
        if(last->GetNextPropDefId() == type::NullGraphId) {
          last->SetNextPropDefId(def->GetGraphId());
          return true;
        } else {
          std::cout << "[CLASS] Error - the last element  of PropDefs does not have a NULL pointer to the next element." << std::endl;
          return false;
        }
      }
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    std::vector<PropDef*> Class::PropDefs() {
      std::vector<PropDef*> v;
      if(this->IsReadable()) {
        if(this->GetRootPropDefId() != type::NullGraphId) {
          PropDef *d = this->Tx()->FindPropDef(this->GetRootPropDefId());
          if(d != 0x0) {
            v.push_back(d);
            while(d->GetNextPropDefId() != type::NullGraphId) {
              d = this->Tx()->FindPropDef(d->GetNextPropDefId());
              if(d != 0x0) {
                v.push_back(d);
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
    Class *Class::Superclass() {
      if(!this->IsReadable()) {
        std::cout << "[CLASS] Error - class is not readable." << std::endl;
        return 0x0;
      }
      return this->Tx()->FindClass(this->GetSuperclassId());
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    std::vector<Inheritance*> Class::GetInheritances() {
      std::vector<Inheritance*> v;

      //std::cout << "GetInheritances: ";

      if(this->IsReadable()) {
        //std::cout << "readable, root id=" << this->GetRootInheritanceId();
         if(this->GetRootInheritanceId() != type::NullGraphId) {
          // std::cout << ", root id=" << this->GetRootInheritanceId();

           Inheritance *h = this->Tx()->FindInheritance(this->GetRootInheritanceId());
           if(h != 0x0) {
            //std::cout << ", found id=" << h->GetGraphId();
             v.push_back(h);
             while(h->GetNextInheritanceId() != type::NullGraphId) {
               h = this->Tx()->FindInheritance(h->GetNextInheritanceId());
               if(h != 0x0) {
              //   std::cout << ", found id=" << h->GetGraphId();
                 v.push_back(h);
               } else {
                // std::cout << ", finished";
                 break;
               }
             }
           }
         }
      } else {
        std::cout << "[CLASS] Error - failed to load inheritances. Class is not readable." << std::endl;
      }

      //std::cout << std::endl;
      return v;
    }



}

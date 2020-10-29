#ifndef STOREABLE_H
#define STOREABLE_H

#include <bytebuffer.h>
#include <iostream>

namespace graph {




  // Any object that is stored in one of the data stores must inherit from Storable
  class Storeable {
    public:
      static const std::size_t EntitySize = 16;
      static const std::size_t EntityTypeSize = 16;
      static const std::size_t PropertySize = 16;
      static const std::size_t PropertyTypeSize = 16;
      static const std::size_t RelationSize = 16;
      static const std::size_t RelationTypeSize = 16;

      // The storable type id's
      enum Type : stid {
        NotStorable,
        Entity,
        EntityType,
        EntityProperty,
        Relation,
        RelationType,
        RelationProperty,
        PropertyType,
        Id
      };

      Storeable(gid id);
      virtual ~Storeable();
      virtual const char * Data() = 0;
      virtual Type ObjectType() = 0;
      virtual void SetFlag(const char flag) = 0;
      virtual char GetFlag() = 0;
      gid GetId() {return m_id;}
      void SetId(gid value) { this->m_id = value; }
    protected:
      void SetUInt8(std::uint8_t value, char *data);
      void SetUInt16(std::uint16_t value, char *data);
      void SetUInt32(std::uint32_t value, char *data);
      std::uint8_t GetUInt8(const char *data);
      std::uint16_t GetUInt16(const char *data);
      std::uint32_t GetUInt32(const char *data);

      gid m_id;
  };



  // Abstract class for creating object. Each type of Storeable object
  // should define a factory that creates objects of its type
  class ObjectFactory {
    public:
      virtual ~ObjectFactory() {}
      virtual Storeable *CreateObject(gid id, const char *data) = 0;
      virtual Storeable *CreateEmptyObject() = 0;
      virtual bool CanCreateObjects() = 0;
  };

  class NullObjectFactory : public ObjectFactory {
    public:
      virtual Storeable *CreateObject(gid, const char *) { return 0x0; }
      virtual Storeable *CreateEmptyObject() {return 0x0; }
      virtual bool CanCreateObjects() {return false; }
  };



}

#endif // STOREABLE_H

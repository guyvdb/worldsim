#ifndef STOREABLE_H
#define STOREABLE_H

#include <iostream>
#include <map>
#include <memory>

#include "type/base.h"
#include "type/buffer.h"


namespace graph {

  //namespace tx {
    class Transaction;
  //}



  /*
   * Buffer layout: Storeable
   * |-----------|
   * | Storeable |
   * |-----------|
   * | 0         |
   * | flag      |
   * |-----------|
   */
  class Storeable {
    public:
      static const int FLAG_OFFSET = 0;

      static const std::size_t EntitySize = 18;
      static const std::size_t RelationSize = 34;
      static const std::size_t ClassSize = 48;
      static const std::size_t InheritanceSize = 18;
      static const std::size_t PropertyDefSize = 46;

      // The storable type id's
      enum Concept : type::cid {
        NoConcept,
        EntityConcept,
        RelationConcept,
        ClassConcept,
        InheritanceConcept,
        PropDefConcept,
        IdConcept,
        TestConcept
      };

      // When data is placed into the byte buffer
      // it can be a "load" from disk or and "update"
      // which marks the object dirty
      enum DataState : type::stateid {
        StateLoaded,
        StateUpdated,
        StateCreated,
        StateDeleted
      };

      std::string static ConceptToString(Concept concept);

      Storeable(type::gid id, std::size_t size);
      Storeable(type::gid id,  graph::type::ByteBuffer *buffer);
      virtual ~Storeable();

      // must be implemented by subclasses - Entity, Relation, AttributeBucket, etc....
      virtual Concept GetConcept() = 0;
      std::string GetConceptString();

      bool IsDirty() { return this->m_dirty; }
      void SetDirty(bool value ) { this->m_dirty = value; }

      type::gid GetGraphId() {return m_graphid;}
      void SetGraphId(type::gid value) { this->m_graphid = value; }

      graph::type::ByteBuffer *Buffer() { return this->m_buffer; }

      std::uint8_t GetFlag();
      void SetFlag(std::uint8_t flag);

      Transaction *GetTransaction();
      void SetTransaction(Transaction *tx);

      // Load does not modify the dirty flag
      void Load(int offset, std::uint8_t value) { this->Set(StateLoaded, offset, value); }
      void Load(int offset, std::uint16_t value){ this->Set(StateLoaded, offset, value); }
      void Load(int offset, std::uint32_t value){ this->Set(StateLoaded, offset, value); }
      void Load(int offset, std::uint64_t value){ this->Set(StateLoaded, offset, value); }
      void Load(int offset, type::FixedString value) {this->Set(StateLoaded, offset, value); }
      //void Load(int offset, bool value) { this->Set(StateLoaded, offset, value); }

      // Update sets the dirty flag to true
      void Update(int offset, std::uint8_t value) { this->Set(StateUpdated, offset, value); }
      void Update(int offset, std::uint16_t value) { this->Set(StateUpdated, offset, value); }
      void Update(int offset, std::uint32_t value) { this->Set(StateUpdated, offset, value); }
      void Update(int offset, std::uint64_t value) { this->Set(StateUpdated, offset, value); }
      void Update(int offset, type::FixedString value) {this->Set(StateUpdated, offset, value); }
      //void Update(int offset, bool value) { this->Set(StateUpdated, offset, value); }

      // Set takes an action. If action is update, dirty flag is set true
      void Set(type::stateid action, int offset, std::uint8_t value);
      void Set(type::stateid action, int offset, std::uint16_t value);
      void Set(type::stateid action, int offset, std::uint32_t value);
      void Set(type::stateid action, int offset, std::uint64_t value);
      void Set(type::stateid action, int offset, type::FixedString value);
      //void Set(type::stateid action, int offset, bool value);

      // Get the values
      uint8_t GetUint8(int offset);
      uint16_t GetUint16(int offset);
      uint32_t GetUint32(int offset);
      uint64_t GetUint64(int offset);
      type::FixedString GetFixedString(int offset);
      bool GetBool(int offset);

      // Transaction related
      Transaction* Tx() { return this->m_transaction; }
      bool IsReadable();
      bool IsWriteable();
    protected:
      type::gid m_graphid;
      graph::type::ByteBuffer *m_buffer;
      Transaction *m_transaction;
      bool m_dirty;
  };


  /*
   * Buffer layout: StoreableWithType
   * |-----------|--------------------|
   * | Storeable | StoreableWithClass |
   * |-----------|--------------------|
   * | 0         | 1 2 3 4            |
   * | flag      | class id           |
   * |-----------|--------------------|
   */
  class StoreableWithClass : public Storeable {
    public:
      const static int CLASS_ID_OFFSET = 1;

      StoreableWithClass(type::gid id, std::size_t size);
      StoreableWithClass(type::gid id, graph::type::ByteBuffer *buffer);
      ~StoreableWithClass();

      type::gid GetClassId();
      void SetClassId(type::gid type);

  };

  /*
   * Buffer layout: StoreableWithAttributes
   * |-----------|--------------------|----------------------|
   * | Storeable | StoreableWithClass | StoreableWithAttrib  |
   * |-----------|--------------------|----------------------|
   * | 0         | 1 2 3 4            | 5 6 7 8              |
   * | flag      | class id           | Root AttribBucket Id |
   * |-----------|--------------------|----------------------|
   */
  class StoreableWithAttributes : public StoreableWithClass {
    public:
      const static int ROOT_ATTRIB_BUCKET_ID_OFFSET =  5;


      StoreableWithAttributes(type::gid id, std::size_t size);
      StoreableWithAttributes(type::gid id, graph::type::ByteBuffer *buf);
      virtual ~StoreableWithAttributes();

      type::gid GetRootAttributesBucketId();
      void SetRootAttributesBucketId(type::gid id);
  };


  struct StoreableId {
      type::gid Id;
      Storeable::Concept Type;
  };






}

#endif // STOREABLE_H

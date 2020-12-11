#ifndef STOREABLE_H
#define STOREABLE_H

#include <iostream>
#include <map>
#include <memory>
#include <type/base.h>
#include <buffer.h>


namespace graph {

  namespace tx {
    class Transaction;
  }



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
      static const std::size_t AttributeBucketSize = 16;
      static const std::size_t AttributeDefinitionSize = 32;
      static const std::size_t TypeSize = 74;
      static const std::size_t HeirarchSize = 26;
      static const std::size_t BucketSize = 64;
      static const std::size_t PropertyDefSize = 82;

      // The storable type id's
      enum Concept : type::cid {
        NotStoreableConcept,
        EntityConcept,
        RelationConcept,
        TypeConcept,
        HeirachyConcept,
        PropertyDefinitionConcept,
        AttributeBucketConcept,
        AttributeDefinitionConcept,
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
      Storeable(type::gid id,  ByteBuffer *buffer);
      virtual ~Storeable();

      // must be implemented by subclasses - Entity, Relation, AttributeBucket, etc....
      virtual Concept GetConcept() = 0;
      std::string GetConceptString();

      bool IsDirty() { return this->m_dirty; }
      void SetDirty(bool value ) { this->m_dirty = value; }

      type::gid GetGraphId() {return m_graphid;}
      void SetGraphId(type::gid value) { this->m_graphid = value; }

      ByteBuffer *Buffer() { return this->m_buffer; }

      std::uint8_t GetFlag();
      void SetFlag(std::uint8_t flag);

      tx::Transaction *GetTransaction();
      void SetTransaction(tx::Transaction *tx);

      // Load does not modify the dirty flag
      void Load(int offset, std::uint8_t value) { this->Set(StateLoaded, offset, value); }
      void Load(int offset, std::uint16_t value){ this->Set(StateLoaded, offset, value); }
      void Load(int offset, std::uint32_t value){ this->Set(StateLoaded, offset, value); }
      void Load(int offset, std::uint64_t value){ this->Set(StateLoaded, offset, value); }

      // Update sets the dirty flag to true
      void Update(int offset, std::uint8_t value){ this->Set(StateUpdated, offset, value); }
      void Update(int offset, std::uint16_t value){ this->Set(StateUpdated, offset, value); }
      void Update(int offset, std::uint32_t value){ this->Set(StateUpdated, offset, value); }
      void Update(int offset, std::uint64_t value){ this->Set(StateUpdated, offset, value); }

      // Set takes an action. If action is update, dirty flag is set true
      void Set(type::stateid action, int offset, std::uint8_t value);
      void Set(type::stateid action, int offset, std::uint16_t value);
      void Set(type::stateid action, int offset, std::uint32_t value);
      void Set(type::stateid action, int offset, std::uint64_t value);

      // Get the values
      uint8_t GetUint8(int offset);
      uint16_t GetUint16(int offset);
      uint32_t GetUint32(int offset);
      uint64_t GetUint64(int offset);

      // Transaction related
      tx::Transaction* Tx() { return this->m_transaction; }
      bool IsReadable();
      bool IsWriteable();
    protected:
      type::gid m_graphid;
      ByteBuffer *m_buffer;
      tx::Transaction *m_transaction;
      bool m_dirty;
  };


  /*
   * Buffer layout: StoreableWithType
   * |-----------|-------------------|
   * | Storeable | StoreableWithType |
   * |-----------|-------------------|
   * | 0         | 1 2 3 4           |
   * | flag      | typeid            |
   * |-----------|-------------------|
   */
  class StoreableWithType : public Storeable {
    public:
      const static int TYPEID_OFFSET = 1;

      StoreableWithType(type::gid id, std::size_t size);
      StoreableWithType(type::gid id, ByteBuffer *buffer);
      ~StoreableWithType();

      type::gid GetTypeId();
      void SetTypeId(type::gid type);

  };

  /*
   * Buffer layout: StoreableWithAttributes
   * |-----------|-------------------|----------------------|
   * | Storeable | StoreableWithType | StoreableWithAttrib  |
   * |-----------|-------------------|----------------------|
   * | 0         | 1 2 3 4           | 5 6 7 8              |
   * | flag      | typeid            | Root AttribBucket Id |
   * |-----------|-------------------|----------------------|
   */
  class StoreableWithAttributes : public StoreableWithType {
    public:
      const static int ROOT_ATTRIB_BUCKET_ID_OFFSET =  5;


      StoreableWithAttributes(type::gid id, std::size_t size);
      StoreableWithAttributes(type::gid id, ByteBuffer *buf);
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

#ifndef PROPDEF_H
#define PROPDEF_H

#include <storeable.h>
#include <type/base.h>
#include <type/buffer.h>

namespace graph {


  /*
   * Buffer layout: PropDef
   * |-----------|--------------------------------------------------------------------|
   * | Storeable | PropDef                                                            |
   * |-----------|----------|--------|-----------|-------|----------|-----------------|
   * | 0         | 1 2 3 4  | 5..37  | 38        | 39    | 40       | 41 42 43 44     |
   * | flag      | Class Id | Name   | Scalar Id | Array | Required | Next PropDef Id |
   * |-----------|----------|--------|-----------|-------|----------|-----------------|
   *
   * Name is a short string
   * PropDef padded to 46 bytes long
   */

  class PropDef : public Storeable {
    public:
      const static int CLASS_ID_OFFSET = 1;
      const static int NAME_OFFSET = 5;
      const static int SCALAR_ID_OFFSET = 38;
      const static int ARRAY_FLAG_OFFSET = 39;
      const static int REQUIRED_FLAG_OFFSET = 40;
      const static int NEXT_PROPDEF_IF_OFFSET = 41;

      PropDef(type::gid id) : Storeable(id, Storeable::PropertyDefSize) {}
      PropDef(type::gid id, type::ByteBuffer *buffer) : Storeable(id, buffer) {}

      type::gid GetClassId() { return this->GetUint32(CLASS_ID_OFFSET); }
      void SetClassId(type::gid id) { this->Update(CLASS_ID_OFFSET, id); }
      std::string GetName() { return this->GetFixedString(NAME_OFFSET).StdString(); }
      void SetName(std::string value) { this->Update(NAME_OFFSET, type::FixedString(value)); }
      type::DataType GetPropertyDataType() { return (type::DataType)this->GetUint8(SCALAR_ID_OFFSET); }
      void SetPropertyDataType(type::DataType type) { this->Update(SCALAR_ID_OFFSET, type); }
      bool GetArrayFlag() { return this->GetBool(ARRAY_FLAG_OFFSET); }
      //void SetArrayFlag(bool value) { this->SetBool(ARRAY_FLAG_OFFSET, value); }
      bool GetRequiredFlag() { return this->GetBool(REQUIRED_FLAG_OFFSET); }
      //void SetRequiredFlag(bool value) { this->SetBool(REQUIRED_FLAG_OFFSET, value); }
      type::gid GetNextPropDefId() { return this->GetUint32(NEXT_PROPDEF_IF_OFFSET); }
      void SetNextPropDefId(type::gid id) { this->Update(NEXT_PROPDEF_IF_OFFSET, id); }

  };



}


#endif // PROPDEF_H

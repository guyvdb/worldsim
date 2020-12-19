#ifndef PROPERTY_H
#define PROPERTY_H

#include "../storeable.h"
#include "buffer.h"
#include "base.h"

namespace graph {
  namespace type {

   /*
    * Buffer layout: PropertyDef
    * |-----------|-----------------------------------------------------------------------------------|
    * | Storeable | PropertyDef                                                                       |
    * |-----------|---------|---------|------|---------|----------|-----------------|-----------------|
    * | 0         | 1 2 3 4 | 5..70   | 71   | 72      | 73       | 74 75 76 77     | 78 79 80 81     |
    * | flag      | type id | name    | Dtid | ordinal | Required | Next ProfDef Id | Prev PropDef Id |
    * |-----------|---------|---------|------|---------|----------|-----------------|-----------------|
    *
    * Name is a short string
    * PropertyDef padded to 82 bytes long
    */

    // This is the definition of a property. The property can be an entity property
    // or a relation property. That is determined by the type definition.
    class PropertyDef : public Storeable {
      public:

        const static int TYPE_ID_OFFSET = 1;
        const static int NAME_OFFSET = 5;
        const static int DATATYPE_ID_OFFSET = 71;
        const static int ORDINAL_OFFSET = 72;
        const static int REQUIRED_OFFSET = 73;
        const static int NEXT_PROPERTY_DEF_ID_OFFSET = 74;
        const static int PREV_PROPERTY_DEF_ID_OFFSET = 78;

        PropertyDef(gid id);
        PropertyDef(gid id, ByteBuffer *buffer);
        ~PropertyDef();

        gid GetTypeId();
        void SetTypeId(gid id);
        FixedString GetName();
        void SetName(FixedString name);
        stid GetDataTypeId();
        void SetDataTypeId(stid id);
        std::uint8_t GetOrdinal();
        void SetOrdinal(std::uint8_t ordinal);
        bool GetRequired();
        void SetReuired(bool value);
        gid GetNextPropertyDefId();
        void SetNextPropertyDefId(gid id);
        gid GetPrevPropertyDefId();
        void SetPrevPropertyDefId(gid id);


        virtual Storeable::Concept GetConcept() { return Storeable::PropDefConcept; }
    };
  }
}


#endif // PROPERTY_H

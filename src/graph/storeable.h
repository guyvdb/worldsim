#ifndef STOREABLE_H
#define STOREABLE_H

#include <bytebuffer.h>

namespace graph {


  // Any object that is stored in one of the data stores must inherit from Storable
  class Storeable {


    public:

      static const std::size_t ThingSize = 16;
      static const std::size_t ThingTypeSize = 16;
      static const std::size_t PropertySize = 16;
      static const std::size_t PropertyTypeSize = 16;
      static const std::size_t RelationSize = 16;
      static const std::size_t RelationTypeSize = 16;

      // The storable type id's
      enum Type : stid {
        NotStorable,
        Thing,
        ThingType,
        ThingProperty,
        Relation,
        RelationType,
        RelationProperty,
        PropertyType,
        Id
      };

      Storeable();
      virtual ~Storeable();
      virtual ByteBuffer *Buffer() = 0;
  };

}

#endif // STOREABLE_H

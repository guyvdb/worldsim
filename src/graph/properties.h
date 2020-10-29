#ifndef PROPERTIES_H
#define PROPERTIES_H




/*
 * Properties can either be entity properties or relation properties.
 * This class provides convinient methods for grouping all the properties
 * of the entity for access
 */

namespace graph {


  class PropertyCollection {
    public:
      PropertyCollection();
     // Property *[](name);
    //  Property *Get(const char *name);

  };

  class EntityPropertyCollection : public PropertyCollection {

  };

  class RelationPropertyCollection : public PropertyCollection {

  };

}

#endif // PROPERTIES_H

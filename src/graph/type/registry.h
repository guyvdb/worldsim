#ifndef REGISTRY_H
#define REGISTRY_H


namespace graph {

  class Entity;
  class Relation;

  namespace type {

    // We can define a type derived from base class entity or relation
    // or one of the subclasses of the two.

    // We can define the properties of our new type

    // We can provide a factory for the generation of our new type


    class ObjectFactory {

    };


    // The registry allows applications to register
    // pre-defined types with the type system
    class Registry {
      public:
        Registry();
    };


  }
}


#endif // REGISTRY_H

#include "planet.h"


namespace nature {
  namespace planet {

    graph::Storeable* PlanetFactory(graph::type::gid id, graph::type::ByteBuffer *buffer) {
      if(id == graph::type::NullGraphId && buffer == 0x0) {
        return new Planet();
      } else if (buffer == 0x0) {
        return new Planet(id);
      } else {
        return  new Planet(id, buffer);
      }
    }

    graph::type::ClassDefinition PlanetDefinition() {
      return graph::type::ClassDefinition {
        .Name="Planet",
        .SuperclassName="Entity",
        .Concept=graph::Storeable::Concept::ClassConcept,
        .Factory=&PlanetFactory,
        .Properties=std::vector<graph::type::ClassProperty>{
            graph::type::ClassProperty{
              .Name="Name",
              .DataType=graph::type::DataType::LongString,
              .Required=true,
            },
            graph::type::ClassProperty {
              .Name="Circumference",
              .DataType=graph::type::DataType::Float,
              .Required=true,
            }
        }
      };
    }


    /*
    struct ClassProperty {
        std::string Name;
        type::PropertyDataType DataType;
        bool Array;
        bool Required;
    };
    */



  }
}

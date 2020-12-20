#ifndef FOOD_H
#define FOOD_H

#include <graph/entity.h>
#include <graph/type/base.h>
#include <graph/type/buffer.h>

// We need to build a culnary core for our culture
//

/*

    <- culture - nature ->

              Raw
            /     \
        Cooked -  Rotten

*/

// A civilised culute values cooked -> raw -> rotten
//

//        value/cost
//     <- high - low ->
//      protein - carb

namespace culture {
  namespace food {
    class Food : public graph::Entity {


        /*
         *       Entity();
      Entity(type::gid id);
      Entity(type::gid id, graph::type::ByteBuffer *buffer);
      */
    };
  }
}


#endif // FOOD_H

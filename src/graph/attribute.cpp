#include "attribute.h"

#include <tx/transaction.h>


namespace graph {



  AttributeBucket::AttributeBucket(type::gid id) : Storeable(id, Storeable::AttributeBucketSize) {
    this->SetNextBucketId(type::NullGraphId);
  }

  AttributeBucket::AttributeBucket(type::gid id, ByteBuffer *buffer) : Storeable(id, buffer) {

  }

  void AttributeBucket::SetNextBucketId(type::gid id){

  }

  type::gid AttributeBucket::GetNextBucketId() {

  }


  AttributeBucket* AttributeBucket::NextBucket() {

  }


  AttributeDefinition::AttributeDefinition(type::gid id) : Storeable(id, Storeable::AttributeDefinitionSize) {

  }

  AttributeDefinition::AttributeDefinition(type::gid id, ByteBuffer *buffer) : Storeable(id, buffer) {

  }


  AttributeCollection::AttributeCollection(Transaction *tx, StoreableWithAttributes *storeable) :
    m_transaction(tx), m_storeable(storeable) {

  }

  AttributeCollection::~AttributeCollection() {

  }

}

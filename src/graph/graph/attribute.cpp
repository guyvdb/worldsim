#include "attribute.h"

#include <transaction.h>


namespace graph {



  AttributeBucket::AttributeBucket(gid id) : Storeable(id, Storeable::AttributeBucketSize) {
    this->SetNextBucketId(NullGraphId);
  }

  AttributeBucket::AttributeBucket(gid id, ByteBuffer *buffer) : Storeable(id, buffer) {

  }

  void AttributeBucket::SetNextBucketId(gid id){

  }

  gid AttributeBucket::GetNextBucketId() {

  }


  AttributeBucket* AttributeBucket::NextBucket() {

  }


  AttributeDefinition::AttributeDefinition(gid id) : Storeable(id, Storeable::AttributeDefinitionSize) {

  }

  AttributeDefinition::AttributeDefinition(gid id, ByteBuffer *buffer) : Storeable(id, buffer) {

  }


  AttributeCollection::AttributeCollection(Transaction *tx, StoreableWithAttributes *storeable) :
    m_transaction(tx), m_storeable(storeable) {

  }

  AttributeCollection::~AttributeCollection() {

  }

}

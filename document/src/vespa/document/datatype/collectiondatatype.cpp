// Copyright Yahoo. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.

#include "collectiondatatype.h"
#include <vespa/document/util/stringutil.h>

namespace document {

IMPLEMENT_IDENTIFIABLE_ABSTRACT(CollectionDataType, DataType);

CollectionDataType::CollectionDataType(const CollectionDataType& other)
    : DataType(other),
      _nestedType(other._nestedType)
{
}

CollectionDataType&
CollectionDataType::operator=(const CollectionDataType& other)
{
    if (this != &other) {
        DataType::operator=(other);
        _nestedType = other._nestedType;
    }
    return *this;
}

CollectionDataType::CollectionDataType(vespalib::stringref name,
                                       const DataType& nestedType)
    : DataType(name),
      _nestedType(&nestedType) {
}

CollectionDataType::CollectionDataType(vespalib::stringref name,
                                       const DataType& nestedType,
                                       int32_t id)
    : DataType(name, id),
      _nestedType(&nestedType) {
}

CollectionDataType::~CollectionDataType() = default;

bool
CollectionDataType::operator==(const DataType& other) const
{
    if (!DataType::operator==(other)) return false;
    const CollectionDataType * o = other.cast_collection();
    return o && *_nestedType == *o->_nestedType;
}

} // document

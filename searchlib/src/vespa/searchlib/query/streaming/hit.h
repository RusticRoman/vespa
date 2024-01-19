// Copyright Vespa.ai. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.
#pragma once

#include <cstdint>
#include <vector>

namespace search::streaming {

class Hit
{
public:
    Hit(uint32_t pos_, uint32_t field_id_, uint32_t elemId_, int32_t weight_) noexcept
        : _position(pos_ | (field_id_<<24)),
          _elemId(elemId_),
          _weight(weight_)
    { }
    int32_t weight() const { return _weight; }
    uint32_t pos()     const { return _position; }
    uint32_t wordpos() const { return _position & 0xffffff; }
    uint32_t field_id() const noexcept { return _position >> 24; }
    uint32_t elemId() const { return _elemId; }
private:
    uint32_t _position;
    uint32_t _elemId;
    int32_t  _weight;
};

using HitList = std::vector<Hit>;

}

#pragma once

#ifndef SET_ASSOC_HPP
#define SET_ASSOC_HPP

#include "cache.hpp"

class TwoWaySetAssociative : public Cache
{
public:
    TwoWaySetAssociative();
    ~TwoWaySetAssociative();
    void read(uint32_t address);

private:
    const int ways = 2;
    cacheEntry (*entries)[cacheSize];
};

#endif
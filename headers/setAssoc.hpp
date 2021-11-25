#pragma once

#ifndef SET_ASSOC_HPP
#define SET_ASSOC_HPP

#include "cache.hpp"

class TwoWaySetAssociative : public Cache //inherits from Cache base class
{
public:
    TwoWaySetAssociative();  //definition of the constructor
    ~TwoWaySetAssociative(); //definition of the destructor

    //definition of the read function (overriding the one in the base class)
    //called on every read access to the cache
    void read(uint32_t address);

    //definition of the detailed print function (overriding the one in the base class)
    void detailedPrint();

    //implementation to return the cache type (overriding the one in the base class)
    char *getType() { return "Two Way Set Associative"; };

private:
    //number of ways in the cache
    //hard coded to 2 as the current implementation of LRU will not work for more than two ways
    const int ways = 2;

    cacheEntry (*entries)[cacheSize]; //pointer to the array of cacheEntries
};

#endif
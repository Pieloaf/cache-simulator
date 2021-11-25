#pragma once

#ifndef DIRECT_MAP_HPP
#define DIRECT_MAP_HPP

#include "cache.hpp"

class DirectMap : public Cache //inherits from Cache base class
{
public:
    DirectMap();  //definition of the constructor
    ~DirectMap(); //definition of the destructor

    //definition of the read function (overriding the one in the base class)
    //called on every read access to the cache
    void read(uint32_t address);

    //definition of the detailed print function (overriding the one in the base class)
    void detailedPrint();

    //implementation to return the cache type (overriding the one in the base class)
    char *getType() { return "Direct Map"; };

private:
    cacheEntry *entries; //pointer to the array of cache entries
};

#endif
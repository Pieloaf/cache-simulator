#pragma once

#ifndef FULLY_ASSOC_HPP
#define FULLY_ASSOC_HPP

#include "cache.hpp"
#define fullAssocMask 0xFFFFFFFC //mask to isolate the first 30 bits of the address

class FullyAssociative : public Cache //inherits from Cache base class
{
public:
    FullyAssociative();  //definition of the constructor
    ~FullyAssociative(); //definition of the destructor

    //definition of the read function (overriding the one in the base class)
    //called on every read access to the cache
    void read(uint32_t address);

    //definition of the detailed print function (overriding the one in the base class)
    void detailedPrint();

    //implementation to return the cache type (overriding the one in the base class)
    char *getType() { return "Fully Associative"; };

    //definition of the cacheEntry struct (overriding the one in the base class)
    struct cacheEntry
    {
        bool invalid; // valid flag (deteremines if the cache entry is valid or not)
        uint32_t tag; // 32 bit tag (to accomodate for 30 bit tags)
        char data[4]; // array of 4 bytes (representing a cache line)
    };

private:
    cacheEntry *entries; //pointer to the array of cache entries
    int cIndex;          //index of the next empty cache entry
};

#endif
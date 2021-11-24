#pragma once

#ifndef CACHE_HPP
#define CACHE_HPP

#include <stdint.h>
#include <stdio.h>

#define cacheSize 16384     //cache size of 16KB (14 bit set number)
#define setMask 0x0000FFFC  //mask to isolate 14 bits of the address following the first 2 bits
#define wordMask 0x00000003 //mask to isolate the first 2 bits of the address
#define tagMask 0xFFFF0000  //mask to isolate the last 16 bits of the address

class Cache
{
public:
    Cache();    //definition of the constructor
    ~Cache(){}; //implementation of the destructor

    //definition of the parse address function
    void parseAddr(uint32_t address, uint16_t *tag, uint16_t *set, uint8_t *word);

    //definition of the purely virtual read function (to be implemented in the derived classes)
    virtual void read(uint32_t address) = 0;

    void incHit();  //definition of the function to increment the hit counter
    void incMiss(); //definition of the function to increment the miss counter
    int getHit();   //definition of the function to return the hit counter
    int getMiss();  //definition of the function to return the miss counter

    //definiiton of the cacheEntry struct (represents a single entry in the cache, to be used in the cache array)
    struct cacheEntry
    {
        bool LRU;     // least recently used flag (used for LRU replacement policy, this only works for 2-way set associative caches)
        bool invalid; // valid flag (deteremines if the cache entry is valid or not)
        uint16_t tag; // 16 bit tag (to accomodate for 14 bit tags)
        char data[4]; // array of 4 bytes (representing a cache line)
    };

private:
    //definition hit and miss counters
    int hit, miss;
};

#endif
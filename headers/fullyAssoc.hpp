#pragma once

#ifndef FULLY_ASSOC_HPP
#define FULLY_ASSOC_HPP

#include <vector>
#include "cache.hpp"
#define fullAssocMask 0xFFFFFFFC

struct cacheEntry
{
    bool LRU; // Least Recently Used
    bool invalid; // valid bit
    uint32_t tag; // 32 bit tag because 
    char data[4]; // array of 4 bytes - cache line
};


class FullyAssociative : public Cache
{
public:
    FullyAssociative();
    ~FullyAssociative();

    void read(uint32_t address);
    
private:
    cacheEntry *entries;
    int cIndex;
};

#endif
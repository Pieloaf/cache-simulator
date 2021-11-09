#pragma once

#ifndef CACHE_HPP
#define CACHE_HPP

#include <stdint.h>
#include <stdio.h>

#define cacheSize 16384
#define setMask 0x0000FFFC
#define wordMask 0x00000003
#define tagMask 0xFFFF0000

struct cacheEntry
{
    bool LRU;
    bool invalid;
    uint16_t tag;
    char data[4];
};

class Cache
{
public:
    Cache(int way);
    ~Cache();

    void read(uint32_t address, uint16_t *tag, uint16_t *set, uint8_t *word);

    void incHit();
    void incMiss();
    int getHit();
    int getMiss();

    cacheEntry getEntry(uint8_t way, uint32_t set);

    void setTag(uint8_t way, uint32_t set, uint32_t tag);
    void setInvalid(uint8_t way, uint32_t set, bool state);
    void setLRU(uint8_t way, uint32_t set, bool state);

private:
    int hit, miss;
    cacheEntry (*entries)[cacheSize];
};

#endif
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
    bool LRU; // Least Recently Used
    bool invalid; // valid bit
    uint16_t tag; // 16 bit tag
    char data[4]; // array of 4 bytes - cache line
};

class Cache
{
public:
    Cache();
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
};

#endif
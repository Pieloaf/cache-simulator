#include "../headers/cache.hpp"

Cache::Cache(int way)
{
    entries = new cacheEntry[way][cacheSize];
    hit = 0;
    miss = 0;
    // Initialize the cache
    for (int w = 0; w < way; w++)
    {
        for (int i = 0; i < cacheSize; i++)
        {
            entries[w][i].LRU = true;
            entries[w][i].invalid = true;
        }
    }
}

Cache::~Cache()
{
    delete[] entries;
}

void Cache::read(uint32_t address, uint16_t *tag, uint16_t *set, uint8_t *word)
{
    *tag = (address & tagMask) >> 16;
    *set = (address & setMask) >> 2;
    *word = (address & wordMask);
    printf("Address: %x | "
           "Tag: %x | "
           "Set: %x | "
           "Byte Number: %x\n",
           address, *tag, *set, *word);
}

void Cache::incHit()
{
    hit++;
    printf("Hit: %d\n", hit);
}
void Cache::incMiss()
{
    miss++;
    printf("Miss: %d\n", miss);
}
int Cache::getHit() { return hit; }
int Cache::getMiss() { return miss; }

cacheEntry Cache::getEntry(uint8_t way, uint32_t set) { return entries[way][set]; }

void Cache::setTag(uint8_t way, uint32_t set, uint32_t tag)
{
    entries[way][set].tag = tag;
}
void Cache::setInvalid(uint8_t way, uint32_t set, bool state)
{
    entries[way][set].invalid = state;
}
void Cache::setLRU(uint8_t way, uint32_t set, bool state)
{
    entries[way][set].LRU = state;
}
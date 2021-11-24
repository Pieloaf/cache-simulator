#include "../headers/directMap.hpp"

DirectMap::DirectMap(){
    entries = new cacheEntry[cacheSize];
    for (int i = 0; i < cacheSize; i++)
    {
        entries[i].invalid = true;
    }
};

DirectMap::~DirectMap(){
    delete[] entries;
}

void DirectMap::read(uint32_t address)
{
    uint16_t tag, set;
    uint8_t word;
    Cache::read(address, &tag, &set, &word);
    // Check if the cache is valid
    if (!entries[set].invalid && entries[set].tag == tag)
    {
        incHit();
    }
    else
    {
        incMiss();
        // Update the cache
        entries[set].tag = tag;
        entries[set].invalid = false;
    }
}

#include "../headers/directMap.hpp"

DirectMap::DirectMap() : Cache(1){};

void DirectMap::read(uint32_t address)
{
    uint16_t tag, set;
    uint8_t word;
    Cache::read(address, &tag, &set, &word);
    // Check if the cache is valid
    if (!getEntry((uint8_t)0, set).invalid && getEntry(0, set).tag == tag)
    {
        incHit();
    }
    else
    {
        incMiss();
        // Update the cache
        setTag(0, set, tag);
        setInvalid(0, set, false);
    }
}

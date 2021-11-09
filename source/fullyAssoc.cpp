#include "../headers/fullyAssoc.hpp"

FullyAssociative::FullyAssociative() : Cache(1) {}

void FullyAssociative::read(uint32_t address)
{

    uint32_t tag = (address & fullAssocMask) >> 16;
    uint8_t word = address & wordMask;
    // Check if the cache is valid
    for (int i = 0; i < cacheSize; i++)
    {
        if (getEntry(0, i).tag == tag)
        {
            if (!getEntry(0, i).invalid)
            {
                incHit();
            }
            else
            {
                incMiss();
                //read from memory here
                setInvalid(0, i, false);
            }
            break;
        }
        else if (i == cacheSize - 1)
        {
            incMiss();
            for (int j = 0; j < cacheSize; j++)
            {
                if (getEntry(0, j).LRU)
                {
                    setTag(0, j, tag);
                    //read from memory here
                    setInvalid(0, j, false);
                    break;
                }
            }
        }
    }
}
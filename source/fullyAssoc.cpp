#include "../headers/fullyAssoc.hpp"

FullyAssociative::FullyAssociative()
{
    cIndex = 0;
    entries = new cacheEntry[cacheSize];
    for (int i = 0; i < cacheSize; i++)
    {
        entries[i].invalid = true;
    }
}

FullyAssociative::~FullyAssociative()
{
    delete[] entries;
}

void FullyAssociative::read(uint32_t address)
{
    bool found = false;
    uint32_t tag = (address & fullAssocMask) >> 2;
    uint8_t word = address & wordMask;
    // Check if the cache is valid
    for (int i = 0; i < cacheSize; i++)
    {
        if (entries[i].tag == tag)
        {
            if (!entries[i].invalid)
            {
                incHit();
            }
            else
            {
                incMiss();
                //read from memory here
                entries[i].invalid = false;
            }
            found = true;
            break;
        }
    }
    if (!found)
    {
        incMiss();
        //read from memory here
        //fifo replacement
        if (!cIndex == cacheSize - 1)
        {
            entries[cIndex].tag = tag;
            entries[cIndex].invalid = false;
            cIndex++;
        }
        else
        {
            for (int i = 0; i < cacheSize; i++)
            {
                if (i == cacheSize - 1)
                {
                    entries[i].tag = tag;
                    entries[i].invalid = false;
                }
                else
                {
                    entries[i] = entries[i + 1];
                }
            }
        }
    }
}
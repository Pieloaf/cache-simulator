#include "../headers/setAssoc.hpp"

TwoWaySetAssociative::TwoWaySetAssociative(){
    entries = new cacheEntry[ways][cacheSize];
    // Initialize the cache
    for (int w = 0; w < ways; w++)
    {
        for (int i = 0; i < cacheSize; i++)
        {
            entries[w][i].LRU = true;
            entries[w][i].invalid = true;
        }
    }
};

TwoWaySetAssociative::~TwoWaySetAssociative()
{
    delete[] entries;
}

void TwoWaySetAssociative::read(uint32_t address)
{
    uint16_t tag, set;
    uint8_t word;
    Cache::read(address, &tag, &set, &word);
    // Check if the cache is valid
    for (int i = 0; i < ways; i++)
    {
        if (entries[i][set].tag == tag)
        {
            if (!entries[i][set].invalid)
            {
                incHit();
            }
            else
            {
                incMiss();
            }
            //if LRU, update the LRU
            if (entries[i][set].LRU)
            {
                for (int k = 0; k < ways; k++)
                {
                    entries[k][set].LRU = !getEntry(k, set).LRU;
                }
            }
            break;
        }
        else if (i == ways - 1)
        {
            incMiss();

            for (int j = 0; j < ways; j++)
            {
                if (entries[j][set].LRU)
                {
                    entries[j][set].tag = tag;;
                    entries[j][set].invalid =  false;
                    entries[j][set].LRU = false;
                    entries[!j][set].LRU = true;
                    break;
                }
            }
        }
    }
}
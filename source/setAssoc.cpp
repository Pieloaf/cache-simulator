#include "../headers/setAssoc.hpp"

TwoWaySetAssociative::TwoWaySetAssociative() : ways(2), Cache(2){};

void TwoWaySetAssociative::read(uint32_t address)
{
    uint16_t tag, set;
    uint8_t word;
    Cache::read(address, &tag, &set, &word);
    // Check if the cache is valid
    for (int i = 0; i < ways; i++)
    {
        printf("Checking way %d\n", i);
        if (!getEntry(i, set).invalid && getEntry(i, set).tag == tag)
        {
            incHit();
            //if LRU, update the LRU
            if (getEntry(i, set).LRU)
            {
                for (int k = 0; k < ways; k++)
                {
                    setLRU(k, set, !getEntry(k, set).LRU);
                }
            }
            break;
        }
        else if (i == ways - 1)
        {
            incMiss();

            for (int j = 0; j < ways; j++)
            {
                printf("way %d lru state: %d\n", j, getEntry(j, set).LRU);
                if (getEntry(j, set).LRU)
                {
                    printf("LRU way %d\n", j);
                    setTag(j, set, tag);
                    setInvalid(j, set, false);
                    setLRU(j, set, false);
                    setLRU(!j, set, true);
                    break;
                }
            }
        }
    }
}
#include "../headers/cache.hpp"

Cache::Cache()
{
    hit = 0;
    miss = 0;
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
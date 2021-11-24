#include "../headers/cache.hpp"

//implementation of the overridden default constructor
Cache::Cache()
{
    hit = 0;  //initialize hit count to 0
    miss = 0; //initialize miss count to 0
}

//implementation of the parse address function
void Cache::parseAddr(uint32_t address, uint16_t *tag, uint16_t *set, uint8_t *word)
{
    *tag = (address & tagMask) >> 16; //extract the tag from the address
    *set = (address & setMask) >> 2;  //extract the set from the address
    *word = (address & wordMask);     //extract the word from the address

    //print the breakdown of the address in hexadecimal format
    printf("Address: %x | "
           "Tag: %x | "
           "Set: %x | "
           "Byte Number: %x\n",
           address, *tag, *set, *word);
}

//implementation of the increment hit function
void Cache::incHit()
{
    hit++; //increment the hit counter
    //on each hit, print the new hit count
    printf("Hit: %d\n", hit);
}
void Cache::incMiss()
{
    miss++; //increment the miss counter
    //on each miss, print the new miss count
    printf("Miss: %d\n", miss);
}
int Cache::getHit() { return hit; }   //return the hit counter
int Cache::getMiss() { return miss; } //return the miss counter
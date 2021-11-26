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
    *tag = address >> 16;            //extract the tag from the address
    *set = (address & setMask) >> 2; //extract the set from the address
    *word = (address & wordMask);    //extract the word from the address

    //print the breakdown of the address in hexadecimal format
    printf("Address: %x | Tag: %x | Set: %x | Byte Number: %x\n",
           address, *tag, *set, *word);
}

//implementation of the increment hit function
void Cache::incHit()
{
    hit++; //increment the hit counter

    //print the result of the read operation
    printReadResult((char *)"Hit");
}

//implementation of the increment miss function
void Cache::incMiss()
{
    miss++; //increment the miss counter

    //print the result of the read operation
    printReadResult((char *)"Miss");
}

int Cache::getHit() { return hit; }   //return the hit counter
int Cache::getMiss() { return miss; } //return the miss counter

//implementation of the function to print the result of a read operation
void Cache::printReadResult(char *result)
{
    //print the result of the read operation along with the hit and miss counters
    printf("Cache %s!\n"
           "Hits: %d | Misses: %d\n",
           result, hit, miss);
}
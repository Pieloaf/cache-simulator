// FormalElement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

#define cacheSize 65386
#define setMask 0x0000FFFC
#define wordMask 0x00000003
#define tagMask 0xFFFF0000

struct cacheEntry
{
    bool LRU;
    bool invalid;
    uint16_t tag;
    char bytes[4];
};

class cache
{
public:
    cache()
    {
        entries = new cacheEntry[cacheSize];
        hit = 0;
        miss = 0;
    }
    ~cache()
    {
        delete entries;
    }
    int getHit()
    {
        return hit;
    }
    int getMiss()
    {
        return miss;
    }
    int readAddr(uint16_t tag, uint16_t set, uint8_t word)
    {
        for (int i = 0; i < cacheSize; i++){
            if (entries[i].tag == tag && entries[i].invalid){
                // entries[i]
            }
        }
    }
    cacheEntry *entries;

private:
    int hit, miss;
};

int main()
{
    cache directM;
    //init invalid to true
    for (int i = 0; i < cacheSize; i++)
    {
        directM.entries[i].invalid = true;
    }

    std::ifstream cpuAddr;
    cpuAddr.open("CPUaddr.txt");
    uint32_t addr;

    while (cpuAddr >> std::hex >> addr)
    {
        uint16_t tag = (addr & tagMask) >> 16;
        uint16_t set = (addr & setMask) >> 2;
        uint8_t word = (addr & wordMask);
    };

    return 0;
}
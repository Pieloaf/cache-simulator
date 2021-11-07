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
    char data[4];
};

class Cache
{
public:
    Cache(int size)
    {
        entries = new cacheEntry[size];
        hit = 0;
        miss = 0;
        // Initialize the cache
        for (int i = 0; i < size; i++)
        {
            entries[i].LRU = false;
            entries[i].invalid = true;
        }
    }
    ~Cache()
    {
        delete entries;
    }
    void incHit() { hit++; }
    void incMiss() { miss++; }
    int getHit() { return hit; }
    int getMiss() { return miss; }

    cacheEntry getEntry(uint32_t set) { return entries[set]; }
    void setTag(uint32_t set, uint32_t tag)
    {
        entries[set].tag = tag;
    }
    void toggleInvalid(uint32_t set)
    {
        entries[set].invalid = !entries[set].invalid;
    }
    void toggleLRU(uint32_t set)
    {
        entries[set].LRU = !entries[set].LRU;
    }

private:
    int hit, miss;
    cacheEntry *entries;
};

class DirectMapCache : public Cache
{
public:
    DirectMapCache() : Cache(16384){};

    void read(uint32_t address)
    {
        uint16_t tag = (address & tagMask) >> 16;
        uint16_t set = (address & setMask) >> 2;
        uint8_t word = (address & wordMask);
        printf("Read: %x\n", address);
        printf("Tag: %x\n", tag);
        printf("Set: %x\n", set);
        printf("Byte Number: %x\n", word);
        // Check if the cache is valid
        if (!getEntry(set).invalid && getEntry(set).tag == tag)
        {
            incHit();
        }
        else
        {
            incMiss();
            // Update the cache
            setTag(set, tag);
            toggleInvalid(set);
            toggleLRU(set);
        }
    }
};

main()
{
    DirectMapCache directMap;

    std::ifstream cpuAddr;
    cpuAddr.open("CPUaddr.txt");
    uint32_t addr;

    while (cpuAddr >> std::hex >> addr)
    {
        directMap.read(addr);
    };
    std::cout << directMap.getHit() << std::endl;
    std::cout << directMap.getMiss() << std::endl;

    return 0;
}
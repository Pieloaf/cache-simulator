#include <fstream>
#include <sstream>
#include <iostream>

#define cacheSize 65386
#define setMask 0x0000FFFC
#define wordMask 0x00000003
#define tagMask 0xFFFF0000
#define fullAssocMask 0xFFFFFFFC

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

    void read(uint32_t address, uint16_t *tag, uint16_t *set, uint8_t *word)
    {
        *tag = (address & tagMask) >> 16;
        *set = (address & setMask) >> 2;
        *word = (address & wordMask);
        printf("Address: %x\n"
               "Tag: %x\n"
               "Set: %x\n"
               "Byte Number: %x\n"
               "------------\n",
               address, *tag, *set, *word);
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
    void setInvalid(uint32_t set, bool state)
    {
        entries[set].invalid = state;
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
        uint16_t tag, set;
        uint8_t word;
        Cache::read(address, &tag, &set, &word);
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
            setInvalid(set, false);
            // toggleLRU(set);
        }
    }
};

class FullyAssociativeCache : public Cache
{
public:
    FullyAssociativeCache() : Cache(16384){};

    void read(uint32_t address)
    {

        uint32_t tag = (address & fullAssocMask) >> 16;
        uint8_t word = address & wordMask;
        // Check if the cache is valid
        for (int i = 0; i < cacheSize; i++)
        {
            if (getEntry(i).tag == tag)
            {
                if (!getEntry(i).invalid)
                {
                    incHit();
                }
                else
                {
                    incMiss();
                    //read from memory here
                    setInvalid(i, false);
                }
                break;
            }
            else if (i == cacheSize - 1)
            {
                incMiss();
                for (int j = 0; j < cacheSize; j++)
                {
                    if (getEntry(j).LRU)
                    {
                        setTag(j, tag);
                        setInvalid(j, false);
                        break;
                    }
                }
            }
        }
    }
};

class SetAssociativeCache : public Cache
{
public:
    SetAssociativeCache() : Cache(16384){};

    void read(uint32_t address)
    {
        uint16_t tag, set;
        uint8_t word;
        Cache::read(address, &tag, &set, &word);
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
            setInvalid(set, false);
            // toggleLRU(set);
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
    std::cout << "Hits:" << directMap.getHit() << std::endl;
    std::cout << "Misses: " << directMap.getMiss() << std::endl;

    return 0;
}
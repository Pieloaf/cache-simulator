#include "../headers/directMap.hpp"

//implementation of the overridden default constructor
DirectMap::DirectMap()
{
    // Initialize the cache
    entries = new cacheEntry[cacheSize];
    for (int i = 0; i < cacheSize; i++)
    {
        entries[i].invalid = true; //set all entries to invalid
    }
};

//implementation of the overridden default destructor
DirectMap::~DirectMap()
{
    //Delete the cache
    //delete needs to be used as the cache entries are dynamically allocated
    delete[] entries;
}

//implementation of the read function (overriding the one in the base class)
//called on every read access to the cache
void DirectMap::read(uint32_t address)
{
    uint16_t tag, set; //defining 16 bit ints for the tag and set
    uint8_t word;      //defining a byte for the word

    //calling parse address from base class to extract the tag, set, and word
    parseAddr(address, &tag, &set, &word);

    //check if the cache entry is valid and the tag matches
    if (!entries[set].invalid && entries[set].tag == tag)
    {
        incHit(); //increment the hit count
    }
    //if either the tag doesnt match or the entry is invalid
    else
    {
        incMiss(); //increment the miss count

        //
        //read from memory
        //
        //write the new data from memory to the cache
        //
        //entries[set].data[word] = data from memory
        //

        //update the cache entry with the new data from memory
        entries[set].tag = tag;       //update the entry's tag
        entries[set].invalid = false; //set the entry to valid
    }
}

//implementation of the detailed print function (overriding the one in the base class)
void DirectMap::detailedPrint()
{
    //caclulating number of bytes per line
    int bpl = (sizeof(entries[0].data) / sizeof(entries[0].data[0]));

    //print cache details
    printf("Direct Map Cache\n"
           "=================\n"
           "Cache Size: %dkB\n"
           "Line Size: %dB\n"
           "# of Lines: %d\n"
           "# of Sets: %d\n\n",
           (cacheSize * bpl) / 1024, //calculate cache size and convert to kb
           bpl,                      //bytes per line
           cacheSize,                //number of lines
           cacheSize);               //number of sets
}

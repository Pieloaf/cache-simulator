#include "../headers/setAssoc.hpp"

//implementation of the overridden default constructor
TwoWaySetAssociative::TwoWaySetAssociative()
{
    //create a multidimensional array of cache entries
    //each dimension represents a way
    entries = new cacheEntry[ways][cacheSize];

    // Initialize the cache etries
    //for each way in the cache
    for (int w = 0; w < ways; w++)
    {
        //for each entry in the way
        for (int i = 0; i < cacheSize; i++)
        {
            entries[w][i].LRU = true;     //set all entries to LRU
            entries[w][i].invalid = true; //set all entries to invalid
        }
    }
};

//implementation of the overridden default destructor
TwoWaySetAssociative::~TwoWaySetAssociative()
{
    //Delete the cache
    //delete needs to be used as the cache entries are dynamically allocated
    delete[] entries;
}

//implementation of the read function (overriding the one in the base class)
//called on every read access to the cache
void TwoWaySetAssociative::read(uint32_t address)
{

    uint16_t tag, set; //defining 16 bit ints for the tag and set
    uint8_t word;      //defining a byte for the word

    //calling parse address from base class to extract the tag, set, and word
    parseAddr(address, &tag, &set, &word);

    //for each way in the cache
    for (int i = 0; i < ways; i++)
    {
        //if tag matches the corresponding entry in either way
        if (entries[i][set].tag == tag)
        {
            //if the entry is valid
            if (!entries[i][set].invalid)
            {
                incHit(); //increment the hit count
            }
            else //if the entry is invalid
            {
                incMiss(); //increment the miss count

                //
                //read from memory
                //
                //write the new data from memory to the cache
                //
                //entries[i][set].data[word] = data from memory

                entries[i][set].invalid = false; //set the entry to valid
            }

            if (entries[i][set].LRU) //if entry is LRU
            {
                //set the entry in current way to MRU
                entries[i][set].LRU = false;
                //set the entry in the other way to LRU
                entries[!i][set].LRU = true;

                //Note: this logic of indexing the other way of the cache with !i only works for 2 way
                //      associative caches and will need to be changed for higher order associations.
                //      However, using a boolean to store the LRU  was a requirement for this assignment
                //      and also only works for 2 way associative caches. As such I have used this limited
                //      logic in indexing the way due to the fact a fundamental design requirement of the
                //      project already limits it to 2 ways associativity.
            }
            break;
        }
        // if the a matching tag is not found in any way
        else if (i == ways - 1)
        {
            incMiss(); //increment the miss count

            //
            // read from memory
            //

            //find the LRU way
            //for each way in the cache
            for (int j = 0; j < ways; j++)
            {
                //if the entry in the current way is LRU
                if (entries[j][set].LRU)
                {
                    //write the new data from memory to the cache
                    //
                    //entries[j][set].data[word] = data from memory
                    //

                    entries[j][set].tag = tag;       //update the entry's tag
                    entries[j][set].invalid = false; //set the entry to valid

                    entries[j][set].LRU = false; //set the entry in current way to MRU
                    entries[!j][set].LRU = true; //set the entry in the other way to LRU

                    //Note: again using the !j to index the other way is not usable for higher order associativity
                    //      but was suitable for this assignment

                    break; //break from the loop to avoid double setting of LRU
                }
            }
        }
    }
}
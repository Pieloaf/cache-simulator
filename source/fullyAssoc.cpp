#include "../headers/fullyAssoc.hpp"

//implementation of the overridden default constructor
FullyAssociative::FullyAssociative()
{
    // initalise cache index to 0
    cIndex = 0;

    // Initialize the cache
    entries = new cacheEntry[cacheSize];
    for (int i = 0; i < cacheSize; i++)
    {
        entries[i].invalid = true; //set all entries to invalid
    }
}

//implementation of the overridden default destructor
FullyAssociative::~FullyAssociative()
{
    //Delete the cache
    //delete needs to be used as the cache entries are dynamically allocated
    delete[] entries;
}

//implementation of the read function (overriding the one in the base class)
//called on every read access to the cache
void FullyAssociative::read(uint32_t address)
{
    bool found = false; //flag to indicate if the address is found in the cache

    uint32_t tag = (address & fullAssocMask) >> 2; //extract the tag from the address
    uint8_t word = address & wordMask;             //extract the word from the address

    // itterate through the cache
    for (int i = 0; i < cacheSize; i++)
    {
        //check if the tag matches an entry in the cache
        if (entries[i].tag == tag)
        {
            //if the entry is valid increment the hit count
            if (!entries[i].invalid)
            {
                incHit();
            }
            else //if the entry is invalid
            {
                incMiss(); //increment the miss count

                //
                //read from memory
                //
                //write the new data from memory to the cache
                //
                //entries[i].data[word] = data from memory
                //

                entries[i].invalid = false; //set the entry to valid
            }
            //set the found flag to true
            found = true;
            //break from itteration through the cache
            break;
        }
    }

    //if loop exits without finding the address
    //i.e. address not found in cache
    if (!found)
    {
        incMiss(); //increment the miss count

        //
        //read from memory
        //

        //Update the cache with the new data from memory
        //fifo replacement policy
        //if the cache is not full
        if (cIndex < cacheSize - 1)
        {
            //
            //write the new data from memory to the cache
            //
            //entries[cIndex].data[word] = data from memory;
            //

            entries[cIndex].tag = tag;       //add the new entry to the next position in the cache
            entries[cIndex].invalid = false; //set the new entry to valid
            cIndex++;                        //increment the cache index
        }
        else //if the cache is full
        {
            //iterate through the cache
            for (int i = 0; i < cacheSize; i++)
            {
                if (!i == cacheSize - 1) //if not the end of the cache
                {
                    entries[i] = entries[i + 1]; //replace the entry with the following entry
                }
                else //on the last entry in the cache
                {

                    //
                    //write the new data from memory to the cache
                    //
                    //entries[i].data[word] = data from memory;
                    //

                    //replace the entry with the new entry
                    entries[i].tag = tag;       //set the tag to the new tag
                    entries[i].invalid = false; //set the entry to valid
                }
            }
        }
    }
}
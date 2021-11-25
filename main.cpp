#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include "./headers/directMap.hpp"
#include "./headers/fullyAssoc.hpp"
#include "./headers/setAssoc.hpp"

//clear function
void clear()
{
//if the OS is windows
#if defined _WIN32
    //call windows system call to clear the screen
    system("cls");

//if the OS is unix based (linux, mac)
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined(__APPLE__)
    //call the unix system call to clear the screen
    system("clear");
#endif
}

void continueProgram()
{

    std::cout << "Press enter to continue..."; //prompt user for input
    //clear the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); //wait for user input
}

//function to test the cache
void testCache(Cache *cache)
{
    clear(); //clear terminal before printing cache stats

    cache->detailedPrint(); //print cache stats

    continueProgram(); //wait for user to press enter to continue

    std::ifstream cpuAddr;       //create an input file stream object
    cpuAddr.open("CPUaddr.txt"); //open the file containing the addresses

    //define a 32 bit unsigned int to hold the addresses
    //and hold a count of the number of reads
    uint32_t addr, readCount = 0;

    while (cpuAddr >> std::hex >> addr) //while the file is not empty read the next address
    {
        cache->read(addr); //pass the address to the caches read function
        readCount++;       //increment the read count

        printf("---------------------\n"); //print a line to seperate the reads
    };

    //after reading all the addresses print the statistics of the read operations
    printf("\nCache Read Statistics\n"
           "=====================\n"
           "Cache Type: %s\n"
           "# Reads: %d\n"
           "Hit Rate: %.2f%%\n"
           "Hits: %d | Misses: %d\n\n",
           cache->getType(),
           readCount,                                       //print the number of reads
           (float)cache->getHit() / (float)readCount * 100, //calculate the hit rate
           cache->getHit(),                                 //print the number of hits
           cache->getMiss());                               //print the number of misses
}

//main function
int main()
{
    //initialize the cache to 0
    int cacheType = 0;

    //while the user has not entered a valid cache type
    while (cacheType < 1 || cacheType > 3)
    {
        clear(); //clear the screen

        //print the menu of cache types
        printf("1. Direct Map\n"
               "2. Two Way Set Associative\n"
               "3. Fully Associative\n"
               "Enter cache type: "); //request user input

        std::cin >> cacheType; //read the user input
        if (std::cin.fail())   //if the input is not a number
        {
            std::cin.clear(); //clear the error flag

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore the input
        }
    }
    //switch statement to test the correct cache type
    switch (cacheType)
    {
    case 1:
        //test the direct map cache
        testCache(new DirectMap());
        break;
    case 2:
        //test the two way set associative cache
        testCache(new TwoWaySetAssociative());
        break;
    case 3:
        //test the fully associative cache
        testCache(new FullyAssociative());
        break;
    default:
        break;
    }

    return 0;
}
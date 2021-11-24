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

//function to test the cache
void testCache(Cache *cache)
{
    std::ifstream cpuAddr;       //create an input file stream object
    cpuAddr.open("CPUaddr.txt"); //open the file containing the addresses
    uint32_t addr;               //define a 32 bit unsigned integer to hold the addresses

    while (cpuAddr >> std::hex >> addr) //while the file is not empty read the next address
    {
        cache->read(addr); //pass the address to the caches read function

        std::cout << "---------------------" << std::endl; //print a line to seperate the reads
    };

    //after reading all the addresses print the number of hits and misses
    std::cout << "Hits:" << cache->getHit() << std::endl;
    std::cout << "Misses: " << cache->getMiss() << std::endl;
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
        std::cout << "1. Direct Map\n2. Two Way Set Associative\n3. Fully Associative\n";
        std::cout << "Enter cache type: "; //request user input

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
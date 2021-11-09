#include <fstream>
#include <sstream>
#include <iostream>
#include "./headers/cache.hpp"
#include "./headers/directMap.hpp"
#include "./headers/fullyAssoc.hpp"
#include "./headers/setAssoc.hpp"

#define cacheSize 16384
#define setMask 0x0000FFFC
#define wordMask 0x00000003
#define tagMask 0xFFFF0000

main()
{
    DirectMap directMap;
    TwoWaySetAssociative twoWaySetAssociative;

    std::ifstream cpuAddr;
    cpuAddr.open("CPUaddr.txt");
    uint32_t addr;

    while (cpuAddr >> std::hex >> addr)
    {
        // directMap.read(addr);
        twoWaySetAssociative.read(addr);
        std::cout << "---------------------" << std::endl;
    };
    std::cout << "Hits:" << twoWaySetAssociative.getHit() << std::endl;
    std::cout << "Misses: " << twoWaySetAssociative.getMiss() << std::endl;

    return 0;
}
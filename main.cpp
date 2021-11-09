#include <fstream>
#include <sstream>
#include <iostream>
#include "./headers/directMap.hpp"
#include "./headers/fullyAssoc.hpp"
#include "./headers/setAssoc.hpp"

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
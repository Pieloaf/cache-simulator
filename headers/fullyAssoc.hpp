#pragma once

#ifndef FULLY_ASSOC_HPP
#define FULLY_ASSOC_HPP

#include <vector>
#include "cache.hpp"
#define fullAssocMask 0xFFFFFFFC

class FullyAssociative : public Cache
{
public:
    FullyAssociative();

    void read(uint32_t address);

private:
    std::vector<cacheEntry> lru;
};

#endif
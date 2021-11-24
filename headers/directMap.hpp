#pragma once

#ifndef DIRECT_MAP_HPP
#define DIRECT_MAP_HPP

#include "cache.hpp"

class DirectMap : public Cache
{
public:
    DirectMap();
    ~DirectMap();

    void read(uint32_t address);

private:
    cacheEntry *entries;
};

#endif
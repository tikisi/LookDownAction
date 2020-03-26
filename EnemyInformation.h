#pragma once
#include <Siv3D.hpp>
#include "Common.h" 

class EnemyInformation {
public:
    const uint32 id;
    const Point pos;
    const com::Direction dir;
    const int frequency;
    const size_t index;

    EnemyInformation(uint32 id, Point pos, com::Direction dir, int frequency, size_t index) : 
        id(id), pos(pos), dir(dir), frequency(frequency), index(index) {}
};

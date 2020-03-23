#pragma once
#include <Siv3D.hpp>

#include "Common.h"

class Attack {
protected:
    Point pos;
    Point drawPos;

public:
    Attack(Point _pos) : pos(_pos) {
        this->drawPos = Point(int((pos.x + 0.25) * com::BLOCK_SIZE),
            int((pos.y + 0.25) * com::BLOCK_SIZE));
    }

    virtual void update() = 0;
    virtual void draw() const;
    Point getPos() const { return this->pos; }
};

class StraightAttack : public Attack {
    using Direction = com::Direction;
private:
    int moveCounter;
    Direction direction;

public:
    StraightAttack(Point pos, Direction direction)
        : Attack(pos), direction(direction) {
        this->moveCounter = 0;
    }

    void update();
};

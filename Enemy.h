#pragma once
#include <Siv3D.hpp>

#include "Common.h"

class MapMediator;

class Enemy {
    using Direction = com::Direction;
protected:
    Point pos;
    Point drawPos;
    Direction dir;
    MapMediator* mapMediator;

public:
    Enemy(Point pos, Direction dir, MapMediator* mapMediator)
        : pos(pos), dir(dir), mapMediator(mapMediator) {}

    virtual void update() = 0;
    virtual void laterUpdate() {};
    virtual void draw() const;
    Point getPos() const { return this->pos; }
};

class RandomRoomba : public Enemy {
    using Direction = com::Direction;
protected:
    const int id = 0;
    int frameCounter;
    int moveCounter;
    Point beforePos;

public:
    RandomRoomba(Point pos, Direction dir, MapMediator* mapChecker)
        : Enemy(pos, dir, mapChecker) {
        this->beforePos = pos;
        this->drawPos = pos * com::BLOCK_SIZE;
        this->frameCounter = 0;
        this->moveCounter = 0;
    }

    void update() override;
    void draw() const override;
    void laterUpdate() override;
};

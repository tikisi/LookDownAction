#pragma once
#include <Siv3D.hpp>

#include "Common.h"
using namespace com;

class MapMediator;

class Player {
private:
    MapMediator* mapMediator;
    Point pos;
    Point drawPos;
    Direction dir;
    int knockBackCounter;
    int moveCounter;  // 0: 移動していない 0以外: 移動中

    static Direction getDirFromKey(const Key &key);
    static Key getMinKey(const Key &a, const Key &b);

public:
    Player(Point pos, Direction dir, MapMediator* mapMediator)
        : pos(pos), dir(dir), mapMediator(mapMediator) {
        this->moveCounter = 0;
        this->drawPos = pos * BLOCK_SIZE;
    };

    void update();

    void laterUpdate();  // 当たり判定後の更新

    void draw() const;

    Point getPos() const { return this->pos; }

    void setKnockBack();
};

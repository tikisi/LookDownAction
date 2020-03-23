#pragma once
#include <Siv3D.hpp>

#include "Common.h"
using namespace common;

class MapMediator;

class Player {
 private:
  MapMediator *mapMediator;
  Point pos;
  Point drawPos;
  Point nextPos;
  Direction dir;
  int knockBackCounter;
  int moveCounter;  // 0: ˆÚ“®‚µ‚Ä‚¢‚È‚¢ 0ˆÈŠO: ˆÚ“®’†

 public:
  Player(Point pos, Direction dir, MapMediator *mapMediator)
      : pos(pos), dir(dir), mapMediator(mapMediator) {
    this->moveCounter = 0;
    this->drawPos = pos * BLOCK_SIZE;
  };

  void update();

  void laterUpdate();  // “–‚½‚è”»’èŒã‚ÌXV

  void draw() const;

  Point getPos() const { return this->pos; }

  void setKnockBack();
};

#pragma once
#include <Siv3D.hpp>

#include "Common.h"
using namespace common;

class MapMediator;

class Player {
 private:
  MapMediator *mapMediator;
  Point pos;
  Direction dir;
  int knockBackCounter;

 public:
  Player(Point pos, MapMediator *mapMediator)
      : pos(pos), mapMediator(mapMediator){
    this->dir = Direction::Down;
  };
  void update();
  void laterUpdate(); // “–‚½‚è”»’èŒã‚ÌXV
  void draw() const;
  Point getPos() const { return this->pos; }
  void setKnockBack();
};

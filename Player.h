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
  Player(Point pos, Direction dir, MapMediator *mapMediator)
      : pos(pos), dir(dir), mapMediator(mapMediator){
  };
  void update();
  void laterUpdate(); // 当たり判定後の更新
  void draw() const;
  Point getPos() const { return this->pos; }
  void setKnockBack();
};

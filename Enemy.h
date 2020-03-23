#pragma once
#include <Siv3D.hpp>

#include "Common.h"

class MapMediator;

class Enemy {
  using Direction = common::Direction;
 protected:
  Point pos;
  Point drawPos;
  Point nextPos;
  Direction dir;
  MapMediator *mapMediator;

 public:
  Enemy(Point pos, Direction dir, MapMediator *mapMediator)
      : pos(pos), nextPos(pos), dir(dir), mapMediator(mapMediator) {}

  virtual void update() = 0;
  virtual void laterUpdate(){};
  virtual void draw() const;
  Point getPos() const { return this->pos; }
};

class RandomRoomba : public Enemy {
  using Direction = common::Direction;
 protected:
  const int id = 0;
  uint16 frameCounter;
  uint16 moveCounter; 
  Point beforePos;

 public:
  RandomRoomba(Point pos, Direction dir, MapMediator *mapChecker)
      : Enemy(pos, dir, mapChecker) {
    this->beforePos = pos;
    this->drawPos = pos * common::BLOCK_SIZE;
    this->frameCounter = 0;
    this->moveCounter = 0;
  }

  void update() override;
  void draw() const override;
  void laterUpdate() override;
};

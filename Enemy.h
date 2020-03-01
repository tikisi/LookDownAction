#pragma once
#include <Siv3D.hpp>

class MapMediator;

class Enemy {
 protected:
  Point pos;
  MapMediator *mapMediator;

 public:
  Enemy(Point pos, MapMediator *mapMediator) : pos(pos), mapMediator(mapMediator) {}

  virtual void update() = 0;
  virtual void laterUpdate(){};
  virtual void draw() const;
  Point getPos() const { return this->pos; }
};

class RandomRoomba : public Enemy {
 protected:
  int frameCounter;
  Point beforePos;

 public:
  RandomRoomba(Point pos, MapMediator *mapChecker) : Enemy(pos, mapChecker) {
    this->beforePos = pos;
    frameCounter = 0;
  }

  void update() override;
  void laterUpdate() override;
  virtual void draw() const { Enemy::draw(); };
};

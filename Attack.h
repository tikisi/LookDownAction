#pragma once
#include <Siv3D.hpp>

#include "Common.h"

class Attack {
 protected:
  Point pos;

 public:
  Attack(Point _pos) : pos(_pos) {}

  virtual void update() = 0;
  virtual void draw() const;
  Point getPos() const { return this->pos; }
};

class StraightAttack : public Attack {
 private:
  int moveCounter;
  common::Direction direction;

 public:
  StraightAttack(Point pos, common::Direction direction)
      : Attack(pos), direction(direction) {
    this->moveCounter = 0;
  }

  void update();
};

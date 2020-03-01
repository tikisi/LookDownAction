#pragma once
#include <Siv3D.hpp>
#include <vector>

#include "Enemy.h"
#include "Common.h"
#include "Player.h"
#include "Attack.h"
using namespace common;

class MapMediator {
 public:
  virtual bool isEmpty(const Point &pos) const = 0;
  virtual void setDirt(const Point &pos) = 0;
  virtual void setClean(const Point &pos) = 0;
  virtual void addAttack(Attack *attack) = 0;
};

class MapManager : public MapMediator {
 private:
  Player *player;
  Array<Enemy *> enemies;
  Array<Attack *> attacks;

 public:
  const int xNum;
  const int yNum;
  const int blockSize;
  std::vector<std::vector<int> > mapChip;
  std::vector<std::vector<int> > mapState;

  // MapManager() = default;
  MapManager(int _xNum = (DEFAULT_SCENE_WIDTH / BLOCK_SIZE),
             int _yNum = (DEFAULT_SCENE_HEIGHT / BLOCK_SIZE),
             int _blockSize = BLOCK_SIZE)
      : xNum(_xNum),
        yNum(_yNum),
        blockSize(_blockSize),
        mapState(
            std::vector<std::vector<int> >(xNum, std::vector<int>(yNum, 0))) {
    this->player = new Player(Point(1, 1), this);
    this->enemies.push_back(new RandomRoomba(Point(10, 10), this));
  }

  void setMapChip(std::vector<std::vector<int> > _mapChip) {
    this->mapChip = _mapChip;
  }

  void update();

  void draw() const;

  bool isEmpty(const Point &pos) const override;
  void setDirt(const Point &pos) override;
  void setClean(const Point &pos) override;
  void addAttack(Attack *attack) override;
};

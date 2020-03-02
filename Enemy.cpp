#include "Enemy.h"

#include "Common.h"
#include "MapManager.h"
using namespace common;

void Enemy::draw() const {
  Rect(pos.x * BLOCK_SIZE, pos.y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)
      .draw(Palette::Red);
}

void RandomRoomba::update() {
  if (++(this->frameCounter) == 60) {
    this->frameCounter = 0;

    int random = Random(0, 3);
    Point nextPos = this->pos + getVecFromDir(random);

    // ‘O‚ÌˆÊ’u‚É–ß‚éd‚Ý‚ð‰º‚°‚é
    if (beforePos == nextPos) {
      random = Random(0, 3);
      nextPos = this->pos + getVecFromDir(random);
    }

    this->dir = static_cast<common::Direction>(random);

    if (this->mapMediator->isEmpty(nextPos)) {
      this->beforePos = this->pos;
      this->pos = nextPos;
    } else {
      this->frameCounter = 59;
      this->update();
    }
  }
}

void RandomRoomba::draw() const {
  TextureAsset(U"Roomba").rotated((int)dir * 90_deg).draw(BLOCK_SIZE * pos.x, BLOCK_SIZE * pos.y);
}

void RandomRoomba::laterUpdate() { this->mapMediator->setClean(this->pos); }

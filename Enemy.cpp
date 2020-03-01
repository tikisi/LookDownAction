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

    int random = Random(1, 4);
    Point nextPos = this->pos + getVecFromDir(random);

    // ‘O‚ÌˆÊ’u‚É–ß‚éd‚Ý‚ð‰º‚°‚é
    if (beforePos == nextPos) {
      nextPos = this->pos + getVecFromDir(random);
    }

    if (this->mapMediator->isEmpty(nextPos)) {
      this->beforePos = this->pos;
      this->pos = nextPos;
    } else {
      this->frameCounter = 59;
      this->update();
    }
  }
}

void RandomRoomba::laterUpdate() { this->mapMediator->setClean(this->pos); }

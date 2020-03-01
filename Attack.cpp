#include "Attack.h"
using namespace common;

void Attack::draw() const {
  Rect((pos.x + 0.25) * BLOCK_SIZE, (pos.y + 0.25) * BLOCK_SIZE, BLOCK_SIZE / 2)
      .draw(Palette::Aliceblue);
}

void StraightAttack::update() {
  if (moveCounter++ % 20 == 0) {
    this->pos += getVecFromDir(static_cast<int>(this->direction));
  }
}

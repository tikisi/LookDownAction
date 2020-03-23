#include "Attack.h"
using namespace common;

void Attack::draw() const {
  Rect(drawPos, BLOCK_SIZE / 2).draw(Palette::Blue);
}

void Attack::update() {
  this->pos.x = (drawPos.x + 0.25f * BLOCK_SIZE) / BLOCK_SIZE;
  this->pos.y = (drawPos.y + 0.25f * BLOCK_SIZE) / BLOCK_SIZE;
}

void StraightAttack::update() {
  this->drawPos += 2 * getVecFromDir(this->direction);
  Attack::update();
}

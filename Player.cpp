#include "Player.h"

#include "MapManager.h"
#include "Attack.h"

void Player::update() {
  // 移動処理
  Point nextPos = pos;
  if (KeyUp.down()) {
    nextPos += Point::Up(1);
    this->dir = Direction::Up;
  }
  if (KeyDown.down()) {
    nextPos += Point::Down(1);
    this->dir = Direction::Down;
  }
  if (KeyRight.down()) {
    nextPos += Point::Right(1);
    this->dir = Direction::Right;
  }
  if (KeyLeft.down()) {
    nextPos += Point::Left(1);
    this->dir = Direction::Left;
  }

  if (mapMediator ->isEmpty(nextPos)) {
    this->pos = nextPos;
  }

  // ノックバック
  if (knockBackCounter != 0) {
    if (knockBackCounter++ == 80) {
      knockBackCounter = 0;
    }
  }

  // 攻撃
  if(KeyZ.down()) {
    mapMediator->addAttack(new StraightAttack(this->pos, this->dir)); 
  }
}

void Player::laterUpdate() {
  this->mapMediator->setDirt(this->pos);
}

void Player::draw() const {
  if (knockBackCounter == 0 || !(knockBackCounter % 10 == 0)) {
    Rect(pos * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE).draw(Palette::Gold);
  }
}

void Player::setKnockBack() {
  if (this->knockBackCounter == 0) {
    this->knockBackCounter = 1;
  }
}

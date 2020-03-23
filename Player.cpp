#include "Player.h"

#include "Attack.h"
#include "MapManager.h"

void Player::update() {
  // 移動処理
  if (moveCounter == 0) {
    this->nextPos = pos;
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
    if (mapMediator->isEmpty(nextPos) && pos != nextPos) {
      // this->pos = nextPos;
      this->moveCounter = 1;
    }
  }
  if (moveCounter != 0) {
    this->drawPos += 2 * getVecFromDir(this->dir);
    if (moveCounter++ == 16) {
      this->moveCounter = 0;
      this->pos = this->nextPos;
    }
  }

  // ノックバック
  if (knockBackCounter != 0) {
    if (knockBackCounter++ == 80) {
      knockBackCounter = 0;
    }
  }

  // 攻撃
  if (KeyZ.down()) {
    mapMediator->addAttack(new StraightAttack(this->pos, this->dir));
  }
}

void Player::laterUpdate() { this->mapMediator->setDirt(this->pos); }

void Player::draw() const {
  if (knockBackCounter == 0 || !(knockBackCounter % 10 == 0)) {
    // Rect(pos * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE).draw(Palette::Gold);
    Rect(drawPos, BLOCK_SIZE).draw(Palette::Red);
  }
}

void Player::setKnockBack() {
  if (this->knockBackCounter == 0) {
    this->knockBackCounter = 1;
  }
}

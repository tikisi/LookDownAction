#include "Player.h"

#include "Attack.h"
#include "MapManager.h"


void Player::update() {
    // 移動処理
    if (moveCounter == 0) {
        const Key key = getMinKey(getMinKey(KeyUp, KeyDown), getMinKey(KeyLeft, KeyRight));
        if (key.pressed()) {
            this->dir = getDirFromKey(key);
            if (mapMediator->isEmpty(pos + getVecFromDir(dir)))
                this->moveCounter = 1;
        }
    }
    if (moveCounter != 0) {
        static constexpr int speed = 2;
        this->drawPos += speed * getVecFromDir(this->dir);
        if (moveCounter++ == BLOCK_SIZE / speed) {
            this->moveCounter = 0;
            this->pos = drawPos / BLOCK_SIZE;
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

Key Player::getMinKey(const Key& a, const Key& b) {
    return std::min(a, b, [](const Key& a, const Key& b) {
        if(!a.pressed() && b.pressed()) {
            return false;
        }
        if(a.pressed() && !b.pressed()) {
            return true;
        }
        return a.pressedDuration() < b.pressedDuration();
        });
}

Direction Player::getDirFromKey(const Key& key) {
    if (key == KeyUp) {
        return Direction::Up;
    }
    else if (key == KeyDown) {
        return Direction::Down;
    }
    else if (key == KeyRight) {
        return Direction::Right;
    }
    else if (key == KeyLeft) {
        return Direction::Left;
    }
    else {
        throw "Can't recognize key \n";
    }
}

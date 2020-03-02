#include "MapManager.h"

void MapManager::update() {
  // 各要素の更新
  player->update();
  for (const auto &e : this->enemies) {
    e->update();
  }
  // 攻撃の更新
  auto attack = attacks.begin();
  while (attack != attacks.end()) {
    (*attack)->update();
    // 壁に当たったとき削除
    if (!isEmpty((*attack)->getPos())) {
      attack = attacks.erase(attack);
    } else {
      attack++;
    }
  }

  // 当たり判定
  // プレイヤーと敵の当たり判定
  for (const auto &e : this->enemies) {
    if (e->getPos() == this->player->getPos()) {
      this->player->setKnockBack();
    }
  }
  // 敵と攻撃の当たり判定
  attack = attacks.begin();
  while (attack != attacks.end()) {
    auto enemy = enemies.begin();
    bool deleteFlg = false;
    while (enemy != enemies.end()) {
      if ((*enemy)->getPos() == (*attack)->getPos()) {
        enemy = enemies.erase(enemy);
        attack = attacks.erase(attack);
        deleteFlg = true;
        break;
      } else {
        enemy++;
      }
    }
    if (!deleteFlg) {
      attack++;
    }
  }

  // 当たり判定後のupdate
  player->laterUpdate();
  for (const auto &e : this->enemies) {
    e->laterUpdate();
  }
}

void MapManager::draw() const {
  // マップの描画
  for (int i = 0; i < xNum; i++) {
    for (int j = 0; j < yNum; j++) {
      // マップチップの描画
      if (mapChip[i][j] == 1) {
        Rect(i * blockSize, j * blockSize, blockSize, blockSize)
            .drawFrame(4, 1, Palette::Green);
        //TextureAsset(U"MapChip1").draw(i * blockSize, j * blockSize);
      } else if(mapChip[i][j] == 0) {
        TextureAsset(U"MapChip2").draw(i * blockSize, j * blockSize);
      }
      // 汚れの描画
      if (mapState[i][j] == 1) {
        Circle((i + 0.5f) * blockSize, (j + 0.5f) * blockSize, blockSize / 2.0f)
            .drawFrame(1, 1, Palette::Pink);
      }
    }
  }

  // プレイヤーの描画
  this->player->draw();
  //敵の描画
  for (const auto &e : this->enemies) {
    e->draw();
  }
  // 敵の描画
  for (const auto &a : this->attacks) {
    a->draw();
  }
}

bool MapManager::isEmpty(const Point &pos) const {
  return !(mapChip[pos.x][pos.y] == 1);
}

void MapManager::setDirt(const Point &pos) {
  if (this->isEmpty(pos)) {
    this->mapState[pos.x][pos.y] = 1;
  }
}

void MapManager::setClean(const Point &pos) {
  this->mapState[pos.x][pos.y] = 0;
}

void MapManager::addAttack(Attack *attack) { this->attacks.push_back(attack); }

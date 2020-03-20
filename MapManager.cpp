#include "MapManager.h"

void MapManager::update() {
  // Še—v‘f‚ÌXV
  player->update();
  for (const auto &e : this->enemies) {
    e->update();
  }
  // UŒ‚‚ÌXV
  auto attack = attacks.begin();
  while (attack != attacks.end()) {
    (*attack)->update();
    // •Ç‚É“–‚½‚Á‚½‚Æ‚«íœ
    if (!isEmpty((*attack)->getPos())) {
      attack = attacks.erase(attack);
    } else {
      attack++;
    }
  }

  // “–‚½‚è”»’è
  // ƒvƒŒƒCƒ„[‚Æ“G‚Ì“–‚½‚è”»’è
  for (const auto &e : this->enemies) {
    if (e->getPos() == this->player->getPos()) {
      this->player->setKnockBack();
    }
  }
  // “G‚ÆUŒ‚‚Ì“–‚½‚è”»’è
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

  // “–‚½‚è”»’èŒã‚Ìupdate
  player->laterUpdate();
  for (const auto &e : this->enemies) {
    e->laterUpdate();
  }
}

void MapManager::draw() const {
  // ƒ}ƒbƒv‚Ì•`‰æ
  for (int i = 0; i < X_NUM; i++) {
    for (int j = 0; j < Y_NUM; j++) {
      // ƒ}ƒbƒvƒ`ƒbƒv‚Ì•`‰æ
      if (mapChip[i][j] == 1) {
        Rect(i * BLOCK_SIZE, j * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)
            .drawFrame(4, 1, Palette::Green);
        //TextureAsset(U"MapChip1").draw(i * BLOCK_SIZE, j * BLOCK_SIZE);
      } else if(mapChip[i][j] == 0) {
        TextureAsset(U"MapChip2").draw(i * BLOCK_SIZE, j * BLOCK_SIZE);
      }
      // ‰˜‚ê‚Ì•`‰æ
      if (mapState[i][j] == 1) {
        Circle((i + 0.5f) * BLOCK_SIZE, (j + 0.5f) * BLOCK_SIZE, BLOCK_SIZE / 2.0f)
            .drawFrame(1, 1, Palette::Pink);
      }
    }
  }

  // ƒvƒŒƒCƒ„[‚Ì•`‰æ
  this->player->draw();
  //“G‚Ì•`‰æ
  for (const auto &e : this->enemies) {
    e->draw();
  }
  // “G‚Ì•`‰æ
  for (const auto &a : this->attacks) {
    a->draw();
  }
}

void MapManager::loadMap(const String mapPath) {
  const CSVData csv(mapPath);
  
  if(!csv) {
    throw Error(U"Failed to load " + mapPath);
  }

  for(size_t row = 0; row < csv.rows(); ++row) {
    for(size_t col = 0; col < csv.columns(row); ++col) {
      this->mapChip[col][row] = Parse<int16>(csv[row][col]);
    }
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

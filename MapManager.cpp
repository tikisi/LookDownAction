#include "MapManager.h"

void MapManager::update() {
  // �e�v�f�̍X�V
  player->update();
  for (const auto &e : this->enemies) {
    e->update();
  }
  // �U���̍X�V
  auto attack = attacks.begin();
  while (attack != attacks.end()) {
    (*attack)->update();
    // �ǂɓ��������Ƃ��폜
    if (!isEmpty((*attack)->getPos())) {
      attack = attacks.erase(attack);
    } else {
      attack++;
    }
  }

  // �����蔻��
  // �v���C���[�ƓG�̓����蔻��
  for (const auto &e : this->enemies) {
    if (e->getPos() == this->player->getPos()) {
      this->player->setKnockBack();
    }
  }
  // �G�ƍU���̓����蔻��
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

  // �����蔻����update
  player->laterUpdate();
  for (const auto &e : this->enemies) {
    e->laterUpdate();
  }
}

void MapManager::draw() const {
  // �}�b�v�̕`��
  for (int i = 0; i < X_NUM; i++) {
    for (int j = 0; j < Y_NUM; j++) {
      // �}�b�v�`�b�v�̕`��
      if (mapChip[i][j] == 1) {
        Rect(i * BLOCK_SIZE, j * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)
            .drawFrame(4, 1, Palette::Green);
        //TextureAsset(U"MapChip1").draw(i * BLOCK_SIZE, j * BLOCK_SIZE);
      } else if(mapChip[i][j] == 0) {
        TextureAsset(U"MapChip2").draw(i * BLOCK_SIZE, j * BLOCK_SIZE);
      }
      // ����̕`��
      if (mapState[i][j] == 1) {
        Circle((i + 0.5f) * BLOCK_SIZE, (j + 0.5f) * BLOCK_SIZE, BLOCK_SIZE / 2.0f)
            .drawFrame(1, 1, Palette::Pink);
      }
    }
  }

  // �v���C���[�̕`��
  this->player->draw();
  //�G�̕`��
  for (const auto &e : this->enemies) {
    e->draw();
  }
  // �G�̕`��
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

#include "MapManager.h"

void MapManager::update() {
    // 各要素の更新
    player->update();
    for (const auto& e : this->enemies) {
        e->update();
    }
    enemyRespawner.update();
    // 攻撃の更新
    auto attack = attacks.begin();
    while (attack != attacks.end()) {
        (*attack)->update();
        // 壁に当たったとき削除
        if (!isEmpty((*attack)->getPos())) {
            attack = attacks.erase(attack);
        }
        else {
            attack++;
        }
    }

    // 当たり判定
    // プレイヤーと敵の当たり判定
    for (const auto& e : this->enemies) {
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
                // 死んだことをRespawnerに知らせる
                enemyRespawner.addActiveSpawner((*enemy)->getIndex());
                enemy = enemies.erase(enemy);
                attack = attacks.erase(attack);
                deleteFlg = true;
                break;
            }
            else {
                enemy++;
            }
        }
        if (!deleteFlg) {
            attack++;
        }
    }

    // 当たり判定後のupdate
    player->laterUpdate();
    for (const auto& e : this->enemies) {
        e->laterUpdate();
    }
}

void MapManager::draw() const {
    // マップの描画
    for (int i = 0; i < X_NUM; i++) {
        for (int j = 0; j < Y_NUM; j++) {
            // マップチップの描画
            if (mapChip[i][j] == 1) {
                Rect(i * BLOCK_SIZE, j * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)
                    .drawFrame(4, 1, Palette::Green);
                // TextureAsset(U"MapChip1").draw(i * BLOCK_SIZE, j * BLOCK_SIZE);
            }
            else if (mapChip[i][j] == 0) {
                TextureAsset(U"MapChip2").draw(i * BLOCK_SIZE, j * BLOCK_SIZE);
            }
            // 汚れの描画
            if (mapState[i][j] == 1) {
                Circle((i + 0.5f) * BLOCK_SIZE, (j + 0.5f) * BLOCK_SIZE,
                    BLOCK_SIZE / 2.0f)
                    .drawFrame(1, 1, Palette::Pink);
            }
        }
    }

    // プレイヤーの描画
    this->player->draw();
    //敵の描画
    for (const auto& e : this->enemies) {
        e->draw();
    }
    // 敵の描画
    for (const auto& a : this->attacks) {
        a->draw();
    }
}

void MapManager::loadMap(const int stageNum) {
    const String csvPath = mapPath + Format(stageNum) + U".csv";
    const String jsonPath = mapPath + Format(stageNum) + U".json";
    const CSVData csv(csvPath);
    const JSONReader json(jsonPath);

    if (!csv) {
        throw Error(U"Failed to load " + csvPath);
    }
    if (!json) {
        throw Error(U"Failed to load " + jsonPath);
    }

    // mapChip
    for (size_t row = 0; row < csv.rows(); ++row) {
        for (size_t col = 0; col < csv.columns(row); ++col) {
            this->mapChip[col][row] = Parse<int16>(csv[row][col]);
        }
    }

    // player
    {
        Point pos(json[U"player.posX"].get<int>(), json[U"player.posY"].get<int>());
        auto dir = json[U"player.dir"].getString();
        this->player =
            new Player(pos, StringToDir.at(dir), this);
    }

    // enemy
    const auto enemyNum = json[U"enemyNum"].get<int>();
    for (size_t i = 0; i < enemyNum; i++) {
        String name = U"enemy" + Format(i);
        auto id = json[name + U".id"].get<int>();
        Point pos(json[name + U".posX"].get<int>(), json[name + U".posY"].get<int>());
        auto dir = StringToDir.at(json[name + U".dir"].getString());
        auto frequency = json[name + U".frequency"].get<int>();

        this->enemyRespawner.push_backInformation(id, pos, dir, frequency);

        if (id == 0) {
            this->enemies.push_back(new RandomRoomba(pos, dir, this, i));
        }
    }
}

bool MapManager::isEmpty(const Point& pos) const {
    return !(mapChip[pos.x][pos.y] == 1);
}

void MapManager::setDirt(const Point& pos) {
    if (this->isEmpty(pos)) {
        this->mapState[pos.x][pos.y] = 1;
    }
}

void MapManager::setClean(const Point& pos) {
    this->mapState[pos.x][pos.y] = 0;
}

void MapManager::addAttack(Attack* attack) { this->attacks.push_back(attack); }

void MapManager::addEnemy(Enemy* enemy) { this->enemies.push_back(enemy); }

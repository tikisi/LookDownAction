#pragma once
#include <Siv3D.hpp>
#include <vector>
#include <map>

#include "Enemy.h"
#include "EnemyRespawner.h"
#include "Common.h"
#include "Player.h"
#include "Attack.h"
using namespace com;

class MapMediator {
public:
    virtual bool isEmpty(const Point& pos) const = 0;
    virtual void setDirt(const Point& pos) = 0;
    virtual void setClean(const Point& pos) = 0;
    virtual void addAttack(Attack* attack) = 0;
    virtual void addEnemy(Enemy* enemy) = 0;
};

class MapManager : public MapMediator {
private:
    Player* player;
    Array<Enemy*> enemies;
    Array<Attack*> attacks;

    EnemyRespawner enemyRespawner;

    void loadMap(const int stageNum);

public:
    std::vector<std::vector<int16> > mapChip;
    std::vector<std::vector<int16> > mapState;

    MapManager()
        : mapChip(
            std::vector<std::vector<int16> >(X_NUM, std::vector<int16>(Y_NUM, 0))),
        mapState(
            std::vector<std::vector<int16> >(X_NUM, std::vector<int16>(Y_NUM, 0))),
        enemyRespawner(EnemyRespawner(this)) {
        this->loadMap(1);
    }

    void setMapChip(std::vector<std::vector<int16> > _mapChip) {
        this->mapChip = _mapChip;
    }

    void update();

    void draw() const;

    bool isEmpty(const Point& pos) const override;
    void setDirt(const Point& pos) override;
    void setClean(const Point& pos) override;
    void addAttack(Attack* attack) override;
    void addEnemy(Enemy* enemy) override;
};

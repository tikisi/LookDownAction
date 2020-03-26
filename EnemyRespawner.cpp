#include "EnemyRespawner.h"
#include "MapManager.h"
#include "Enemy.h"

void EnemyRespawner::update() {
    for (auto& i : activeSpawner) {
        i.second--;
        if (i.second == 0) {
            auto info = informations[i.first];
            if (info->id == 0) {
                mapMediator->addEnemy(
                    new RandomRoomba(info->pos, info->dir, mapMediator, i.first)
                );
            }
        }
    }
}
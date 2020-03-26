#pragma once
#include <Siv3D.hpp>
#include "Common.h" 

class MapMediator;

class EnemyRespawner {
    using Direction = com::Direction;
public:
    class EnemyInformation {
    public:
        const uint32 id;
        const Point pos;
        const Direction dir;
        const int frequency;

        EnemyInformation(uint32 id, Point pos, Direction dir, int frequency) :
            id(id), pos(pos), dir(dir), frequency(frequency) {}
    };

private:
    MapMediator* mapMediator;
    Array<EnemyInformation*> informations;
    Array<std::pair<size_t, int>> activeSpawner; // <index, frame>

public:
    explicit EnemyRespawner(MapMediator* mapMediator) : mapMediator(mapMediator){};

    void push_backInformation(uint32 id, Point pos, Direction dir, int frequency) {
        this->informations.push_back(new EnemyInformation(id, pos, dir, frequency));
    }

    void addActiveSpawner(size_t index) {
        this->activeSpawner.push_back(std::make_pair(index, informations[index]->frequency * 60));
    }

    void update();
};

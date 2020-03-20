#pragma once
#include <Siv3D.hpp>
#include "MapManager.h"
#include "DummyMap.h"

using App = SceneManager<String>;

class TestScene : public App::Scene {
 private:
   MapManager *mapManager;
 public:
  TestScene(const InitData& init) : IScene(init) {
    this->mapManager = new MapManager();
    // this->mapManager->setMapChip(transporseMatrix(dummyMap));
  }

  ~TestScene() {
    delete mapManager;
  }

  void update() override;
  void draw() const override;
}; 
#pragma once
#include <Siv3D.hpp>

using App = SceneManager<String>;

class Title : public App::Scene {
 private:
 public:
  Title(const InitData &initData) : IScene(initData) {};
  void update() override;
  void draw() const override;
};

#pragma once
#include <Siv3D.hpp>

class Config : public SceneManager<String>::Scene {
 private:
 public:
  Config(const InitData &initData) : IScene(initData) {};
  void update() override;
  void draw() const override;
};

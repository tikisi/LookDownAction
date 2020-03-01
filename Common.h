#pragma once
#include <Siv3D.hpp>

namespace common {
constexpr int DEFAULT_WINDOW_WIDTH = 1024;
constexpr int DEFAULT_WINDOW_HEIGHT = 768;
constexpr int DEFAULT_SCENE_WIDTH = 640;
constexpr int DEFAULT_SCENE_HEIGHT = 480;
constexpr int BLOCK_SIZE = 32;

enum class Direction : int {
  Left = 1,
  Up,
  Right,
  Down
};

// 方向をもとに単位ベクトルを生成
extern constexpr Point getVecFromDir(int d);

}  // namespace information

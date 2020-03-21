#pragma once
#include <Siv3D.hpp>
#include <map>

namespace common {
// ��{���
constexpr int DEFAULT_WINDOW_WIDTH = 1024;
constexpr int DEFAULT_WINDOW_HEIGHT = 768;
constexpr int DEFAULT_SCENE_WIDTH = 640;
constexpr int DEFAULT_SCENE_HEIGHT = 480;
constexpr int BLOCK_SIZE = 32;
constexpr int X_NUM = 20;
constexpr int Y_NUM = 15;

// �t�@�C���p�X
const String mapPath = U"../Asset/Map/stage";

// ����
enum class Direction : int { Up = 0, Right, Down, Left };

// String��Direction�̃}�b�v
const std::map<String, Direction> StringToDir{{U"Up", Direction::Up},
                                              {U"Right", Direction::Right},
                                              {U"Down", Direction::Down},
                                              {U"Left", Direction::Left}};

// ���������ƂɒP�ʃx�N�g���𐶐�
extern constexpr Point getVecFromDir(int d);

}  // namespace common

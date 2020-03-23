#include "Common.h"

namespace common {
// 方向をもとに単位ベクトルを生成
Point getVecFromDir(int d) {
  switch (d) {
    case 0:
      return Point::Up();
    case 1:
      return Point::Right();
    case 2:
      return Point::Down();
    case 3:
      return Point::Left();
  }

  return Point(0, 0);
}

Point getVecFromDir(Direction d) {
  switch (d) {
    case Direction::Up:
      return Point::Up();
    case Direction::Right:
      return Point::Right();
    case Direction::Down:
      return Point::Down();
    case Direction::Left:
      return Point::Left();
  }

  return Point(0, 0);
}

}  // namespace common
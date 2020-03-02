#include "Common.h"

namespace common {
// 方向をもとに単位ベクトルを生成
constexpr Point getVecFromDir(int d) {
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
}  // namespace common
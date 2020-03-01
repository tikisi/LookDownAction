#include "Common.h"

namespace common {
// ���������ƂɒP�ʃx�N�g���𐶐�
constexpr Point getVecFromDir(int d) {
  switch (d) {
    case 1:
      return Point::Left();
    case 2:
      return Point::Up();
    case 3:
      return Point::Right();
    case 4:
      return Point::Down();
  }

  return Point(0, 0);
}
}  // namespace common
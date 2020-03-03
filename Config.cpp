#include "Config.h"

#include <array>

const Array<String> windowSizesString = {U"1024Å~768", U"640Å~480"};
constexpr std::array<std::pair<int, int>, 2> windowSizes = {
    std::make_pair(1024, 768), std::make_pair(640, 480)};
size_t windowIndex = 0;

void Config::update() {
  if (SimpleGUI::RadioButtons(windowIndex, windowSizesString,
                              Point(100, 200))) {
    Window::Resize(windowSizes[windowIndex].first, windowSizes[windowIndex].second);
  }
}

void Config::draw() const {}
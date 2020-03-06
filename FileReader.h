#pragma once
#include <string>
#include <vector>

class FileReader {
 public:
  static std::vector<std::vector<int>> mapRead(std::string filePath);
};

#include "FileReader.h"
#include <fstream>
#include <sstream>
using namespace std;

vector<vector<int>> FileReader::mapRead(string filePath) {
  vector<vector<int>> result;
  ifstream ifs(filePath);
  string str;
  while(getline(ifs, str)) {
    string tmp;
    istringstream stream(str);
    vector<int> line;
    while(getline(stream, tmp, ',')) {
      line.push_back(stoi(tmp));
    }
    result.push_back(line);
  }
  
  return result;
} 

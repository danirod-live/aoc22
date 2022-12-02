#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char **argv) {
  std::ifstream file("01.txt");
  std::string line;

  std::vector<int> sums = {};
  int maxlocal = 0;

  while (std::getline(file, line)) {
    if (line.empty()) {
      sums.push_back(maxlocal);
      maxlocal = 0;
    } else {
      std::istringstream strm(line);
      int res;
      strm >> res;
      maxlocal += res;
    }
  }

  std::sort(sums.begin(), sums.end());
  auto goal = sums.rbegin();
  std::cout << "P1: " << *goal << std::endl;
  std::cout << "P2: " << *(goal) + *(goal + 1) + *(goal + 2) << std::endl;
}

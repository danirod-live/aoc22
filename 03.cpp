#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

int Score(char letter) {
  if ('a' <= letter && letter <= 'z') {
    return 1 + (letter - 'a');
  } else {
    return 27 + (letter - 'A');
  }
}

char CommonLetter(std::string s1, std::string s2) {
  int i = 0, j = 0;
  while (i < s1.size() && j < s2.size()) {
    if (s1.at(i) == s2.at(j)) {
      return s1.at(i);
    }
    if (s1.at(i) < s2.at(j)) {
      i++;
    } else {
      j++;
    }
  }
  return -1;
}

int main(int argc, char **argv) {
  std::ifstream file("03.txt");
  std::string line;

  std::vector<std::string> lines;

  int score = 0;
  while (std::getline(file, line)) {
    lines.push_back(line);

    std::string s1 = line.substr(0, line.size() / 2);
    std::string s2 = line.substr(line.size() / 2, line.size() / 2);

    std::sort(s1.begin(), s1.end());
    std::sort(s2.begin(), s2.end());

    char common = CommonLetter(s1, s2);
    score += Score(common);
  }

  // P2
  int score2 = 0;
  for (int i = 0; i < lines.size(); i += 3) {
    std::string s1 = lines.at(i);
    std::string s2 = lines.at(i + 1);
    std::string s3 = lines.at(i + 2);

    std::sort(s1.begin(), s1.end());
    std::sort(s2.begin(), s2.end());
    std::sort(s3.begin(), s3.end());

    std::vector<char> midint;
    std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
                          std::back_inserter(midint));
    std::vector<char> intersection;
    std::set_intersection(midint.begin(), midint.end(), s3.begin(), s3.end(),
                          std::back_inserter(intersection));
    char common = intersection.at(0);
    score2 += Score(common);
  }

  std::cout << "P1: " << score << std::endl;
  std::cout << "P2: " << score2 << std::endl;
}

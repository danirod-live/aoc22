#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

class Par {
public:
  Par(std::string input);
  int Min();
  int Max();

  bool Contains(const Par &);
  bool Overlap(const Par &);

private:
  int min, max;
  friend std::ostream &operator<<(std::ostream &, const Par &);
};

Par::Par(std::string input) {
  std::stringstream ss(input);
  std::string token;
  std::getline(ss, token, '-');
  min = std::stoi(token);
  std::getline(ss, token, '-');
  max = std::stoi(token);
}

bool Par::Contains(const Par &par) {
  return this->min <= par.min && this->max >= par.max;
}

bool Par::Overlap(const Par &par) {
  if (par.min >= this->min) {
    return par.min <= this->max;
  } else if (par.max <= this->max) {
    return par.max >= this->min;
  }
  return false;
}

std::ostream &operator<<(std::ostream &str, const Par &par) {
  return str << "Par(" << par.min << "," << par.max << ")";
}

int Par::Min() { return min; }

int Par::Max() { return max; }

int main(int argc, char **argv) {
  std::ifstream file("04.txt");
  std::string str;

  int count1 = 0;
  int count2 = 0;
  while (std::getline(file, str)) {
    std::stringstream ss(str);
    std::string left, right;
    std::getline(ss, left, ',');
    std::getline(ss, right, ',');

    Par parLeft(left), parRight(right);
    if (parLeft.Contains(parRight) || parRight.Contains(parLeft)) {
      count1++;
    }
    if (parLeft.Overlap(parRight) || parRight.Overlap(parLeft)) {
      count2++;
    }
  }

  std::cout << "P1: " << count1 << std::endl;
  std::cout << "P2: " << count2 << std::endl;

  return 0;
}

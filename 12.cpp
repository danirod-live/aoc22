#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Coord {
public:
  int x, y;
  Coord() {
    this->x = 0;
    this->y = 0;
  }
  Coord(int x, int y) {
    this->x = x;
    this->y = y;
  }

  Coord Inc(int x, int y) { return Coord(this->x + x, this->y + y); }

  bool operator<(const Coord &c) const {
    return x < c.x || (x == c.x && y < c.y);
  }
  friend std::ostream &operator<<(std::ostream &, const Coord &);
};

std::ostream &operator<<(std::ostream &str, const Coord &coord) {
  return str << "(" << coord.x << "," << coord.y << ")";
}

class Grid {
public:
  Grid(const string &filename);
  void Dump();
  int Score() { return score; }

private:
  void Process();
  int MinScore(Coord &initial, set<Coord> &visited);
  bool Acceptable(int x, int y, char current);
  bool Acceptable(Coord &coord, char current) {
    return Acceptable(coord.x, coord.y, current);
  }

  int width = 0, height = 0;
  vector<string> lines;
  Coord pos;
  int score = 0;
};

void Grid::Dump() {
  cout << "size -> " << width << "," << height << endl;
  cout << "p -> " << pos << endl;
  cout << "score -> " << score << endl;
}

Grid::Grid(const string &filename) {
  ifstream file(filename);
  string line;
  while (getline(file, line)) {
    lines.push_back(line);
    if (line.find('S') != string::npos) {
      // This is the line.
      pos.x = line.find('S');
      pos.y = height;
    }
    height++;
  }
  width = lines[0].size();

  Process();
}

void Grid::Process() {
  set<Coord> visited = {pos};
  score = MinScore(pos, visited);
}

int level = 0;

#define SPACE(n)                                                               \
  do {                                                                         \
    for (int i = 0; i < n; i++)                                                \
      cout << " ";                                                             \
  } while (0);

int Grid::MinScore(Coord &initial, set<Coord> &visited) {
  char self = lines[initial.y][initial.x];
  if (self == 'E') {
    return 0;
  }
  unsigned int score = -1;
  vector<Coord> around = {
      initial.Inc(0, -1),
      initial.Inc(0, 1),
      initial.Inc(-1, 0),
      initial.Inc(1, 0),
  };
  level++;
  for (Coord c : around) {
    if (Acceptable(c, self) && visited.count(c) == 0) {
      // Let's look around there!
      visited.insert(c);
      int s = 1 + MinScore(c, visited);
      SPACE(level);
      cout << s << " (" << initial << " -> " << c << ")" << endl;
      if (s > -1 && s < score) {
        score = s;
      }
      visited.erase(c);
    }
  }
  level--;
  return score;
}

// Is it acceptable to jump to (x, y) if our current letter is (current)?
bool Grid::Acceptable(int x, int y, char current) {
  if (x < 0 || y < 0 || x >= width || y >= height) {
    return false;
  }
  char target = lines[y][x];
  if (current == 'S') {
    current = 'a' - 1;
  }
  if (target == 'E') {
    target = 'z' + 1;
  }
  return target >= current && target - current <= 1;
}

int main(int argc, char **argv) {
  Grid g("12.exp2");
  g.Dump();
  return 0;
}

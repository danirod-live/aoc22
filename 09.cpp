#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

struct Movement {
  char dir;
  int count;
};

struct Pos {
  int x, y;
};

class Rope
{
public:
  Rope(const string &filename, int k);

  bool Palpar(int ax, int ay, int bx, int by);
  void EvaluateT(int ax, int ay, int bx, int by, int *cx, int *cy);

  void Dump();
  int Exec();
  void Visit(int x, int y);
private:
  int knots;
  vector<Movement> movements;
  vector<Pos> positions;
  set<string> visited;
};

bool Rope::Palpar(int ax, int ay, int bx, int by) {
  return (ax - 1 <= bx) && (bx <= ax + 1) && (ay - 1 <= by) && (by <= ay + 1);
}

void Rope::Visit(int x, int y) {
  stringstream ss;
  string str;
  ss << x << "," << y;
  ss >> str;
  visited.insert(str);
}

Rope::Rope(const string &filename, int k) {
  knots = k;
  ifstream file(filename);
  string line;

  for (int i = 0; i < k; i++) {
    Pos p = { .x = 0, .y = 0 };
    positions.push_back(p);
  }

  while (getline(file, line)) {
    char dir;
    int count;
    sscanf(line.c_str(), "%c %d", &dir, &count);
    Movement m = {
      .dir = dir,
      .count = count,
    };
    movements.push_back(m);
  }
}

int Rope::Exec() {
  visited.clear();
  for (Movement m : movements) {
    for (int i = 0; i < m.count; i++) {
      switch (m.dir) {
        case 'L': positions[0].x--; break;
        case 'R': positions[0].x++; break;
        case 'U': positions[0].y--; break;
        case 'D': positions[0].y++; break;
      }
      for (int k = 0; k < knots - 1; k++) {
        int x, y;
        EvaluateT(positions[k].x, positions[k].y, positions[k + 1].x, positions[k + 1].y, &x, &y);
        positions[k + 1].x = x;
        positions[k + 1].y = y;
      }
      Visit(positions[knots - 1].x, positions[knots - 1].y);
    }
  }
  return visited.size();
}

void Rope::EvaluateT(int ax, int ay, int bx, int by, int *cx, int *cy) {
  *cx = bx;
  *cy = by;
  if (Palpar(ax, ay, bx, by)) {
    return;
  }

  // Check if we have to move in a single direction
  if (ax == bx && ay == by + 2) {
    *cy += 1;
  }
  else if (ax == bx && ay == by - 2) {
    *cy -= 1;
  }
  else if (ay == by && ax == bx + 2) {
    *cx += 1;
  }
  else if (ay == by && ax == bx - 2) {
    *cx -= 1;
  }
  // We have to pick a corner to move.
  else if (Palpar(ax, ay, bx + 1, by + 1)) {
    *cx += 1;
    *cy += 1;
  }
  else if (Palpar(ax, ay, bx - 1, by + 1)) {
    *cx -= 1;
    *cy += 1;
  }
  else if (Palpar(ax, ay, bx - 1, by - 1)) {
    *cx -= 1;
    *cy -= 1;
  }
  else if (Palpar(ax, ay, bx + 1, by - 1)) {
    *cx += 1;
    *cy -= 1;
  }
  else {
    cout << "WHAT THE FUCK" << " ";
  }
}

void Rope::Dump() {
  for (Movement m : movements) {
    cout << m.dir << " total de " << m.count << " veces" << endl;
  }
  cout << "Visited" << endl;
  for (string s : visited) {
    cout << " " << s << endl;
  }
}

int main(int argc, char** argv)
{
  Rope r("09.txt", 2);
  cout << "P1: " << r.Exec() << endl;

  Rope r2("09.txt", 10);
  cout << "P2: " << r2.Exec() << endl;
}

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Coord {
public:
  int x, y, z;
  Coord() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
  }
  Coord(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  Coord Front() { return Coord(x, y, z + 1); }
  Coord Back() { return Coord(x, y, z - 1); }
  Coord Left() { return Coord(x - 1, y, z); }
  Coord Right() { return Coord(x + 1, y, z); }
  Coord Up() { return Coord(x, y - 1, z); }
  Coord Down() { return Coord(x, y + 1, z); }

  bool operator<(const Coord &c) const {
    return x < c.x || (x == c.x && y < c.y) || (y == c.y && z < c.z);
  }

  friend std::ostream &operator<<(std::ostream &, const Coord &);
};

std::ostream &operator<<(std::ostream &str, const Coord &coord) {
  return str << "(" << coord.x << "," << coord.y << "," << coord.z << ")";
}

int main() {
  vector<Coord> lista;
  ifstream file("18.exp");
  string line;
  while (getline(file, line)) {
    int x, y, z;
    sscanf(line.c_str(), "%d,%d,%d", &x, &y, &z);
    Coord c(x, y, z);
    lista.push_back(c);
  }

  int count = 6 * lista.size();

  for (int i = 0; i < lista.size(); i++) {
    for (int j = i + 1; j < lista.size(); j++) {
      vector<Coord> around = {
          lista[i].Front(), lista[i].Back(), lista[i].Up(),
          lista[i].Down(),  lista[i].Left(), lista[i].Right(),
      };
      for (Coord a : around) {
        Coord b = lista[j];
        if (a.x == b.x && a.y == b.y && a.z == b.z) {
          count -= 2;
        }
      }
    }
  }

  cout << "P1: " << count << endl;

  return 0;
}

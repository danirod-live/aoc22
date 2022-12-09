#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Grid
{
public:
  Grid(const string &filename);
  void P1Bruto();
  void P1();
  void P2();
  void Dump();

  int Rows() { return trees.size(); }
  int Cols() { return trees[0].size(); }
private:
  ifstream file;
  vector<vector<int>> trees;
};

Grid::Grid(const string &filename) {
  file = ifstream(filename);
  string line;
  while (getline(file, line)) {
    vector<int> row;
    for (char c : line) {
      row.push_back(c - 0x30);
    }
    trees.push_back(row);
  }
}

void Grid::P1Bruto()
{
  int total = 0;
  int rows = trees.size();
  int cols = trees[0].size();

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      bool visibleArr = true, visibleAba = true, visibleIz = true, visibleDc = true;
      int este = trees[r][c];

      for (int i = 0; visibleArr && i < r; i++) {
        if (trees[i][c] >= este) {
          visibleArr = false;
        }
      }
      for (int i = rows - 1; visibleAba && i > r; --i) {
        if (trees[i][c] >= este) {
          visibleAba = false;
        }
      }
      for (int j = 0; visibleIz && j < c; j++) {
        if (trees[r][j] >= este) {
          visibleIz = false;
        }
      }
      for (int j = cols - 1; visibleDc && j > c; --j) {
        if (trees[r][j] >= este) {
          visibleDc = false;
        }
      }

      if (visibleArr || visibleAba || visibleIz || visibleDc) {
        total++;
      }
    }
  }

  cout << "P1: " << total << endl;
}

void Grid::P1()
{
  // Prepare the array where the data will be dumped
  int rows = trees.size();
  int cols = trees[0].size();
  bool **visibles = new bool*[rows];
  for (int i = 0; i < rows; i++)
    visibles[i] = new bool[cols];

  // The edges are always visible.
  for (int c = 0; c < cols; c++) {
    visibles[0][c] = true;
    visibles[rows - 1][c] = true;
  }
  for (int r = 1; r < cols - 1; r++) {
    visibles[r][0] = true;
    visibles[r][cols - 1] = true;
  }

  // Iterate over the remaining centers looking for visible ones.
  for (int c = 1; c < cols - 1; c++) {
    int max;

    // Top to bottom.
    max = trees[0][c];
    for (int r = 1; r < rows - 1; r++) {
      if (trees[r][c] > max) {
        visibles[r][c] = true;
        max = trees[r][c];
      }
    }

    // Bottom to top
    max = trees[rows - 1][c];
    for (int r = rows - 2; r > 0; --r) {
      if (trees[r][c] > max) {
        visibles[r][c] = true;
        max = trees[r][c];
      }
    }
  }

  for (int r = 1; r < rows - 1; r++) {
    int max;

    // Left to right.
    max = trees[r][0];
    for (int c = 1; c < cols - 1; c++) {
      if (trees[r][c] > max) {
        visibles[r][c] = true;
        max = trees[r][c];
      }
    }

    // Right to left.
    max = trees[r][cols - 1];
    for (int c = cols - 2; c > 0; --c) {
      if (trees[r][c] > max) {
        visibles[r][c] = true;
        max = trees[r][c];
      }
    }
  }

  // Count the number of trues and report.
  int total = 0;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      if (visibles[r][c])
        total++;
    }
  }
  cout << "P1: " << total << endl;
}

void Grid::P2()
{
  int rows = Rows();
  int cols = Cols();
  int max = 0;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      int self = trees[r][c];

      int w = 0, a = 0, s = 0, d = 0;
      for (int i = r - 1; i >= 0; --i) {
        w++;
        if (trees[i][c] >= self) {
          break;
        }
      }
      for (int i = r + 1; i < rows; i++) {
        s++;
        if (trees[i][c] >= self) {
          break;
        }
      }
      for (int j = c - 1; j >= 0; --j) {
        a++;
        if (trees[r][j] >= self) {
          break;
        }
      }
      for (int j = c + 1; j < cols; j++) {
        d++;
        if (trees[r][j] >= self) {
          break;
        }
      }

      int score = w * a * s * d;
      if (score > max)
        max = score;
    }
  }

  cout << "P2: " << max << endl;
}

void Grid::Dump()
{
  for (vector<int> row : trees) {
    for (int col : row) {
      cout << col << " ";
    }
    cout << endl;
  }
}

int main(int argc, char** argv)
{
  Grid g("08.txt");
  g.P1Bruto();
  g.P2();
  return 0;
}

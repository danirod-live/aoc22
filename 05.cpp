#include <cstdio>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

void p1() {
  vector<stack<char>> crates = {
      /* 1 */ stack<char>({'T', 'D', 'W', 'Z', 'V', 'P'}),
      /* 2 */ stack<char>({'L', 'S', 'W', 'V', 'F', 'J', 'D'}),
      /* 3 */ stack<char>({'Z', 'M', 'L', 'S', 'V', 'T', 'B', 'H'}),
      /* 4 */ stack<char>({'R', 'S', 'J'}),
      /* 5 */ stack<char>({'C', 'Z', 'B', 'G', 'F', 'M', 'L', 'W'}),
      /* 6 */ stack<char>({'Q', 'W', 'V', 'H', 'Z', 'R', 'G', 'B'}),
      /* 7 */ stack<char>({'V', 'J', 'P', 'C', 'B', 'D', 'N'}),
      /* 8 */ stack<char>({'P', 'T', 'B', 'Q'}),
      /* 9 */ stack<char>({'H', 'G', 'Z', 'R', 'C'}),
  };

  ifstream file("05.txt");
  string line;

  while (getline(file, line)) {
    int count, from, to;
    sscanf(line.c_str(), "move %d from %d to %d", &count, &from, &to);

    for (int i = 0; i < count; i++) {
      char next = crates[from - 1].top();
      crates[from - 1].pop();
      crates[to - 1].push(next);
    }
  }

  cout << "P1: ";
  for (int i = 0; i < 9; i++) {
    cout << crates[i].top();
  }
  cout << endl;
}

void p2() {
  vector<stack<char>> crates = {
      /* 1 */ stack<char>({'T', 'D', 'W', 'Z', 'V', 'P'}),
      /* 2 */ stack<char>({'L', 'S', 'W', 'V', 'F', 'J', 'D'}),
      /* 3 */ stack<char>({'Z', 'M', 'L', 'S', 'V', 'T', 'B', 'H'}),
      /* 4 */ stack<char>({'R', 'S', 'J'}),
      /* 5 */ stack<char>({'C', 'Z', 'B', 'G', 'F', 'M', 'L', 'W'}),
      /* 6 */ stack<char>({'Q', 'W', 'V', 'H', 'Z', 'R', 'G', 'B'}),
      /* 7 */ stack<char>({'V', 'J', 'P', 'C', 'B', 'D', 'N'}),
      /* 8 */ stack<char>({'P', 'T', 'B', 'Q'}),
      /* 9 */ stack<char>({'H', 'G', 'Z', 'R', 'C'}),
  };

  ifstream file("05.txt");
  string line;

  while (getline(file, line)) {
    int count, from, to;
    sscanf(line.c_str(), "move %d from %d to %d", &count, &from, &to);

    stack<char> temp;
    for (int i = 0; i < count; i++) {
      char next = crates[from - 1].top();
      crates[from - 1].pop();
      temp.push(next);
    }
    for (int i = 0; i < count; i++) {
      char next = temp.top();
      temp.pop();
      crates[to - 1].push(next);
    }
  }

  cout << "P2: ";
  for (int i = 0; i < 9; i++) {
    cout << crates[i].top();
  }
  cout << endl;
}

int main(int argc, char **argv) {
  p1();
  p2();
  return 0;
}

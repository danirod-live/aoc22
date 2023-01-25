#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Procesador {
public:
  Procesador(const string &fname);
  void Cycle();
  void CycleUntil(int n);
  bool Done();
  long X() { return reg_x; }
  unsigned int Cycles() { return cycles; }

private:
  void LoadNextInstruction();
  void Postconditions();
  vector<string> program;
  vector<string> current;
  long reg_ip = 0;
  long reg_x = 1;
  unsigned int cycles = 0, cycle_count = 0;
};

void Procesador::CycleUntil(int n) {
  while (cycles < n) {
    Cycle();
  }
}

Procesador::Procesador(const string &fname) {
  ifstream file(fname);
  string line;
  while (getline(file, line)) {
    program.push_back(line);
  }
}

void Procesador::Cycle() {
  if (cycle_count == 0) {
    Postconditions();
    LoadNextInstruction();
  }
  cycle_count--;
  cycles++;
}

bool Procesador::Done() { return reg_ip == program.size(); }

void Procesador::Postconditions() {
  if (current.empty()) {
    return;
  }
  if (current[0] == "addx") {
    int value = atoi(current[1].c_str());
    reg_x += value;
  }
}

void Procesador::LoadNextInstruction() {
  string token, next = program[reg_ip++];
  stringstream ss(next);
  current.clear();
  while (getline(ss, token, ' ')) {
    current.push_back(token);
  }

  if (current[0] == "noop") {
    cycle_count = 1;
  } else if (current[0] == "addx") {
    cycle_count = 2;
  }
}

void P1() {
  Procesador p("10.txt");
  int acc = 0;
  for (int c = 20; c <= 220; c += 40) {
    p.CycleUntil(c);
    acc += (c * p.X());
  }
  cout << "P1: " << acc << endl;
}

void P2() {
  cout << "P2:" << endl;
  Procesador p("10.txt");
  for (int i = 0; i < 240; i++) {
    p.Cycle();
    int x = p.X() % 40;
    int coord = i % 40;
    if (x >= coord - 1 && x <= coord + 1) {
      cout << "█";
    } else {
      cout << " ";
    }
    if (i % 40 == 39) {
      cout << endl;
    }
  }
}

int main() {
  P1();
  P2();
  return 0;
}

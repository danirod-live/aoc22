#include <fstream>
#include <iostream>
#include <string>

int play1(char their, char mine) {
  int th = their - 'A';
  int mi = mine - 'X';
  int shape = 1 + mi;

  // Easy case is tie.
  if (th == mi) {
    return shape + 3;
  }

  // In case rock is 0, make rock 3 to make math work.
  if (mi == 0) {
    mi = 3;
  }

  // So it works like this: if your number is higher than theirs, you win.
  if (mi - th == 1) {
    return shape + 6;
  } else {
    return shape;
  }
}

/**
 * their: A B C (rock, paper, scissor)
 * result: X Y Z (lose, tie, win)
 */
int play2(char their, char result) {
  int th = their - 'A';
  int mi, score;
  switch (result) {
  case 'X':
    // You must lose.
    mi = th - 1;
    if (mi == -1)
      mi = 2;
    score = 0;
    break;
  case 'Y':
    // You must tie.
    mi = th;
    score = 3;
    break;
  case 'Z':
    // You must win.
    mi = th + 1;
    if (mi == 3)
      mi = 0;
    score = 6;
    break;
  }
  return score + (mi + 1);
}

int main(int argc, char **argv) {
  std::ifstream file("02.txt");
  std::string line;

  int score1 = 0;
  int score2 = 0;

  while (std::getline(file, line)) {
    score1 += play1(line.at(0), line.at(2));
    score2 += play2(line.at(0), line.at(2));
  }

  std::cout << "P1: " << score1 << std::endl;
  std::cout << "P2: " << score2 << std::endl;
}

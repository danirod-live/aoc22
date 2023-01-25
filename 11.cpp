#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Monkey {
public:
  Monkey(vector<int> initial, function<int(int)> operation, int div, int ifTrue,
         int ifFalse) {
    for (int i : initial)
      items.push(i);
    this->operation = operation;
    this->divisibility = div;
    this->ifTrue = ifTrue;
    this->ifFalse = ifFalse;
  }

  bool HasItems() { return !items.empty(); }
  void AcceptItem(int x) { items.push(x); }
  int NextItem() {
    toques++;
    int i = items.front();
    items.pop();
    return i;
  }
  function<int(int)> Operation() { return operation; }
  int Divisibility() { return divisibility; }
  int IfTrue() { return ifTrue; }
  int IfFalse() { return ifFalse; }

  int Toques() { return toques; }

private:
  int toques = 0;
  queue<int> items;
  int divisibility;
  int ifTrue, ifFalse;
  function<int(int)> operation;
};

int main() {
  vector<Monkey> monkeys = {
      // Monkey(
      //     {79, 98}, [](int o) { return o * 19; }, 23, 2, 3),
      // Monkey(
      //     {54, 65, 75, 74}, [](int o) { return o + 6; }, 19, 2, 0),
      // Monkey(
      //     {79, 60, 97}, [](int o) { return o * o; }, 13, 1, 3),
      // Monkey(
      //     {74}, [](int o) { return o + 3; }, 17, 0, 1),
      Monkey(
          {64}, [](int o) { return o * 7; }, 13, 1, 3),
      Monkey(
          {60, 84, 84, 65}, [](int o) { return o + 7; }, 19, 2, 7),
      Monkey(
          {52, 67, 74, 88, 51, 61}, [](int o) { return o * 3; }, 5, 5, 7),
      Monkey(
          {67, 72}, [](int o) { return o + 3; }, 2, 1, 2),
      Monkey(
          {80, 79, 58, 77, 68, 74, 98, 64}, [](int o) { return o * o; }, 17, 6,
          0),
      Monkey(
          {62, 53, 61, 89, 86}, [](int o) { return o + 8; }, 11, 4, 6),
      Monkey(
          {86, 89, 82}, [](int o) { return o + 2; }, 7, 3, 0),
      Monkey(
          {92, 81, 70, 96, 69, 84, 83}, [](int o) { return o + 4; }, 3, 4, 5),

  };
  for (int ronda = 0; ronda < 10000; ronda++) {
    for (int mono = 0; mono < monkeys.size(); mono++) {
      while (monkeys[mono].HasItems()) {
        int next = monkeys[mono].NextItem();
        int newValue = monkeys[mono].Operation()(next);
        newValue /= 3;
        if (newValue % monkeys[mono].Divisibility() == 0) {
          int to = monkeys[mono].IfTrue();
          monkeys[to].AcceptItem(newValue);
        } else {
          int to = monkeys[mono].IfFalse();
          monkeys[to].AcceptItem(newValue);
        }
      }
    }
  }

  vector<int> business;
  for (int mono = 0; mono < monkeys.size(); mono++) {
    business.push_back(monkeys[mono].Toques());
  }
  sort(business.begin(), business.end());
  cout << "P1: "
       << business[business.size() - 2] * business[business.size() - 1] << endl;
  return 0;
}

#include <fstream>
#include <iostream>
#include <set>

using namespace std;

int extract(string &haystack, int count) {
  set<char> characters;
  for (int i = count - 1; i < haystack.size(); i++) {
    characters.clear();
    for (int offt = count - 1; offt >= 0; --offt) {
      characters.insert(haystack[i - offt]);
    }
    if (characters.size() == count) {
      return i + 1;
    }
  }
  return -1;
}

int main(int argc, char **argv) {
  ifstream file("06.txt");
  string datastream;
  getline(file, datastream);

  cout << "P1: " << extract(datastream, 4) << endl;
  cout << "P2: " << extract(datastream, 14) << endl;

  return 0;
}

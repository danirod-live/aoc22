#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

class Valve
{
public:
    Valve(string &name, int rate, string& connects) {

    }
private:
    string name;
    int rate;
    vector<string> tunnels;
};

int main() {
    ifstream file("16.exp2");
    string line;

    while (getline(file, line)) {
        char name[3], tunnels[80];
        int rate;

        sscanf(line.c_str(), "Valve %s has flow rate=%d; tunnels lead to valves %[^\t\n]\n", name, &rate, tunnels);
        cout << "Name: " << name << endl;
        cout << "Rate: " << rate << endl;

        cout << "Tunnels: ";
        cout << tunnels << endl;
        regex tunnel_g("([A-Z]{2})");
        smatch matches;
        string tunnels_str(tunnels);
        if (regex_search(tunnels_str, matches, tunnel_g)) {
            for (int i = 1; i <= matches.size(); i++) {
                cout << matches[i] << " ";
            }
        }
        cout << endl << endl;
    }


    return 0; 
}
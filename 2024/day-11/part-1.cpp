#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <set>

using namespace std;

vector<string> stones;
size_t BLINKS = 25;

void loadData() {
  string line = "";
  ifstream ip("ip.txt");
  if(ip.is_open()) {
    while(getline(ip, line, ' ')) {
      stones.push_back(line);
    }
    ip.close();
  }
}

void getTransformation() {
    vector<string> newStones = stones;
    for(int i = 0; i < stones.size(); i++) {
        if(stol(stones[i]) == 0) {
            newStones[i] = '1';
        } else if(stones[i].size() % 2 == 0) {
            newStones[i] = stones[i].substr(0, stones[i].size() / 2);
            newStones.push_back(to_string(stol(stones[i].substr(stones[i].size() / 2, stones[i].size()))));
        } else {
            newStones[i] = to_string(stol(stones[i]) * 2024);
        }
    }
    stones = newStones;
}

int main() {
    loadData();

    for(int i = 0; i < BLINKS; i++) {
        getTransformation();
    }

    cout << stones.size() << endl;

    return 0;
}
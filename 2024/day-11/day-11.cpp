#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <map>

using namespace std;

map<string, long int> stones;
size_t BLINKS = 75;

void loadData() {
  string line = "";
  ifstream ip("ip.txt");
  if(ip.is_open()) {
    while(getline(ip, line, ' ')) {
      stones[line]++;
    }
    ip.close();
  }
}

void getTransformation() {
    map<string, long int> newStones;
    for(auto& [stone, number] : stones) {
        if(stol(stone) == 0) {
            newStones["1"] += number;
        } else if(stone.size() % 2 == 0) {
            newStones[stone.substr(0, stone.size() / 2)] += number;
            newStones[to_string(stol(stone.substr(stone.size() / 2, stone.size())))] += number;
        } else {
            newStones[to_string(stol(stone) * 2024)] += number;
        }
    }

    stones = newStones;
}

int main() {
    loadData();

    for(int i = 0; i < BLINKS; i++) {
        getTransformation();
    }

    long long int totalStones = 0;
    for(auto& [stone, number] : stones) {
        totalStones += number;
    }

    cout << totalStones << endl;

    return 0;
}
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstring>

using namespace std;

vector<vector<char>> word_search;

void loadData() {
    string line = "";
    ifstream ip("ip.txt");
    if (ip.is_open()) {
        while (getline(ip, line)) {
            vector<char> row;
            for (char c : line) {
                row.push_back(c);
            }
            word_search.push_back(row);
        }
        ip.close();
    }
}

// part 1
size_t LEN = 4;
char XMAS[5] = "XMAS";

bool checkDirection(int x, int y, int dx, int dy) {
  int boundX = x + (LEN - 1) * dx;
  int boundY = y + (LEN - 1) * dy;
  
  if(boundX < 0 || boundY < 0 || boundX >= word_search.size() || boundY >= word_search[0].size()) {
    return false;
  }

  for (int k = 0; k < LEN; k++) {
        int nx = x + k * dx;
        int ny = y + k * dy;
        if (word_search[nx][ny] != XMAS[k]) {
            return false;
        }
    }
    return true;
}

bool checkMas(int x, int y) {
  // bounds
  if(x - 1 < 0 || x + 1 >= word_search.size() || y - 1 < 0 || y + 1 >= word_search[0].size()) {
    return false;
  }

  // M.S
  // .A.
  // S.M
    if ((word_search[x - 1][y - 1] == 'M' && word_search[x + 1][y + 1] == 'S') &&
        (word_search[x - 1][y + 1] == 'M' && word_search[x + 1][y - 1] == 'S')) {
        return true;
    }

    // S.M
    // .A.
    // S.M
    if ((word_search[x - 1][y - 1] == 'S' && word_search[x + 1][y + 1] == 'M') &&
        (word_search[x - 1][y + 1] == 'S' && word_search[x + 1][y - 1] == 'M')) {
        return true;
    }

    // S.S
    // .A.
    // M.M
    if ((word_search[x - 1][y - 1] == 'S' && word_search[x + 1][y + 1] == 'M') &&
        (word_search[x - 1][y + 1] == 'M' && word_search[x + 1][y - 1] == 'S')) {
        return true;
    }

    // M.M
    // .A.
    // S.S
    if ((word_search[x - 1][y - 1] == 'M' && word_search[x + 1][y + 1] == 'S') &&
        (word_search[x - 1][y + 1] == 'S' && word_search[x + 1][y - 1] == 'M')) {
        return true;
    }

  return false;
}

int main() {
    loadData();
    int cnt = 0;

    for (int i = 0; i < word_search.size(); i++) {
        for (int j = 0; j < word_search[i].size(); j++) {
            // Check all 8 directions
            if (checkDirection(i, j, 0, 1)) cnt++;  // right
            if (checkDirection(i, j, 0, -1)) cnt++; // left
            if (checkDirection(i, j, 1, 0)) cnt++;  // down
            if (checkDirection(i, j, -1, 0)) cnt++; // up
            if (checkDirection(i, j, 1, 1)) cnt++;  // diagonal right-down
            if (checkDirection(i, j, -1, -1)) cnt++; // diagonal left-up
            if (checkDirection(i, j, 1, -1)) cnt++; // diagonal left-down
            if (checkDirection(i, j, -1, 1)) cnt++; // diagonal right-up
        }
    }

    cout << "count of XMAS: " << cnt << endl;

    cnt = 0;
    for(int i = 0; i < word_search.size(); i++) {
      for(int j = 0; j < word_search[0].size(); j++) {
        if(word_search[i][j] == 'A' && checkMas(i, j)) cnt++;
      }
    }

    cout << "count of cross MAX: " << cnt << endl;

    return 0;
}
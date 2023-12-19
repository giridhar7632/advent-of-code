#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;
vector<string> data;
vector<pair<int, int>> universe;

vector<bool> emptyRows;
vector<bool> emptyCols;

void loadData() {
  string line;
  ifstream ip("ip.txt");
  if (ip.is_open()) {

    while (getline(ip, line)) {
      data.push_back(line);
    }

    ip.close();
  }

  int n = data.size();
  int m = data[0].length();

  emptyRows.resize(n, true);
  emptyCols.resize(m, true);

  for (int i = 0; i < data.size(); i++) {
    bool rowHasChar = false;
    for (int j = 0; j < data[0].length(); j++) {
      if (data[i][j] == '#') {
        universe.push_back(make_pair(i, j));
      }
      if (data[i][j] != '.') {
        rowHasChar = true;
        emptyCols[j] = false;
      }
    }
    if (rowHasChar) {
      emptyRows[i] = false;
    }
  }
}

void swap(int &a, int &b) {
  int temp = a;
  a = min(a, b);
  b = max(temp, b);
}

int getDistance(pair<int, int> &a, pair<int, int> &b) {
  int i1, i2, j1, j2;
  tie(i1, j1) = a;
  tie(i2, j2) = b;

  swap(i1, i2);
  swap(j1, j2);

  int dist = 0;
  for (int i = i1; i < i2; i++) {
    dist += 1;
    if (emptyRows[i]) {
      // dist += 1;
      dist += 999999;
    }
  }

  for (int j = j1; j < j2; j++) {
    dist += 1;
    if (emptyCols[j]) {
      // dist += 1;
      dist += 999999;
    }
  }

  return dist;
}

int main() {
  loadData();
  long int sum = 0;

  for (int i = 0; i < universe.size(); i++) {
    for (int j = i + 1; j < universe.size(); j++) {
      int d = getDistance(universe[i], universe[j]);
      sum += d;
    }
  }

  cout << "grand total: " << sum;

  return 0;
}
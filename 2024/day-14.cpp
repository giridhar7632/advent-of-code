#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
vector<string> data;

void loadData() {
  string line;
  ifstream ip("ip.txt");
  if (ip.is_open()) {

    while (getline(ip, line)) {
      data.push_back(line);
    }

    ip.close();
  }
}

/*
// part-1
int rolledColumn(int j) {
  int i = 0, ans = 0;
  int n = data.size();
  while (i < n) {
    while (i < n && data[i][j] == '#') {
      i++;
    }

    int cnt = 0, start = i;
    while (i < n && data[i][j] != '#') {
      if (data[i][j] == 'O') {
        cnt++;
      }
      i++;
    }

    for (int ii = start; ii < start + cnt; ii++) {
      ans += n - ii;
    }
  }

  return ans;
}
*/

// start: part-2
int totalLoad(vector<string> &grid) {
  int sum = 0;
  int n = grid.size(), m = grid[0].length();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 'O') {
        sum += n - i;
      }
    }
  }
  return sum;
}

string get_hash(vector<string> &grid) {
  string hash;
  for (auto &line : grid) {
    hash += line;
  }
  return hash;
}

vector<string> rollOnce(vector<string> &grid) {
  int n = grid.size(), m = grid[0].length();

  for (int j = 0; j < m; j++) {
    int i = 0;
    while (i < n) {
      while (i < n && grid[i][j] == '#') {
        i++;
      }

      int cnt = 0, start = i;
      while (i < n && grid[i][j] != '#') {
        if (grid[i][j] == 'O') {
          cnt++;
        }
        i++;
      }

      for (int ii = start; ii < start + cnt; ii++) {
        grid[ii][j] = 'O';
      }

      for (int ii = start + cnt; ii < i; ii++) {
        grid[ii][j] = '.';
      }
    }
  }

  return grid;
}

vector<string> rotate90Deg(vector<string> &grid) {
  int n = grid.size(), m = grid[0].length();
  vector<string> newGrid(n, string(m, '.'));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      newGrid[i][j] = grid[j][m - i - 1];
    }
  }

  return newGrid;
}

vector<string> rotate(vector<string> &grid, int i) {
  vector<string> newGrid = grid;
  for (int k = 0; k < i % 4; k++) {
    newGrid = rotate90Deg(newGrid);
  }

  return newGrid;
}

vector<string> doCycle(vector<string> &grid) {
  vector<string> newGrid = grid;
  for (int i = 0; i < 4; i++) {
    newGrid = rotate(newGrid, 4 - (i % 4));
    newGrid = rollOnce(newGrid);
    newGrid = rotate(newGrid, i % 4);
  }

  return newGrid;
}
// end

int main() {
  loadData();
  vector<string> grid = data;
  unordered_map<string, int> seen;
  unordered_map<int, vector<string>> cycle2Grid;

  // start: part-2
  for (int cycle = 0; cycle < 1000000000; cycle++) {
    grid = doCycle(grid);
    string h = get_hash(grid);
    if (seen.find(h) != seen.end()) {
      int period = cycle - seen[h];
      vector<string> finalGrid =
          cycle2Grid[(1000000000 - 1 - seen[h]) % period + seen[h]];
      cout << "grand total: " << totalLoad(finalGrid) << endl;
      break;
    }
    seen[get_hash(grid)] = cycle;
    cycle2Grid[cycle] = grid;
  }
  // end

  return 0;
}

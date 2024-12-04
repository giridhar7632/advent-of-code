#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
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

int getTiles(vector<int> start) {
  set<vector<int>> visited;
  queue<vector<int>> q;
  q.push(start);

  while (!q.empty()) {
    vector<int> state = q.front();
    q.pop();
    int x = state[0], y = state[1], dx = state[2], dy = state[3];

    x += dx;
    y += dy;

    if (x < 0 || x >= data.size() || y < 0 || y >= data[0].length()) {
      // out of bounds
      continue;
    }
    char c = data[x][y];
    if (c == '.' || (c == '-' && dy != 0) || (c == '|' && dx != 0)) {
      vector<int> new_state = {x, y, dx, dy};
      if (visited.count(new_state) == 0) {
        visited.insert(new_state);
        q.push(new_state);
      }
    } else if (c == '/') {
      vector<int> new_state = {x, y, -dy, -dx};
      if (visited.count(new_state) == 0) {
        visited.insert(new_state);
        q.push(new_state);
      }
    } else if (c == '\\') {
      vector<int> new_state = {x, y, dy, dx};
      if (visited.count(new_state) == 0) {
        visited.insert(new_state);
        q.push(new_state);
      }
    } else {
      // hit the splitter
      vector<pair<int, int>> dirs;
      if (c == '|') {
        dirs = {{1, 0}, {-1, 0}};
      } else {
        dirs = {{0, 1}, {0, -1}};
      }

      for (auto &dir : dirs) {
        vector<int> new_state = {x, y, dir.first, dir.second};
        if (visited.count(new_state) == 0) {
          visited.insert(new_state);
          q.push(new_state);
        }
      }
    }
  }

  set<pair<int, int>> coords;
  for (auto state : visited) {
    coords.insert({state[0], state[1]});
  }

  return coords.size();
}

int main() {
  loadData();
  int maxVal = 0;
  for (int i = 0; i < data.size(); i++) {
    maxVal = max(maxVal, getTiles({i, -1, 0, 1}));
    maxVal = max(maxVal, getTiles({i, int(data[0].length()), 0, -1}));
  }
  for (int j = 0; j < data.size(); j++) {
    maxVal = max(maxVal, getTiles({-1, j, 1, 0}));
    maxVal = max(maxVal, getTiles({int(data.size()), j, -1, 0}));
  }
  cout << "grand total: " << maxVal << endl;
  return 0;
}

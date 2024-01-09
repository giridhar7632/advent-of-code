#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
vector<string> data;

// dikstras

vector<string> loadData() {
  string line;
  ifstream ip("ip.txt");
  if (ip.is_open()) {

    while (getline(ip, line)) {
      data.push_back(line);
    }

    ip.close();
  }

  return data;
}

int main() {
  loadData();
  set<vector<int>> seen;

  priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
  pq.push({0, 0, 0, 0, 0, 0});

  while (!pq.empty()) {
    vector<int> curr = pq.top();
    pq.pop();

    int hl = curr[0], x = curr[1], y = curr[2], dx = curr[3], dy = curr[4],
        n = curr[5];

    // cout << hl << " " << x << " " << y << " " << dx << " " << dy << " " << n
    //      << endl;
    if (x == data.size() - 1 && y == data[0].length() - 1) {
      cout << "total: " << hl << endl;
      break;
    }

    if (seen.count({x, y, dx, dy, n})) {
      continue;
    }

    seen.insert({x, y, dx, dy, n});
    if (n < 3 && (dx != 0 || dy != 0)) {
      int nx = x + dx, ny = y + dy;
      if (0 <= nx && nx < data.size() && 0 <= ny && ny < data[0].length()) {
        int newHl = data[nx][ny] - '0';
        cout << "seen" << endl;
        pq.push({hl + newHl, nx, ny, dx, dy, n + 1});
      }
    }

    for (pair<int, int> dir :
         vector<pair<int, int>>{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}) {
      int ndx = dir.first, ndy = dir.second;
      if (dir != make_pair(dx, dy) && dir != make_pair(-dx, -dy)) {
        int nx = x + ndx, ny = y + ndy;
        if (0 <= nx && nx < data.size() && 0 <= ny && ny < data[0].length()) {
          int newHl = data[nx][ny] - '0';
          cout << "added" << endl;
          pq.push({hl + newHl, nx, ny, ndx, ndy, 1});
        }
      }
    }

    // cout << "grand total: " << sum;
  }
  return 0;
}

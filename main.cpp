#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
vector<string> data;
const vector<int> leftD = {0, -1};
const vector<int> rightD = {0, 1};
const vector<int> up = {-1, 0};
const vector<int> down = {1, 0};
const unordered_map<char, vector<vector<int>>> lookup = {
    {'|', {up, down}},  {'-', {leftD, rightD}}, {'L', {up, rightD}},
    {'J', {up, leftD}}, {'7', {down, leftD}},   {'F', {down, rightD}}, {'.', {}}};

vector<vector<int>> getDifferentials(const vector<int> &pos);

string toString(const pair<int, int> &p) {
  stringstream ss;
  ss << "(" << p.first << ", " << p.second << ")";
  return ss.str();
}

pair<int, int> toPair(const string &s) {
  int x, y;
  char c;
  sscanf(s.c_str(), "(%d, %d)", &x, &y);
  return make_pair(x, y);
}

pair<int, int> toPair(const vector<int> &v) {
  return make_pair(v[0], v[1]);
}

void printPair(const pair<int, int> &p) {
  cout << "(" << p.first << ", " << p.second << ")";
}

vector<int> add(const vector<int> &vec1, const vector<int> &vec2) {
  vector<int> result(vec1.size());

  for (int i = 0; i < vec1.size(); ++i) {
    result[i] = vec1[i] + vec2[i];
  }

  return result;
}

int max_element(const vector<vector<int>> &v) {
  vector<int> inner_maxs;
  for (const auto &inner_v : v) {
    inner_maxs.push_back(*max_element(inner_v.begin(), inner_v.end()));
  }
  return *max_element(inner_maxs.begin(), inner_maxs.end());
}

vector<vector<int>> getNeighbours(const vector<int> &pos) {
  vector<vector<int>> neighbours;
  for (auto &i : getDifferentials(pos)) {
    vector<int> temp = add(pos, i);
    if (!(temp[0] >= 0 && temp[0] < data.size() && temp[1] >= 0 &&
          temp[1] < data[0].length())) {
      continue;
    } else {
      neighbours.push_back(temp);
    }
  }

  return neighbours;
}

vector<vector<int>> getDifferentials(const vector<int> &pos) {
  char c = data[pos[0]][pos[1]];
  vector<vector<int>> res;

  if (c == 'S') {
    cout << "found S" << endl;
    for (auto &i : {down, up, rightD, leftD}) {
      vector<int> temp = add(pos, i);
      if (!(temp[0] >= 0 && temp[0] < data.size() && temp[1] >= 0 &&
            temp[1] < data[0].length())) {
        continue;
      }

      vector<vector<int>> tempNeighbours = getNeighbours(temp);
      if (find(tempNeighbours.begin(), tempNeighbours.end(), pos) !=
          tempNeighbours.end()) {
        res.push_back(i);
      }
    }

    return res;
  }

  return lookup.at(c);
}

pair<int, int> getStartPos() {
  cout << "getting start pipe" << endl;

  for (int i = 0; i < data.size(); ++i) {
    for (int j = 0; j < data[i].length(); j++) {
      if (data[i][j] == 'S') {
        cout << "found S at " << i << ", " << j << endl;
        return make_pair(i, j);
      }
    }
  }

  return make_pair(-1, -1);
}

vector<string> loadData() {
  string line;
  ifstream ip("ip.txt");
  if (ip.is_open()) {

    while (getline(ip, line)) {
      data.push_back(line);
      cout << line << endl;
    }

    ip.close();
  }

  return data;
}

int getMaxLength() {
  cout << "getting length" << endl;
  set<pair<int, int>> visited;
  unordered_map<string, int> distances;
  queue<pair<pair<int, int>, int>> q;

  q.push(make_pair(getStartPos(), 0));

  while (!q.empty()) {
    cout << "queue size: " << q.size() << endl;
    pair<int, int> curr;
    int dist;
    tie(curr, dist) = q.front();
    q.pop();

    if (visited.find(curr) != visited.end()) {
      continue;
    }

    visited.insert(curr);
    distances[toString(curr)] = dist;

    for (const auto &neighbour : getNeighbours(vector<int>{curr.first, curr.second})) {
      if (visited.count(make_pair(neighbour[0], neighbour[1])) == 0) {
        q.emplace(make_pair(toPair(neighbour), dist + 1));
      }
    }
  }

  int max_value = 0;
  for (const auto &kv : distances) {
    max_value = max(max_value, kv.second);
  }

  cout << "distances: " << endl;
  for (const auto &kv : distances) {
    cout << kv.first << ": " << kv.second << endl;
  }

  return max_value;
}

int main() {
  cout << "hello world" << endl;
  loadData();
  int maxDistance = getMaxLength();

  cout << "max distance: " << maxDistance;

  return 0;
}
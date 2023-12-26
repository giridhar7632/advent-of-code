#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
vector<string> data;
vector<vector<int>> metadata;

void addMetadata(string line) {
  vector<int> numbers;
  stringstream ss(line);
  while (ss.good()) {
    string substr;
    getline(ss, substr, ',');
    numbers.push_back(stoi(substr));
  }

  metadata.push_back(numbers);
}

void loadData() {
  string line;
  ifstream ip("ip.txt");
  if (ip.is_open()) {

    while (getline(ip, line)) {
      data.push_back(line.substr(0, line.find(" ")));
      addMetadata(line.substr(line.find(" ") + 1));
    }

    ip.close();
  }
}

bool isValid(vector<int> &line, vector<int> &target) {
  int n = line.size();
  vector<int> runs;

  int i = 0;
  while (i < n) {
    while (i < n && !line[i]) {
      i++;
    }
    if (i == n) {
      break;
    }

    int j = i;
    int c = 0;
    while (j < n && line[j]) {
      j++;
      c++;
    }

    runs.push_back(c);
    i = j;
  }

  return runs == target;
}

int noOfWays(string &s, vector<int> &target) {
  vector<int> line;
  vector<int> idxs;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '.') {
      line.push_back(0);
    }

    if (s[i] == '?') {
      line.push_back(-1);
      idxs.push_back(i);
    }

    if (s[i] == '#') {
      line.push_back(1);
    }
  }

  int cnt = 0;
  for (int mask = 0; mask < (1 << idxs.size()); mask++) {
    vector<int> line_copy = line;
    for (int i = 0; i < idxs.size(); i++) {
      if (mask & (1 << i)) {
        line_copy[idxs[i]] = 0;
      } else {
        line_copy[idxs[i]] = 1;
      }
    }

    if (isValid(line_copy, target)) {
      cnt++;
    }
  }
  return cnt;
}

int main() {
  loadData();
  int sum = 0;

  for (int i = 0; i < data.size(); i++) {
    sum += noOfWays(data[i], metadata[i]);
  }

  cout << "grand total: " << sum;

  return 0;
}
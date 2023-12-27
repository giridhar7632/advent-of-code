#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
vector<string> data;
vector<vector<pair<string, int>>> boxes(256);

void loadData() {
  string line;
  ifstream ip("ip.txt");
  if (ip.is_open()) {

    while (getline(ip, line)) {
      string temp;
      stringstream ss(line);
      while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        data.push_back(substr);
      }
    }

    ip.close();
  }
}

int getHash(string ip) {
  int curr = 0;
  for (char c : ip) {
    curr += c;
    curr *= 17;
    curr %= 256;
  }

  return curr;
}

void loadLens(string &s) {
  pair<string, int> lens;
  size_t equalPos = s.find('=');
  if (equalPos != string::npos) {
    lens = make_pair(s.substr(0, equalPos), stoi(s.substr(equalPos + 1)));

    int hash = getHash(lens.first);
    for (pair<string, int> &p : boxes[hash]) {
      if (p.first == lens.first) {
        p.second = lens.second;
        return;
      }
    }

    boxes[hash].push_back(lens);

    return;
  } else {
    size_t minusPos = s.find('-');
    if (minusPos != string::npos) {
      string label = s.substr(0, minusPos);
      int hash = getHash(label);
      for (int i = 0; i < boxes[hash].size(); i++) {
        if (boxes[hash][i].first == label) {
          boxes[hash].erase(boxes[hash].begin() + i);
          return;
        }
      }
    }
  }
}

int main() {
  loadData();
  long sum = 0;

  for (string &str : data) {
    // part-1
    // int val = getHash(str);
    // sum += val;

    // part-2
    loadLens(str);
  }

  for (int i = 0; i < 256; i++) {
    if (boxes[i].size() != 0) {
      for (int j = 0; j < boxes[i].size(); j++) {
        sum += (i + 1) * (j + 1) * boxes[i][j].second;
      }
    }
  }

  cout << "grand total: " << sum;

  return 0;
}

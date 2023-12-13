#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
vector<vector<int>> data;

vector<int> stringToVector(string &line) {
  vector<int> values;
  stringstream ss(line);
  int value;
  while (ss >> value) {
    values.push_back(value);
  }

  // start: part 2
  reverse(values.begin(), values.end());
  // end

  return values;
}

vector<vector<int>> loadData() {
  string line;
  ifstream ip("ip.txt");
  if (ip.is_open()) {

    while (getline(ip, line)) {
      data.push_back(stringToVector(line));
    }

    ip.close();
  }

  return data;
}

int getTheNextValue(const vector<int> &history) {
  vector<vector<int>> differences;
  differences.push_back(history);
  vector<int> tempHistory = history;

  while (true) {
    bool allZeros = true;
    vector<int> newDifferences(tempHistory.size() - 1);

    for (int i = 0; i < tempHistory.size() - 1; i++) {
      newDifferences[i] = tempHistory[i + 1] - tempHistory[i];
      if (newDifferences[i] != 0) {
        allZeros = false;
      }
    }
    differences.push_back(newDifferences);

    if (allZeros) {
      break;
    }

    tempHistory = newDifferences;
  }

  differences.back().push_back(0);
  for (int i = differences.size() - 2; i >= 0; --i) {
    if (!differences[i].empty() && !differences[i + 1].empty()) {
      differences[i].push_back(differences[i].back() +
                               differences[i + 1].back());
    }
  }

  return differences[0].back();
}

int main() {
  loadData();
  int sum = 0;

  for (auto &history : data) {
    sum += getTheNextValue(history);
  }

  cout << "grand total: " << sum;

  return 0;
}
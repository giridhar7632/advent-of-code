#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
vector<vector<string>> patterns;

bool isHorizontalReflection(const vector<string> &pattern, int i) {
  int n = pattern.size(), m = pattern[0].length();
  for (int j = 0; j < m; ++j) {
    for (int k1 = 0; k1 < n; ++k1) {
      int k2 = i * 2 + 1 - k1;
      if (k2 >= 0 && k2 < n && pattern[k1][j] != pattern[k2][j]) {
        return false;
      }
    }
  }
  return true;
}

vector<string> transpose(const vector<string> &pattern) {
  int n = pattern.size(), m = pattern[0].length();
  vector<string> transposed(m);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      transposed[i] += pattern[j][i];
    }
  }
  return transposed;
}

int reflectionSummary(const vector<string> &pattern) {
  int n = pattern.size(), m = pattern[0].length();

  int horizontal = -1;
  for (int i = 0; i < n - 1; ++i) {
    if (isHorizontalReflection(pattern, i)) {
      horizontal = i;
      break;
    }
  }

  int vertical = -1;
  vector<string> transposed = transpose(pattern);
  for (int j = 0; j < m - 1; ++j) {
    if (isHorizontalReflection(transposed, j)) {
      vertical = j;
      break;
    }
  }

  assert(vertical == -1 || horizontal == -1); // Ensure only one reflection
  return vertical + 1 + 100 * (horizontal + 1);
}

void loadData() {
  string line;
  ifstream ip("ip.txt");
  if (ip.is_open()) {
    patterns.push_back({});

    while (getline(ip, line)) {
      if (line.empty()) {
        patterns.push_back({});
      } else {
        patterns.back().push_back(line);
      }
    }

    ip.close();
  }
}

int main() {
  loadData();
  int sum = 0;

  for (const vector<string> &pattern : patterns) {
    sum += reflectionSummary(pattern);
  }

  cout << "grand total: " << sum;

  return 0;
}

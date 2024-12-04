#include <algorithm>
#include <cassert>
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

string unfoldData(string line, bool isMeta) {
  string repeated_parts = "";
  for (int i = 0; i < 5; i++) {
    repeated_parts += (i > 0 ? isMeta ? "," : "?" : "") + line;
  }
  return repeated_parts;
}

void loadData() {
  string line;
  ifstream ip("ip.txt");
  if (ip.is_open()) {

    while (getline(ip, line)) {
      data.push_back(unfoldData(line.substr(0, line.find(" ")), 0));
      addMetadata(unfoldData(line.substr(line.find(" ") + 1), 1));
    }

    ip.close();
  }
}

/*
// for part-1
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
*/

long long noOfWays(string &s, vector<int> targetRuns) {
  targetRuns.push_back(0);
  int maxRun = *max_element(targetRuns.begin(), targetRuns.end());
  s += '.';

  int n = s.length();
  int m = targetRuns.size();
  vector<vector<vector<long long>>> dp(
      n, vector<vector<long long>>(m, vector<long long>(maxRun + 1, -1)));

  for (int i = 0; i < n; i++) {
    char x = s[i];

    for (int j = 0; j < m; j++) {
      for (int k = 0; k <= targetRuns[j]; k++) {
        // base case
        if (i == 0) {
          if (j != 0) {
            dp[i][j][k] = 0;
            continue;
          }

          if (x == '#') {
            if (k != 1) {
              dp[i][j][k] = 0;
              continue;
            }

            dp[i][j][k] = 1;
            continue;
          }

          if (x == '.') {
            if (k != 0) {
              dp[i][j][k] = 0;
              continue;
            }

            dp[i][j][k] = 1;
            continue;
          }

          if (x == '?') {
            if (k < 0 || k > 1) {
              dp[i][j][k] = 0;
              continue;
            }

            dp[i][j][k] = 1;
            continue;
          }
        }

        // process for '.'
        long long ansDot;
        if (k != 0) {
          ansDot = 0;
        } else if (j > 0) {
          assert(k == 0);
          ansDot = dp[i - 1][j - 1][targetRuns[j - 1]];
          ansDot += dp[i - 1][j][0];
        } else {
          ansDot = (s.substr(0, i).find("#") == string::npos) ? 1 : 0;
        }

        // process for '#'
        long long ansHash;
        if (k == 0) {
          ansHash = 0;
        } else {
          ansHash = dp[i - 1][j][k - 1];
        }

        if (x == '.') {
          dp[i][j][k] = ansDot;
        } else if (x == '#') {
          dp[i][j][k] = ansHash;
        } else {
          dp[i][j][k] = ansDot + ansHash;
        }
      }
    }
  }

  return dp[n - 1][m - 1][0];
}

int main() {
  loadData();
  long long sum = 0;

  // for (const auto &line : data) {
  //   cout << line << endl;
  // }

  // for (const auto &line : metadata) {
  //   for (int i : line) {
  //     cout << i << " ";
  //   }
  //   cout << endl;
  // }

  for (int i = 0; i < data.size(); i++) {
    long long ans = noOfWays(data[i], metadata[i]);
    if (ans < 0) {
      cout << data[i] << " : " << ans << endl;
    }
    sum += ans;
  }

  cout << "grand total: " << sum;

  return 0;
}
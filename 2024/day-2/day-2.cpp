#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
vector<vector<int> > data;

void loadData() {
  string line;
  ifstream ip("ip.txt");
  if (ip.is_open()) {

    while (getline(ip, line)) {
        string level;
        vector<int> report;
        stringstream ss(line);
        while (getline(ss, level, ' ')) {
            report.push_back(stoi(level));
        }

        data.push_back(report);
    }

    ip.close();
  }
}

// part-1: a report only counts as safe if both of the following are true:
// 1. The levels are either all increasing or all decreasing
// 2. Any two adjacent levels differ by at least one and at most three
bool isSafe(vector<int> arr) {
    int n = arr.size();
    bool isIncreasing = true;
    bool isDecreasing = true;

    for (int i = 0; i < n - 1; i++) {
        if (arr[i] >= arr[i + 1]) {
            isIncreasing = false;
        }
        if (arr[i] <= arr[i + 1]) {
            isDecreasing = false;
        }
        if (abs(arr[i] - arr[i + 1]) > 3) {
            return false;
        }
    }

    return isIncreasing || isDecreasing;
}

// part-2: Now, the same rules apply as before, except if removing a single level from an unsafe report would make it safe, the report instead counts as safe.
bool canBeSafe(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        vector<int> temp = arr;
        temp.erase(temp.begin() + i);
        if (isSafe(temp)) {
            return true;
        }
    }

    return false;
}

int main() {
  loadData();
  int cnt = 0;

  for (int i = 0; i < data.size(); i++) {
    if (isSafe(data[i])) { // part - 1
      cnt++;
    } else if (canBeSafe(data[i])) { // part - 2
      cnt++;
    }
  }

  cout << "total safe reports: " << cnt;

  return 0;
}
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
vector<string> data;

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
  int sum = 0;

  cout << "grand total: " << sum;

  return 0;
}
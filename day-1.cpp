#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string line;
  vector<int> num;
  int sum = 0;
  ifstream ip("ip.txt");
  if (ip.is_open()) {

    while (getline(ip, line)) {
      for (char c : line) {
            if (c >= '0' && c <= '9') {
                num.push_back((int)c - (int)'0');
            }
      }

      sum += (num.front()*10 + num.back());
      num.clear();
    }

    ip.close();
  }


    cout << "grand total: " << sum;
    return 0;
}

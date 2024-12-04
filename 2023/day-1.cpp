#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

const map<string, int> numberMap = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9},
    {"zero", 0},
};

int getCalibrationValue(string data) {
    regex pattern(R"((\d+)|one|two|three|four|five|six|seven|eight|nine|zero)");
    smatch matches;
    vector<int> nums;

    cout << data << endl;

    for (sregex_iterator it(data.begin(), data.end(), pattern); it != sregex_iterator(); ++it) {
        smatch match = *it;
        string token = match.str();

        auto temp = numberMap.find(token);
        if (temp != numberMap.end()) {
          nums.push_back(temp->second);
            // cout << "second: " << temp->second << " ";
        } else if (all_of(token.begin(), token.end(), ::isdigit)) {
            for (char digit : token) {
                nums.push_back((int)digit - (int)'0');
                // cout << "digit: " << digit << " ";
            }
        }
    }

  // cout << endl << nums.front()*10 + nums.back() << endl;
  return (nums.front()*10 + nums.back());
}

int main() {
  string line;
  int sum = 0;
  ifstream ip("ip.txt");
  if (ip.is_open()) {

    while (getline(ip, line)) {
      // for (char c : line) {
      //       if (c >= '0' && c <= '9') {
      //           num.push_back((int)c - (int)'0');
      //       }
      // }

      sum += getCalibrationValue(line);

      // sum += (num.front()*10 + num.back());
      // num.clear();
    }

    ip.close();
  }


    cout << "grand total: " << sum;
    return 0;
}

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>

using namespace std;
string data;

void loadData() {
  string line = "";
  ifstream ip("ip.txt");
  if (ip.is_open()) {

    while (getline(ip, line)) {
      data += line;
    }

    ip.close();
  }
}

int main() {
  loadData();

  long int sum = 0;
  regex mulRegex("mul\\((\\d+),\\s*(\\d+)\\)|do\\(\\)|don\\'t\\(\\)");
  smatch matches;
  bool disabled = false;
  bool enabled = true;

  auto begin = sregex_iterator(data.begin(), data.end(), mulRegex);
  auto end = sregex_iterator();

  for (sregex_iterator i = begin; i != end; ++i) {
    matches = *i;
    int idx = 0;
    if(matches[0].str() == "don't()") {
      disabled = true;
    } else if(matches[0].str() == "do()") {
      disabled = false;
    } else {
      if (disabled) {
        continue;
      }

      int a = stoi(matches[1].str());
      int b = stoi(matches[2].str());
      sum += a * b;
    }
  }

  cout << sum << endl;
  return 0;
}
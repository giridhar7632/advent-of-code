#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>
#include <numeric>

using namespace std;

string directions = "";
vector<string> nodes;
unordered_map<string, pair<string, string>> data;

void loadData() {
  string line;
  ifstream ip("ip.txt");
  if (ip.is_open()) {
    bool started_mapping = false;

    while (getline(ip, line)) {
      if (line.empty()) {
        started_mapping = true;
        continue;
      }

      if (!started_mapping) {
        directions += line;
      } else {
        regex pattern(R"(^(\w+) = \((\w+), (\w+)\)$)");
        smatch match;
        if (regex_match(line, match, pattern)) {
          data[match[1]] = make_pair(match[2], match[3]);
          if (match.str(1)[2] == 'A') {
            nodes.push_back(match[1]);
          }
        }
      }
    }

    ip.close();
  } else {
    cout << "Unable to open file";
    exit(1);
  }
}

// start : part 2
long checkNode(string node) {
  long count = 0;
  while (node[2] != 'Z') {
    node = directions[count % directions.size()] == 'R'
               ? data[node].second
               : data[node].first;

    count++;
  }

  return count;
}

long lcm(long a, long b) {
  long temp = std::__gcd(a, b);

  return temp ? (a / temp * b) : 0;
}
// end

int main() {
  loadData();
  vector<long> steps;

  // string current = "AAA";
  // while (current != "ZZZ") {
  //   current = directions[steps % directions.size()] == 'R' ?
  //   data[current].second : data[current].first; 
  //   steps++;
  // }

  // start : part 2
  for(string node : nodes) {
    steps.push_back(checkNode(node));
  }

  cout << "steps: " << endl;
  for (long step : steps) {
    cout << step << " | ";
  }
  cout << endl;


  long long totalSteps = accumulate(steps.begin(), steps.end(), 1, [](long a, long b) {
    return lcm(a, b);
  });
  // end

  cout << "Total steps: " << totalSteps << endl;

  return 0;
}

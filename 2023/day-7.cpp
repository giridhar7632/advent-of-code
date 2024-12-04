#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
vector<string> hands;
unordered_map<string, int> data;
// string labels = "AKQJT98765432";
string labels = "AKQT98765432J";

int getCardType(string hand) {
  unordered_map<char, int> counts;
  int j = 0;
  for (char c : hand) {
    if (c == 'J') {
      j++;
    } else {
      counts[c]++;
    }
  }

  vector<int> values;
  for (const auto &pair : counts) {
    values.push_back(pair.second);
  }
  sort(values.begin(), values.end());
  int vSize = values.size();

  /*
  if (values == vector<int>{1, 1, 1, 2}) {
    return 2; // one pair
  } else if (values == vector<int>{1, 2, 2}) {
    return 3; // two pair
  } else if (values == vector<int>{1, 1, 3}) {
    return 4; // three of a kind
  } else if (values == vector<int>{2, 3}) {
    return 5; // full house
  } else if (values == vector<int>{1, 4}) {
    return 6; // four of a kind
  } else if (values == vector<int>{5}) {
    return 7; // five of a kind
  } else {
    return 1;
  }
  */
  if (values.back() + j >= 4 || j >= 4) {
    return 6; // four of a kind
  } else if (values.back() + j >= 5 || j >= 5) {
    return 7;
  } else if (values.back() + j >= 3) {
    int remJ = values.back() + j - 3;
    if (vSize >= 2 && values[vSize - 2] + remJ >= 2 || remJ >= 2) {
      return 5; // full house
    }
    return 4; // three of a kind
  } else if (values.back() + j >= 2) {
    int remJ = values.back() + j - 2;
    if (vSize >= 2 && values[vSize - 2] + remJ >= 2 || remJ >= 2) {
      return 3; // two pair
    }
    return 2; // one pair
  }
  return 1;
}

bool compare(const string &a, const string &b) {
  int aType = getCardType(a);
  int bType = getCardType(b);

  // cout << a << ", " << b << " : " << aType << ", " << bType << endl << endl;

  if (aType == bType) {
    if (a == b) {
      cout << "equal" << endl;
      return true;
    }
    for (int i = 0; i < a.length(); i++) {
      if (labels.find(a[i]) == labels.find(b[i])) {
        continue;
      }
      return labels.find(a[i]) > labels.find(b[i]);
    }
  }

  return aType < bType;
}

void loadData() {
  string line;
  ifstream ip("ip.txt");
  if (ip.is_open()) {

    while (getline(ip, line)) {
      istringstream iss(line);
      string hand;
      int bid;
      iss >> hand >> bid;
      hands.push_back(hand);
      data[hand] = bid;
    }

    ip.close();
  } else {
    cout << "Unable to open file";
    exit(1);
  }
}

int main() {
  loadData();

  sort(hands.begin(), hands.end(), compare);

  double total = 0;
  for (int i = 0; i < hands.size(); i++) {
    // cout << "hand: " << hands[i] << " bid: " << data[hands[i]] << " rank: "
    // << i + 1
    //      << endl;
    total += data[hands[i]] * (i + 1);
  }

  cout << "grand total: " << total << endl; // 251515496

  return 0;
}

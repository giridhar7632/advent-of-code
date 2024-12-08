#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;
unordered_map<long int, vector<long int>> equations;

void loadData() {
    string line = "";
    ifstream ip("ip.txt");

    if (ip.is_open()) {
        while (getline(ip, line)) {
            // 3267: 81 40 27
            int pos = line.find(":");
            long int key = stol(line.substr(0, pos));
            vector<long int> numbers;
            string token;
            istringstream tokenStream(line.substr(pos + 1));
            while (getline(tokenStream, token, ' ')) {
                if (token != "") {
                    numbers.push_back(stol(token));
                }
            }
            equations[key] = numbers; // Store the key-value pair in the map
        }
        ip.close();
    }
}

bool solve(long int curr, int currIdx, const long int& expected, const vector<long int>& numbers) {
    if(curr > expected) {
        return false;
    }

    if(currIdx == numbers.size() - 1) {
        return curr == expected;
    }

    if(solve(curr + numbers[currIdx + 1], currIdx + 1, expected, numbers)) {
        return true;
    }

    if(solve(curr * numbers[currIdx + 1], currIdx + 1, expected, numbers)) {
        return true;
    }

// concat numbers
    if(solve(stol(to_string(curr) + to_string(numbers[currIdx + 1])), currIdx + 1, expected, numbers)) {
        return true;
    }

    return false;
}

bool canSolve(const long int& value, const vector<long int>& numbers) {
    return solve(numbers[0], 0, value, numbers);
}

int main() {
    loadData();

    long long int total = 0;
    for (auto const& [key, numbers] : equations) {
        if(canSolve(key, numbers)) {
            total += key;
        }
    }

    cout << "calibration: " << total << endl;

    return 0;
}
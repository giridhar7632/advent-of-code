#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <bits/stdc++.h>

using namespace std;
vector<pair<int, int>> rules;
vector<vector<int>> updates;

void loadData() {
    string line = "";
    bool areUpdates = false;
    ifstream ip("ip.txt");
    if (ip.is_open()) {
        while (getline(ip, line)) {
            if(line == "") {
                areUpdates = true;
            }

            if(areUpdates) {
                string level;
                vector<int> update;
                stringstream ss(line);
                while (getline(ss, level, ',')) {
                    update.push_back(stoi(level));
                }
                updates.push_back(update);
            } else {
                stringstream ss(line);
                int a, b;
                char dem;
                ss >> a >> dem >> b;
                rules.push_back(make_pair(a, b));
            }
        }
        ip.close();
    }
}

size_t getIndex(const vector<int>& vec, int element) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == element) {
            return i;
        }
    }
    return -1;
}

bool isRightUpdate(const vector<int>& arr) {
    for(pair<int, int> rule: rules) {
        size_t i = getIndex(arr, rule.first), j = getIndex(arr, rule.second);
        if(i != -1 && j != -1 && i > j) {
            return false;
        }
    }

    return true;
}

void dfs(int node, unordered_set<int>& visited, stack<int>& s, unordered_map<int, vector<int>>& adjList) {
    if (visited.count(node)) {
        return;
    }

    visited.insert(node);
    for (int i : adjList[node]) {
        if (!visited.count(i)) {
            dfs(i, visited, s, adjList);
        }
    }

    s.push(node);
}

int getCorrectedValue(vector<int>& arr) {
    unordered_map<int, vector<int>> adjList;
    for (const auto& rule : rules) {
        int u = rule.first;
        int v = rule.second;
        if (getIndex(arr, u) != -1 && getIndex(arr, v) != -1) {
            adjList[u].push_back(v);
        }
    }

    unordered_set<int> visited;
    stack<int> s;
    for(int i = 0; i < arr.size(); i++) {
        if(!visited.count(arr[i])) {
            dfs(arr[i], visited, s, adjList);
        }
    }

    vector<int> sorted;
    while (!s.empty()) {
        sorted.push_back(s.top());
        s.pop();
    }

    return sorted[sorted.size() / 2];
}

int main() {

    loadData();

    int correctSum = 0, incorrectSum = 0;
    for(int i = 0; i < updates.size(); i++) {
        if(updates[i].size() > 0) {
            if(isRightUpdate(updates[i])) {
                correctSum += updates[i][(updates[i].size() + 1) / 2 - 1];
            } else {
                incorrectSum += makeUpdateRight(updates[i]);
            }
        }
    }

    cout << "total correctSum: " << correctSum << endl;
    cout << "total incorrectSum: " << incorrectSum << endl;

    return 0;
}
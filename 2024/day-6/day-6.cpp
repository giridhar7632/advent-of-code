#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <tuple>

using namespace std;

vector<vector<char>> labMap;
pair<int, int> guard(-1, -1);

void loadData() {
    string line = "";
    ifstream ip("ip.txt");
    int i = 0;

    if (ip.is_open()) {
        while (getline(ip, line)) {
            vector<char> row;
            int j = 0;
            for (char c : line) {
                row.push_back(c);
                if (c == '^') {
                    guard = make_pair(i, j);
                }
                j++;
            }
            labMap.push_back(row);
            i++;
        }
        ip.close();
    }
}

// part-1
struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};
unordered_set<pair<int, int>, pair_hash> visited;

pair<int, int> directions[4] = {
    make_pair(-1, 0), // up
    make_pair(0, 1), // right
    make_pair(1, 0), // down
    make_pair(0, -1) // left
};

void checkGuardPath(int i, int j) {
    int direction = 0;
    while (true) {
        visited.insert(make_pair(i, j));
        int nextI = i + directions[direction].first;
        int nextJ = j + directions[direction].second;

        if (nextI < 0 || nextI >= labMap.size() || nextJ < 0 || nextJ >= labMap[0].size()) {
            break;
        }

        if (labMap[nextI][nextJ] == '#') {
            direction = (direction + 1) % 4;
        } else {
            i = nextI;
            j = nextJ;
        }
    }
}

// part-2
struct tuple_hash {
    template <class T1, class T2, class T3>
    size_t operator()(const std::tuple<T1, T2, T3>& p) const {
        auto hash1 = std::hash<T1>{}(std::get<0>(p));
        auto hash2 = std::hash<T2>{}(std::get<1>(p));
        auto hash3 = std::hash<T3>{}(std::get<2>(p));
        return hash1 ^ (hash2 << 1) ^ (hash3 << 2);
    }
};

bool checkLoop(int oi, int oj) {
    unordered_set<tuple<int, int, int>, tuple_hash> currVisited;

    if (labMap[oi][oj] == '#') {
        return false;
    }

    labMap[oi][oj] = '#';
    int i = guard.first;
    int j = guard.second;
    int direction = 0;

    while (true) {
        if (currVisited.find(make_tuple(i, j, direction)) != currVisited.end()) {
            labMap[oi][oj] = '.';
            return true;
        }

        currVisited.insert(make_tuple(i, j, direction));

        int nextI = i + directions[direction].first;
        int nextJ = j + directions[direction].second;

        if (nextI < 0 || nextI >= labMap.size() || nextJ < 0 || nextJ >= labMap[0].size()) {
            labMap[oi][oj] = '.';
            return false;
        }

        if (labMap[nextI][nextJ] == '#') {
            direction = (direction + 1) % 4;
        } else {
            i = nextI;
            j = nextJ;
        }
    }
}

int main() {
    loadData();
    checkGuardPath(guard.first, guard.second);

    cout << "total positions visited: " << visited.size() << endl;

    int cnt = 0;
    for (const auto& t : visited) {
        if (t.first == guard.first && t.second == guard.second) {
            continue;
        }

        if (checkLoop(t.first, t.second)) {
            cnt++;
        }
    }

    cout << "total positions for new obstruction: " << cnt << endl;

    return 0;
}
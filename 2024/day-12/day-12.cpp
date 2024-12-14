#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;

vector<string> farm;

void loadData() {
    string line;
    ifstream ip("ip.txt");
    if (ip.is_open()) {
        while (getline(ip, line)) {
            farm.push_back(line);  
        }
        ip.close();
    }
}

bool isInBounds(int x, int y) {
    return x >= 0 && x < farm.size() && y >= 0 && y < farm[0].size();
}

struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};
unordered_set<pair<int, int>, pair_hash> visited;

vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int countCorners(const unordered_set<pair<int, int>, pair_hash>& region) {
    unordered_set<pair<float, float>, pair_hash> vertices;
    for(const pair<int, int>& point : region) {
        vertices.insert(make_pair(point.first - 0.5, point.second - 0.5));
        vertices.insert(make_pair(point.first + 0.5, point.second - 0.5));
        vertices.insert(make_pair(point.first + 0.5, point.second + 0.5));
        vertices.insert(make_pair(point.first - 0.5, point.second + 0.5));
    }

    int corners = 0;
    for(const pair<float, float>& vertex : vertices) {
        vector<bool> config;
        vector<pair<float, float>> checkPoints = {
            {vertex.first - 0.5, vertex.second - 0.5},
            {vertex.first + 0.5, vertex.second - 0.5},
            {vertex.first + 0.5, vertex.second + 0.5},
            {vertex.first - 0.5, vertex.second + 0.5}
        };

        for (const auto& cp : checkPoints) {
            config.push_back(!region.count(make_pair(static_cast<int>(cp.first), static_cast<int>(cp.second))));
        }

        int number = 0;
        for(bool b : config) {
            if(b) {
                number++;
            }
        }

        if (number == 1) {
            corners += 1;
        } else if (number == 2) {
            if ((config[0] && config[2] && !config[1] && !config[3]) || (config[1] && config[3] && !config[0] && !config[2])) {
                corners += 2;
            }
        } else if (number == 3) {
            corners += 1;
        }

    }

    return corners;
}

int findRegionCost(int startX, int startY) {
    int area = 0;
    int perimeter = 0;
    unordered_set<pair<int, int>, pair_hash> region;

    queue<pair<int, int>> q;
    q.push(make_pair(startX, startY));
    visited.insert(make_pair(startX, startY));

    region.insert(make_pair(startX, startY));

    while(!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;

        q.pop();

        for(pair<int, int>& dir : directions) {
            int nx = x + dir.first;
            int ny = y + dir.second;

            if(isInBounds(nx, ny) && farm[nx][ny] == farm[x][y]) {
                if(!visited.count(make_pair(nx, ny))) {
                    visited.insert(make_pair(nx, ny));
                    region.insert(make_pair(nx, ny));
                    q.push(make_pair(nx, ny));
                }
            } else {
                perimeter++;
            }
        }
    }

    return region.size() * countCorners(region);
}


int main() {
    loadData();
    long int totalPrice = 0;

    for(int i = 0; i < farm.size(); i++) {
        for(int j = 0; j < farm[i].size(); j++) {
            if(!visited.count(make_pair(i, j))) {
                totalPrice += findRegionCost(i, j);
            }
        }
    }

    cout << "total price: " << totalPrice << endl;
    return 0;
}
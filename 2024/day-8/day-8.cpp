#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;
vector<vector<char>> cityMap;
unordered_map<int, vector<pair<int, int>>> antennas;

void loadData() {
    string line = "";
    ifstream ip("tmp.txt");
    int i = 0;

    if (ip.is_open()) {
        while (getline(ip, line)) {
            vector<char> row;
            int j = 0;
            for (char c : line) {
                row.push_back(c);
                if (c != '.') {
                    antennas[c].push_back(make_pair(i, j));
                }
                j++;
            }
            cityMap.push_back(row);
            i++;
        }
        ip.close();
    }
}

struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

unordered_set<pair<int, int>, pair_hash> antinodes;

bool isInBounds(int x, int y) {
    return x >= 0 && x < cityMap.size() && y >= 0 && y < cityMap[0].size();
}

void getAntinodes() {
    for(auto& [key, points] : antennas) {
        for(int i = 0; i < points.size(); i++) {
            for(int j = i + 1; j < points.size(); j++) {
                int dx = points[j].first - points[i].first;
                int dy = points[j].second - points[i].second;

                pair<int, int> current = points[i];
                do {
                    antinodes.insert(current);
                    current.first -= dx;
                    current.second -= dy;
                } while(isInBounds(current.first, current.second)); //  && cityMap[current.first][current.second] == '.'
                
                // if(isInBounds(points[i].first - dx, points[i].second - dy)) {
                    // antinodes.insert(make_pair(points[i].first - dx, points[i].second - dy));
                // }

                current = points[j];
                do {
                    antinodes.insert(current);
                    current.first += dx;
                    current.second += dy;
                } while(isInBounds(current.first, current.second)); //  && cityMap[current.first][current.second] == '.'

                // if(!(points[j].first + dx < 0 || points[j].first + dx >= cityMap.size() || points[j].second + dy < 0 || points[j].second + dy >= cityMap[0].size())) {
                //     antinodes.insert(make_pair(points[j].first + dx, points[j].second + dy));
                // }
                
            }
        }
    }
}

int main() {
    
    loadData();
    getAntinodes();
    cout << "total antinodes: " << antinodes.size() << endl;
    return 0;
}
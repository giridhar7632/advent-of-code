#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <set>

using namespace std;

vector<string> topographicMap;
vector<pair<int, int>> trailHeads;

void loadData() {
  string line = "";
  ifstream ip("ip.txt");
  if (ip.is_open()) {
    int i = 0;
    while (getline(ip, line)) {
      topographicMap.push_back(line);
      for(int j = 0; j < line.size(); j++) {
        if(topographicMap[i][j] == '0') {
            trailHeads.push_back({i, j});
        }
      }
      i++;
    }

    ip.close();
  }
}

bool isInBounds(int x, int y) {
    return x >= 0 && x < topographicMap.size() && y >= 0 && y < topographicMap[0].size();
}

vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int findTrailheadScore(int startX, int startY) {
    int score = 0;
    vector<vector<bool>> visited(topographicMap.size(), vector<bool>(topographicMap[0].size(), false));
    
    queue<pair<int, int>> q;
    q.push(make_pair(startX, startY));
    visited[startX][startY] = true;

    while(!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if(topographicMap[x][y] == '9') {
            score++;
        }

        for(pair<int, int> dir : directions) {
            int nx = x + dir.first;
            int ny = y + dir.second;

            if(isInBounds(nx, ny) && !visited[nx][ny] && topographicMap[nx][ny] - topographicMap[x][y] == 1) {
                q.push(make_pair(nx, ny));
                visited[nx][ny] = true;
            }
        }
    }

    return score;
}

int findTrailheadRating(int startX, int startY) {
    int rating = 0;
    
    queue<pair<int, int>> q;
    q.push(make_pair(startX, startY));

    while(!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        
        q.pop();

        if(topographicMap[x][y] == '9') {
            rating++;
        }

        for(pair<int, int> dir : directions) {
            int nx = x + dir.first;
            int ny = y + dir.second;

            if(isInBounds(nx, ny) && topographicMap[nx][ny] - topographicMap[x][y] == 1) {
                q.push(make_pair(nx, ny));
            }
        }
    }

    return rating;
}

int main() {
    loadData();

    cout << "no of trailheads: " << trailHeads.size() << endl;

    int totalScore = 0;
    for(int i = 0; i < trailHeads.size(); i++) {
        totalScore += findTrailheadScore(trailHeads[i].first, trailHeads[i].second);
    }
    
    cout << "total trailhead score: " << totalScore << endl;

    int totalRating = 0;
    for(int i = 0; i < trailHeads.size(); i++) {
        totalRating += findTrailheadRating(trailHeads[i].first, trailHeads[i].second);
    }
    
    cout << "total trailhead rating: " << totalRating << endl;

    return 0;
}
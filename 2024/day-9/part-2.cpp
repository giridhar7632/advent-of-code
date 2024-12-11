#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#define ll long long

using namespace std;

vector<string> disk2;
map<int, vector<int>> freeSpaces; // Map of free space size to starting indices
map<int, vector<int>> fileSpaces; // Map of file size to starting indices

void loadData() {
    string line = "";
    ifstream ip("tmp.txt");

    bool isFile = true;
    int index = 0;
    if (ip.is_open()) {
        while (getline(ip, line)) {
            for (ll int i = 0; i < line.size(); i++) {
                ll int num = line[i] - '0';
                if (isFile) {
                    fileSpaces[num].push_back(index);
                    for (ll int j = 0; j < num; j++) {
                        disk2.push_back(to_string(fileSpaces[num].size() - 1));
                        index++;
                    }
                } else {
                    freeSpaces[num].push_back(index);
                    for (ll int j = 0; j < num; j++) {
                        disk2.push_back(".");
                        index++;
                    }
                }
                isFile = !isFile;
            }
        }
        ip.close();
    }
}

int findFreeSpan(int size, int end) {
    for (auto it = freeSpaces.lower_bound(size); it != freeSpaces.end(); ++it) {
        for (int idx : it->second) {
            if (idx < end) {
                return idx;
            }
        }
    }
    return -1;
}

void compactDisk2() {
    for (auto it = fileSpaces.rbegin(); it != fileSpaces.rend(); ++it) {
        int fileSize = it->first;
        for (int fileStart : it->second) {
        int spanStart = findFreeSpan(fileSize, fileStart);
        if (spanStart != -1) {
            for (int j = 0; j < fileSize; j++) {
                disk2[spanStart + j] = disk2[fileStart + j];
                disk2[fileStart + j] = ".";
                }
                freeSpaces[fileSize].push_back(fileStart);
                freeSpaces[fileSize].erase(remove(freeSpaces[fileSize].begin(), freeSpaces[fileSize].end(), spanStart), freeSpaces[fileSize].end());
            }
        }
    }
}

int main() {
    loadData();
    
    compactDisk2();

    ll int checkSum = 0;
    for (ll int i = 0; i < disk2.size(); i++) {
        if (disk2[i] == ".") {
            continue;
        }
        checkSum += i * stoi(disk2[i]);
    }

    cout << "checkSum: " << checkSum << endl;

    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define ll long long

using namespace std;

vector<string> disk1;
vector<string> disk2;

void loadData() {
    string line = "";
    ifstream ip("tmp.txt");

    bool isFile = true;
    if (ip.is_open()) {
        while (getline(ip, line)) {
            for (ll int i = 0; i < line.size(); i++) {
                ll int num = line[i] - '0';
                for (ll int j = 0; j < num; j++) {
                    if(isFile) {
                        disk1.push_back(to_string(i/2));
                        disk2.push_back(to_string(i/2));
                    } else {
                        disk1.push_back(".");
                        disk2.push_back(".");
                    }
                }
                isFile = !isFile;
            }
        }
        ip.close();
    }
}

void compactDisk1() {
    ll int i = 0, j = disk1.size() - 1;
    while(i <= j) {
        if(disk1[i] == "." && disk1[j] != ".") {
            disk1[i] = disk1[j];
            disk1[j] = ".";
            i++;
            j--;
        }

        if(disk1[i] != ".") {
            i++;
        }

        if(disk1[j] == ".") {
            j--;
        }
        
    }
}

int findFreeSpan(int size, int end) {
    int freeCount = 0;
    int start = -1;

    for (int i = 0; i < end; i++) {
        if (disk2[i] == ".") {
            if (start == -1) start = i;
            freeCount++;
            if (freeCount == size) return start;
        } else {
            freeCount = 0;
            start = -1;
        }
    }

    return -1;
}

void compactDisk2() {
    int n = disk2.size();

    for (int i = n - 1; i >= 0; i--) {
        if (disk2[i] != ".") {
            int fileStart = i;
            while (fileStart >= 0 && disk2[fileStart] == disk2[i]) {
                fileStart--;
            }
            fileStart++;
            int fileSize = i - fileStart + 1;

            int spanStart = findFreeSpan(fileSize, fileStart);
            if (spanStart != -1) {
                for (int j = 0; j < fileSize; j++) {
                    disk2[spanStart + j] = disk2[fileStart + j];
                    disk2[fileStart + j] = ".";
                }
            }

            i = fileStart;
        }
    }
}

int main() {
    loadData();
    
    compactDisk2();

    ll int checkSum = 0;
    for(ll int i = 0; i < disk2.size(); i++) {
        if(disk2[i] == ".") {
            continue;
        }
        checkSum += i * stoi(disk2[i]);
    }

    cout << "checkSum: " << checkSum;

    return 0;
}
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

// vector<int> times;
// vector<int> distances;
string times = "";
string distances = "";

void loadData() {
    string line;
    ifstream file("ip.txt");
    if(file.is_open()) {
        while (getline(file, line)) {
            if (line.empty()) continue;

            if (line.find("Time:") != string::npos) {
                istringstream ss(line.substr(6));
                // int time;
                string time;
                while (ss >> time) {
                    // times.push_back(time);
                    times += time;
                }
            } else if (line.find("Distance:") != string::npos) {
                istringstream ss(line.substr(10));
                // int distance;
                string distance;
                while (ss >> distance) {
                    // distances.push_back(distance);
                    distances += distance;
                }
            }
        }
    } else {
        cout << "Unable to open file";
        exit(1);
    }

    file.close();
}

// int waysToBeatRecord(int time, int dist) {
//     int ways = 0;
//     for(int i = 0; i < time; i++) {
//         if(i * (time - i) > dist) {
//             ways++;
//         }
//     }
//     return ways;
// }

// start : part-2
double waysToBeatRecord(double time, double dist) {
    int ways = 0;
    for(int i = 0; i < time; i++) {
        if(i * (time - i) > dist) {
            ways++;
        }
    }
    return ways;
}
// end

int main() {
    loadData();
    double totalWays = 1;

    // for (int i = 0; i < times.size(); i++) {
    //     int ways = waysToBeatRecord(times[i], distances[i]);
    //     totalWays *= ways;
    // }

    // start : part-2
    totalWays = waysToBeatRecord(stod(times), stod(distances));
    cout << "totalWays: " << totalWays << endl;
    // end

    return 0;
}

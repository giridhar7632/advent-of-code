#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

vector<double> seeds;
vector<double> locations;
vector<vector<vector<double>>> data;

double getMappingValue(double seed){
    double temp = seed;

    for (vector<vector<double>> map : data) {
        for(vector<double> pair : map){
            if(pair[1] <= temp && temp < pair[1] + pair[2]){
                temp = pair[0] + (temp - pair[1]);
                break;
            }
        }
    }

    return temp;
}

// void generateSeedPairs(string line){
//     stringstream ss(line);
//     double start, count;
//     while (ss >> start >> count) {
//         seedPairs.push_back(make_pair(start, count));
//     }
// }

vector<double> stringToVector(string line) {
  vector<double> values;
  stringstream ss(line);
  double value;
  while (ss >> value) {
    values.push_back(value);
  }

  return values;
}

// void remap(double low, double high, vector<vector<double>> &map) {
//     vector<vector<double>> newMaps;
//     for(vector<double> entry: map) {
//         double end = entry[1] + entry[2] - 1;
//         double diff = entry[0] - entry[1];

//         if !(end < low || entry[1] > high) [
//             newMaps.push_back({max(entry[1], low), max(end, high), diff});
//         ]
//     }

    
// }

void loadData() {
    string line;
    ifstream file("ip.txt");
    if (!file.is_open()) {
        cout << "Unable to open file";
        exit(1);
    }

    getline(file, line);
    seeds = stringToVector(line.substr(7));

    vector<vector<double>> map_data;
    while (getline(file, line)) {
        if (line.empty()){
           data.push_back(map_data);
           map_data.clear();
        } else {
            if (line.find("map:") != string::npos) continue;
            map_data.push_back(stringToVector(line));
        }
    }

    if (!map_data.empty()) {
        data.push_back(map_data);
    }

    file.close();
}

int main() {
    loadData();

    for (int seed : seeds) {
        locations.push_back(getMappingValue(seed));
    }
    
    cout << "minimum: " << *min_element(locations.begin(), locations.end()) << endl;
    return 0;
}

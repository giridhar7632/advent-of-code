#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector<string> data;

vector<string> loadData() {
    string line;
    ifstream ip("ip.txt");
    if (ip.is_open()) {

        while (getline(ip, line)) {
            string tmp;
            while(getline(line, tmp, ' ')) {

            }
        }

        ip.close();
    }

    return data;
}

bool isSymbol(int i, int j, int num, vector<vector<vector<int>>>& gears) {
    if (i < 0 || i >= data.size() || j < 0 || j >= data[i].length()) {
        return false;
    }

    // start: part 2
    if (data[i][j] == '*') {
        gears[i][j].push_back(num);
        // cout << "inside isSymbol: " << data[i][j] << " " << i << " " << j << " " << num << ' ' << gears[i][j].size() << endl;
    }
    // end

    return data[i][j] != '.' && !isdigit(data[i][j]);
}

int main() {
    loadData();
    int sum = 0;
    int m = data[0].size();

    vector<vector<vector<int>>> gears(data.size(), vector<vector<int>>(m));

    for(int i = 0; i < data.size(); i++) {
        int start = 0;
        string line = data[i];

        // cout << "i: " << i << " ";


        for(int j = 0; j < m;){
            start = j;
            string num = "";
            // cout << "j: " << j << " ";

            while (j < m && isdigit(line[j])) {
                num += line[j];
                j++;
            }

            if(num == "") {
                j++;
                continue;
            }

            int originalNum = stoi(num);

            // if(isSymbol(i, start-1, data) || isSymbol(i, j, data)) {
                // cout << "candidate: " << originalNum << endl;
                // sum += originalNum;
                // continue;
            // }

            // for(int k = start - 1; k < j+1; k++) {
                // cout << "k: " << k << " ";
                // if(isSymbol(i-1, k, data) || isSymbol(i+1, k, data)){
                    // cout << "candidate: " << originalNum << endl;
                    // sum += originalNum;
                    // break;
                // }
            // }

            // start: part 2
            isSymbol(i, start-1, originalNum, gears) || isSymbol(i, j, originalNum, gears);
            for(int k = start - 1; k < j+1; k++) {
                isSymbol(i-1, k, originalNum, gears) || isSymbol(i+1, k, originalNum, gears);
            }
            // end
            
        }
    }

    vector<int> nums;

    for(int i = 0; i < gears.size(); i++) {
        for(int j = 0; j < gears[i].size(); j++) {
            nums = gears[i][j];
            if(data[i][j] == '*' && nums.size() == 2) {
                sum += nums[0] * nums[1];
            }
        }
    }


    cout << "grand total: " << sum;
    return 0;
}

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

vector<string> loadData() {
    vector<string> data;
    string line;
    ifstream ip("ip.txt");
    if (ip.is_open()) {

        while (getline(ip, line)) {
            data.push_back(line);
        }

        ip.close();
    }

    return data;
}

bool isSymbol(int i, int j, vector<string> data) {
    if (i < 0 || i >= data.size() || j < 0 || j >= data[i].length()) {
        return false;
    }

    return data[i][j] != '.' && !isdigit(data[i][j]);
}

bool isGear(int i, int j, vector<string> data) {
    if (i < 0 || i >= data.size() || j < 0 || j >= data[i].length()) {
        return false;
    }

    return data[i][j] == '*';
}

int main() {
    vector<string> data = loadData();
    int sum = 0;
    int m = data[0].size();

    for(int i = 0; i < data.size(); i++) {
        int start = 0;
        string line = data[i];

        // cout << "i: " << i << " ";


        for(int j = 0; j < m;){
            start = j;
            string num1 = "", num2 = "";
            // cout << "j: " << j << " ";

            if(isGear(i, j, data)) {
                if(isdigit(line[j+1])) {
                    while(j < m && isdigit(line[j])) {
                        if(num1 == "") {
                            num1 += line[j];
                        } else {
                            num2 += line[j];
                        }
                        j++;
                    }
                } else if(isdigit(line[j-1])) {
                    while(j >= 0 && isdigit(line[j])) {
                        if(num1 == "") {
                            num1 += line[j];
                        } else {
                            num2 += line[j];
                        }
                        j--;
                    }
                }
                
                j = start;

                for(int k = start - 1; k < j+1; k++) {
                    if(isSymbol(i-1, k, data) || isSymbol(i+1, k, data)){
                        // cout << "candidate: " << originalNum << endl;
                        sum += stoi(num1) * stoi(num2);
                        break;
                    }
                }
                
            } else {
                continue;
            }

            while (j < m && isdigit(line[j])) {
                num += line[j];
                j++;
            }

            if(num == "") {
                j++;
                continue;
            }

            int originalNum = stoi(num);

            if(isSymbol(i, start-1, data) || isSymbol(i, j, data)) {
                // cout << "candidate: " << originalNum << endl;
                sum += originalNum;
                continue;
            }

            for(int k = start - 1; k < j+1; k++) {
                cout << "k: " << k << " ";
                if(isSymbol(i-1, k, data) || isSymbol(i+1, k, data)){
                    // cout << "candidate: " << originalNum << endl;
                    sum += originalNum;
                    break;
                }
            }
            cout << endl;
            
        }
    }


    cout << "grand total: " << sum;
    return 0;
}

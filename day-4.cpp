#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

vector<vector<vector<int>>> data;
map<int, int> cards;

int powerOfTwo(int n) {
    return 1 << n;
}

bool isElementInVector(vector<int>& vec, int element) {
    return find(vec.begin(), vec.end(), element) - vec.end();
}

vector<int> generateIntVector(const string& input) {
    vector<int> result;
    regex reg("\\d+");
    sregex_iterator it(input.begin(), input.end(), reg);
    sregex_iterator end;
    for (; it != end; ++it) {
        result.push_back(stoi(it->str()));
    }

    return result;
}

vector<vector<int>> generateIntVectors(const string& input) {
    vector<vector<int>> result;
    regex divide_sets(R"(\|)");
    sregex_token_iterator it(input.begin(), input.end(), divide_sets, -1);
    sregex_token_iterator end;
    for (; it != end; ++it) {
        result.push_back(generateIntVector(*it));
    }

    return result;
}

vector<vector<vector<int>>> loadData() {
    string line;
    ifstream ip("ip.txt");
    if (ip.is_open()) {

        while (getline(ip, line)) {
            regex card_regex(R"(Card\s+(\d+):)");
            smatch match;

            if (regex_search(line, match, card_regex)) {
                // start part 2
                int card = stoi(match[1]);
                // end

                cards[card] = 1;
                string str = line.substr(match.position() + match.length() + 1); // Get the data after "Card 1: "
                        data.push_back(generateIntVectors(str));
            }
        }

        ip.close();
    }

    return data;
}

int main() {
    loadData();
    int sum = 0;
    int index = 1;
    for (vector<vector<int>> ip : data) {
        vector<int> winning = ip[0];
        vector<int> having = ip[1];
        int matches = 0;

        for(int x : having){
            if(isElementInVector(winning, x)){
                matches++;
            }
        }

        // cout << "points: " << matches << endl;

        if(matches > 0){

            // sum += powerOfTwo(matches-1);

            // start part 2
            for(int k = 1; k <= matches; k++){
                // cout << "k: " << k << endl;
                cards[index + k] += cards[index];
            }
            // end
        }
        index++;
    }

    for (auto& entry : cards) {
        sum += entry.second;
    }
    

    cout << "grand total: " << sum;
    return 0;
}

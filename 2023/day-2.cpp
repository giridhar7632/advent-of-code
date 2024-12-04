#include <fstream>
#include <iostream>
#include <string>
#include <regex>

using namespace std;

int getPossibleGame(string data) {
    int gameId;
    int blueBalls = 14, redBalls = 12, greenBalls = 13;

    regex game_number_regex(R"(Game (\d+))");
    smatch game_number_match;
    if (regex_search(data, game_number_match, game_number_regex)) {
        gameId = stoi(game_number_match[1]);
        // cout << "gameId: " << gameId << endl;
    } else {
        cout << "Invalid game format" << endl;
        return 1;
    }

    regex round_regex(R"((\d+) ([^;]+);?)");
    smatch round_match;
    while (regex_search(data, round_match, round_regex)) {
    string ball_counts = round_match[0];
    // cout << "ball counts: " << ball_counts << endl;

    regex ball_count_regex(R"((\d+) (\w+))");
    smatch ball_count_match;
    while (regex_search(ball_counts, ball_count_match, ball_count_regex)) {
      int count = stoi(ball_count_match[1]);
      string color = ball_count_match[2];
    //   cout << "color: " << color << " : " << "count: " << count << endl;
      if(color == "blue" && count > blueBalls) {
                return 0;
            } else if (color == "red" && count > redBalls) {
                return 0;
            } else if (color == "green" && count > greenBalls) {
                return 0;
            }

      ball_counts = ball_count_match.suffix();
    }

    data = round_match.suffix();
  }

    return gameId;
}


int getGamePower(string data) {
    int blueBalls = 0, redBalls = 0, greenBalls = 0;

    regex round_regex(R"((\d+) ([^;]+);?)");
    smatch round_match;
    while (regex_search(data, round_match, round_regex)) {
    string ball_counts = round_match[0];

    regex ball_count_regex(R"((\d+) (\w+))");
    smatch ball_count_match;
    while (regex_search(ball_counts, ball_count_match, ball_count_regex)) {
      int count = stoi(ball_count_match[1]);
      string color = ball_count_match[2];

    if(color == "blue") {
                blueBalls = max(count, blueBalls);
            } else if (color == "red") {
                redBalls = max(count, redBalls);
            } else if (color == "green") {
                greenBalls = max(count, greenBalls);
            }

      ball_counts = ball_count_match.suffix();
    }

    data = round_match.suffix();
  }

    return blueBalls * redBalls * greenBalls;
}


int main() {

    string line;
    int sum = 0;
    ifstream ip("ip.txt");
    if (ip.is_open()) {

    while (getline(ip, line)) {
        sum += getGamePower(line);
    }

    cout << "grand total: " << sum << endl;

    } else {
        cout << "Error opening the file" << endl;
    }
    return 0;
}

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;

vector<int> left;
vector<int> right;

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void loadData() {
    string line;
    vector<int> left, right;
    ifstream ip("input.txt");

    if (ip.is_open()) {
        while (getline(ip, line)) {
            stringstream ss(line);
            string leftStr, rightStr;

            ss >> leftStr >> rightStr;

            left.push_back(stoi(leftStr));
            right.push_back(stoi(rightStr));
        }

        ip.close();
    }
}

int main() {
    loadData();

    mergeSort(left, 0, left.size() - 1);
    mergeSort(right, 0, right.size() - 1);

    int sum = 0;
    for(int i = 0; i < left.size(); i++) {
        sum += abs(left[i] - right[i]);
    }

    cout << "sum: " << sum << endl;

    // part 2
    unordered_map<int, int> countMap;
    for (int num : right) {
        countMap[num]++;
    }

    long int similarityScore = 0;
    for(int num : left) {
        if (countMap.find(num) != countMap.end()) {
            similarityScore += num * countMap[num];
        }
    }

    cout << "similarityScore: " << similarityScore << endl;

    return 0;
}

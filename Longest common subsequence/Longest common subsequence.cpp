#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

vector<string> lineFromFile(const string& nameFile) {
    vector<string> lines;
    ifstream file(nameFile);
    if (!file.is_open()) {
        cout << "Nie można otworzyć pliku" << endl;
    }
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return lines;
}

void printDiff(const vector<vector<int>>& C, const vector<string>& X, const vector<string>& Y, int i, int j , ofstream& outputFile) {
    if (i >= 0 && j >= 0 && X[i] == Y[j]) {
        printDiff(C, X, Y, i - 1, j - 1, outputFile);
        outputFile << "= " << X[i] << endl;
    }
    else if (j > 0 && (i == 0 || C[i][j - 1] >= C[i - 1][j])) {
        printDiff(C, X, Y, i, j - 1, outputFile);
        outputFile << "> " << Y[j] << endl;
    }
    else if (i > 0 && (j == 0 || C[i][j - 1] < C[i - 1][j])) {
        printDiff(C, X, Y, i - 1, j, outputFile);
        outputFile << "< " << X[i] << endl;
    }
    else {
        outputFile << "" << endl;
    }
}

void LCS(const vector<string>& X, const vector<string>& Y, const string& file) {
    int m = X.size();
    int n = Y.size();
    vector<vector<int>> C(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                C[i][j] = C[i - 1][j - 1] + 1;
            }
            else {
                C[i][j] = max(C[i - 1][j], C[i][j - 1]);
            }
        }
    }
    ofstream outputFile(file);
    printDiff(C, X, Y, m - 1, n - 1, outputFile);
    outputFile.close();
}





int main() {
    string file1 = "file1.txt", file2 = "file2.txt", file3="file3.txt";
    vector<string> line1 = lineFromFile(file1);
    vector<string> line2 = lineFromFile(file2);
    cout << 2 % 4;
    LCS(line1, line2, file3);

    return 0;
}

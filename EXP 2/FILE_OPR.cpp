#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream inputFile("TEST.txt");
    ofstream outputFile("output.txt");

    if (inputFile.is_open() && outputFile.is_open()) {
        char ch;
        while (inputFile.get(ch)) {
            outputFile << ch;
        }
        inputFile.close();
        outputFile.close();
        cout << "File copied successfully." << endl;
    } else {
        cout << "Failed to open the files." << endl;
    }

    return 0;
}
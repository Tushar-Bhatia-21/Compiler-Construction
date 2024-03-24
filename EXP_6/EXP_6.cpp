#include <iostream>
#include <cstring>
#include <cctype>
#include <vector>
#include <algorithm> // Include algorithm header for std::find
using namespace std;

vector<string> productions;
vector<char> firstSet[26];
vector<char> followSet[26];

bool isNonTerminal(char c) {
    return isupper(c);
}

bool isTerminal(char c) {
    return islower(c) || c == '$';
}

// Forward declaration
bool containsEpsilon(const vector<char>& set);

void computeFirst(char c) {
    if (isTerminal(c)) {
        if (find(firstSet[c - 'A'].begin(), firstSet[c - 'A'].end(), c) == firstSet[c - 'A'].end()) {
            firstSet[c - 'A'].push_back(c);
        }
        return;
    }

    for (const string& production : productions) {
        if (production[0] == c) {
            size_t i = 3;
            while (i < production.size() && production[i] != '|') {
                char nextSymbol = production[i];
                computeFirst(nextSymbol);
                for (char symbol : firstSet[nextSymbol - 'A']) {
                    if (symbol != '$' && find(firstSet[c - 'A'].begin(), firstSet[c - 'A'].end(), symbol) == firstSet[c - 'A'].end()) {
                        firstSet[c - 'A'].push_back(symbol);
                    }
                }
                if (!containsEpsilon(firstSet[nextSymbol - 'A'])) {
                    break;
                }
                i++;
            }
        }
    }
}

void computeFollow(char c) {
    if (c == productions[0][0]) {
        if (find(followSet[c - 'A'].begin(), followSet[c - 'A'].end(), '$') == followSet[c - 'A'].end()) {
            followSet[c - 'A'].push_back('$');
        }
    }

    for (const string& production : productions) {
        size_t pos = production.find(c);
        if (pos != string::npos) {
            if (pos + 1 < production.size()) {
                char nextSymbol = production[pos + 1];
                if (isTerminal(nextSymbol)) {
                    if (find(followSet[c - 'A'].begin(), followSet[c - 'A'].end(), nextSymbol) == followSet[c - 'A'].end()) {
                        followSet[c - 'A'].push_back(nextSymbol);
                    }
                } else {
                    for (char symbol : firstSet[nextSymbol - 'A']) {
                        if (symbol != '$' && find(followSet[c - 'A'].begin(), followSet[c - 'A'].end(), symbol) == followSet[c - 'A'].end()) {
                            followSet[c - 'A'].push_back(symbol);
                        }
                    }
                    if (containsEpsilon(firstSet[nextSymbol - 'A'])) {
                        computeFollow(nextSymbol);
                        for (char symbol : followSet[nextSymbol - 'A']) {
                            if (find(followSet[c - 'A'].begin(), followSet[c - 'A'].end(), symbol) == followSet[c - 'A'].end()) {
                                followSet[c - 'A'].push_back(symbol);
                            }
                        }
                    }
                }
            } else if (pos + 1 == production.size() && c != production[0]) {
                computeFollow(production[0]);
                for (char symbol : followSet[production[0] - 'A']) {
                    if (find(followSet[c - 'A'].begin(), followSet[c - 'A'].end(), symbol) == followSet[c - 'A'].end()) {
                        followSet[c - 'A'].push_back(symbol);
                    }
                }
            }
        }
    }
}

bool containsEpsilon(const vector<char>& set) {
    return find(set.begin(), set.end(), '$') != set.end();
}

int main() {
    int z;
    char c;
    
    cout << "Enter the no of productions:" << endl;
    int n;
    cin >> n;
    cout << "Enter the productions:" << endl;
    for (int i = 0; i < n; i++) {
        string production;
        cin >> production;
        productions.push_back(production);
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        computeFirst(c);
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        computeFollow(c);
    }

    for(int i=0;i<n;i++){
        cout << "Enter the element whose first & follow is to be found:";
        cin >> c;
        cout << "First(" << c << ")={";
        for (char symbol : firstSet[c - 'A']) {
            cout << symbol;
        }
        cout << "}" << endl;

        cout << "Follow(" << c << ")={";
        for (char symbol : followSet[c - 'A']) {
            cout << symbol;
        }
        cout << "}" << endl;
    }
    return 0;
}

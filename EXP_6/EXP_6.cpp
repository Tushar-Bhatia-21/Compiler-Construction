#include<iostream>
#include<string>
#include<vector>
using namespace std;


void first(string production) {
    char nonTerminal = production[0];
    int pipeLoc = production.find('|');
    string firstHalf = production.substr(3, pipeLoc - 3);
    string secondHalf = production.substr(pipeLoc + 1);
    string alpha = "";
    int x = 0;
    while (firstHalf[x] == secondHalf[x]) {
        alpha += firstHalf[x];
        x++;
    }
    cout << "First of " << nonTerminal << " is " << alpha << endl;
}

void removeLeftFactoring(string production) {
    char nonTerminal = production[0];
    int pipeLoc = production.find('|');

    string firstHalf = production.substr(3, pipeLoc - 3);
    string secondHalf = production.substr(pipeLoc + 1);

    string alpha = "";
    int x = 0;
    while (firstHalf[x] == secondHalf[x]) {
        alpha += firstHalf[x];
        x++;
    }

    if (alpha.empty()) {
        cout << "Left Factoring not present." << endl;
        return;
    }

    string beta = (x < firstHalf.size()) ? firstHalf.substr(x) : "";
    string gamma = (x < secondHalf.size()) ? secondHalf.substr(x) : "";

    cout << "Production after removal of Left Factoring: " << endl;
    cout << nonTerminal << "  -> " << alpha << nonTerminal << "'" << endl;
    cout << nonTerminal << "' -> " << (beta.empty() ? "$" : beta) << "|" << (gamma.empty() ? "$" : gamma) << endl;
} 

int main() {  
    cout << "Tushar Bhatia" << endl;
    cout << "A2305221202" << endl;
    
    string ip, temp;
    int n;
    cout << "Enter the Parent Non-Terminal : ";
    cin >> ip;
    ip += "->";

    cout << "Enter the number of productions : ";
    cin >> n;
    for(int i = 0; i < n; i++) {
        cout << "Enter Production " << i + 1 << " : ";
        cin >> temp;
        ip += temp;
        if (i != n - 1)
            ip += "|";
    }

    cout << "Production Rule : " << ip << endl;
    removeLeftFactoring(ip);
    first(ip);

    return 0;
}

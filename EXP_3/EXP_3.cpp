#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>

using namespace std;

bool isFunction(const string& word) {
    return word.find('(') != string::npos;
}

int main() {
    int func_count = 0;
    int keyword_count = 0;
     unordered_set<string> keywords = {
        "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
        "bool", "break", "case", "catch", "char", "char16_t", "char32_t", "class",
        "compl", "const", "constexpr", "const_cast", "continue", "decltype", "default",
        "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "export",
        "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int",
        "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr",
        "operator", "or", "or_eq", "private", "protected", "public", "register",
        "reinterpret_cast", "return", "short", "signed", "sizeof", "static", "static_assert",
        "static_cast", "struct", "switch", "template", "this", "thread_local", "throw",
        "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
        "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
    };

    ifstream inputFile("TEST.txt");
    ofstream outputFile("output.txt");
    int wordCount = 0;

    if (inputFile.is_open() && outputFile.is_open()) {
        string line;
        while (getline(inputFile, line, ',')) {
            istringstream iss(line);
            string word;
            while (iss >> word) {
                cout << word << " ";
                if (keywords.find(word) != keywords.end()) {
                    keyword_count++;
                    cout << " (C++ keyword)" << endl;
                } else if (isFunction(word)) {
                    func_count++;
                    cout << " (C++ function)" << endl;
                }

                outputFile << word << " ";
                wordCount++;
            }
        }

        inputFile.close();
        outputFile.close();

        cout << "\nFile copied successfully." << endl;
        cout << "Tushar Bhatia" << endl;
        cout << "A2305221202" << endl;
        cout << "Total count: " << wordCount << endl;
        cout<< "Total functions: " << func_count << endl;
        cout << "Total keywords: " << keyword_count << endl;
    } else {
        cout << "Failed to open the files." << endl;
    }

    return 0;
}

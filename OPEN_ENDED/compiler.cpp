#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>

using namespace std;

class Compiler {
private:
    vector<string> three_address_code;
    int temp_count;

public:
    Compiler() : temp_count(0) {}

    string generate_temp() {
        string temp_var = "t" + to_string(temp_count);
        temp_count++;
        return temp_var;
    }

    void compile(const string& cpp_code) {
        stringstream ss(cpp_code);
        string line;
        while (getline(ss, line)) {
            line = trim(line);
            if (!line.empty()) {
                parse(line);
            }
        }
    }

    void parse(const string& line) {
        regex int_declaration("^int (.+);$");
        regex assignment("^([^=]+)\\s*=\\s*([^=]+);$");
        regex arithmetic("^(.+)$");

        smatch match;
        if (regex_match(line, match, int_declaration)) {
            stringstream ss(match[1]);
            string var;
            while (getline(ss, var, ',')) {
                three_address_code.push_back("int " + trim(var) + ";");
            }
        } else if (regex_match(line, match, assignment)) {
            string lhs = trim(match[1]);
            string rhs = trim(match[2]);
            string temp_var = generate_temp();
            three_address_code.push_back(temp_var + " = " + rhs + ";");
            three_address_code.push_back(lhs + " = " + temp_var + ";");
        } else if (regex_match(line, match, arithmetic)) {
            string temp_var = generate_temp();
            three_address_code.push_back(temp_var + " = " + line + ";");
        } else {
            three_address_code.push_back(line);
        }
    }

    string get_three_address_code() {
        stringstream ss;
        for (const string& code : three_address_code) {
            ss << code << endl;
        }
        return ss.str();
    }

  string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n");
    size_t last = str.find_last_not_of(" \t\n");
    if (first == string::npos || last == string::npos) {
        return "";
    }
    return str.substr(first, (last - first + 1));


    }
};

int main() {
    string cpp_code = R"(
        int a, b, c;
        a = 5;
        b = 10;
        c = a + b;
    )";

    Compiler compiler;
    compiler.compile(cpp_code);
    cout << "Three-address code:" << endl;
    cout << compiler.get_three_address_code();

    return 0;
}

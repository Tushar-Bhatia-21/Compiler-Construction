#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <unordered_set>
#include <stdexcept>

using namespace std;

unordered_set<string> keywords = {"asm", "FPOS", "FNEN", "exit", "mem_addr"};

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
        if (line.find("asm") != string::npos) {
            // Handle assembly code directly
            size_t start_pos = line.find('"');
            size_t end_pos = line.rfind('"');
            if (start_pos != string::npos && end_pos != string::npos && start_pos < end_pos) {
                string asm_content = line.substr(start_pos + 1, end_pos - start_pos - 1);
                three_address_code.push_back(asm_content);
            }
        } else if (line.find("FPOS") != string::npos) {
            // Handle Flip Positive
            size_t pos = line.find("FPOS");
            string var = line.substr(pos + 5);
            string temp_var = generate_temp();
            three_address_code.push_back(temp_var + " = -" + var);
        } else if (line.find("FNEN") != string::npos) {
            // Handle Flip Negative
            size_t pos = line.find("FNEN");
            string var = line.substr(pos + 5);
            string temp_var = generate_temp();
            three_address_code.push_back(temp_var + " = " + var);
        } else if (line.find("exit") != string::npos) {
            // Handle exit
            three_address_code.push_back("goto EXIT");
        } else if (line.find("mem_addr") != string::npos) {
            // Handle memory address
            size_t pos = line.find("mem_addr");
            string temp_var = generate_temp();
            string var = line.substr(pos + 5);
            // Convert address to string
            stringstream ss;
            ss << &var;
            string temp = ss.str();
            three_address_code.push_back(temp_var + " = " + temp);
        } else {
            // Handle other statements
            // Regular expression patterns for matching different statements
            regex int_declaration("^int (.+);$");
            regex assignment("^([^=]+)\\s*=\\s*([^=]+);$");
            regex arithmetic("^(.+)$");

            smatch match;
            if (regex_match(line, match, int_declaration)) {
                // Handle integer declaration
                stringstream ss(match[1]);
                string var;
                while (getline(ss, var, ',')) {
                    three_address_code.push_back("int " + trim(var) + ";");
                }
            } else if (regex_match(line, match, assignment)) {
                // Handle assignment
                string lhs = trim(match[1]);
                string rhs = trim(match[2]);
                string temp_var = generate_temp();
                three_address_code.push_back(temp_var + " = " + rhs);
                three_address_code.push_back(lhs + " = " + temp_var);
            } else if (regex_match(line, match, arithmetic)) {
                // Handle arithmetic operation
                string temp_var = generate_temp();
                three_address_code.push_back(temp_var + " = " + line);
            } else {
                // Push other lines as they are
                three_address_code.push_back(line);
            }
        }
    }

    string get_three_address_code() {
        // Output the three-address code
        stringstream ss;
        for (const string& code : three_address_code) {
            ss << code << endl;
        }
        // Add EXIT label
        ss << "EXIT: " << endl;
        return ss.str();
    }

    string trim(const string& str) {
        // Trim whitespace from both ends of the string
        size_t first = str.find_first_not_of(" \t\n");
        size_t last = str.find_last_not_of(" \t\n");
        if (first == string::npos || last == string::npos) {
            return "";
        }
        return str.substr(first, (last - first + 1));
    }
};

int main() {
    // Input C++ code
    string cpp_code = R"(
        int a, b, c;
        c = a + b;
        FPOS a;
        exit;
        FNEN -b;
        asm("mov $0x1, %eax");
        mem_addr a;
    )";

    // Compile and print the three-address code
    Compiler compiler;
    compiler.compile(cpp_code);
    cout << "Three-address code:" << endl;
    cout << compiler.get_three_address_code();

    return 0;
}

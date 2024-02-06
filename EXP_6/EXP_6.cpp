#include <iostream>
#include <string>
using namespace std;

#define MAX 100

int main()
{
    int n;
    string input, op1, op2, temp;
    int size[MAX] = {};

    char c;
    cout << "Enter the Parent Non-Terminal: " << endl;
    cin >> c;
    input.push_back(c);
    op1 += input + "\'->";
    input += "->";
    op2 += input;
    cout << "Enter the number of productions: " << endl;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the production " << i + 1 << ":" << endl;
        cin >> temp;
        size[i] = temp.size();
        input += temp;
        if (i != n - 1)
        {
            input += "|";
        }
    }
    cout << "Production Rule: " << input << endl;

    // Left Recursion Removal
    for (int i = 3; i < input.size(); i++)
    {
        if (input[i] == input[0])
        {
            cout << "Left Recursion Detected" << endl;
            if (input[i] != '#')
            {
                for (int l = i + 1; l < i + size[i] - 1; l++)
                {
                    op2.push_back(input[l]);
                }
                op2.push_back(input[0]);
                op2 += "\'|";
            }
            else
            {
                cout << "Production " << i + 1 << " does not have left recursion" << endl;
                op2.push_back(input[0]);
                op2 += "\'";
            }
        }
    }
  // Left Factoring
    string factoredInput = input;
    for (int i = 3; i < input.size(); i++)
    {
        // Check for common prefixes among alternative productions
        int commonPrefixLength = 0;
        while (i + commonPrefixLength < input.size() && input[i + commonPrefixLength] == input[i - 3 + commonPrefixLength])
        {
            commonPrefixLength++;
        }

        // If there is a common prefix, factor it out
        if (commonPrefixLength > 0)
        {
            string newNonTerminal = input.substr(i, commonPrefixLength);
            factoredInput.replace(i - 3, commonPrefixLength, newNonTerminal);
            op1 += newNonTerminal + "\'";
            i += newNonTerminal.size() - 1;
        }
    }




    // Left Factoring
    cout << "After Left Recursion Removal: " << op2 << endl;
    op1 += "#";
    cout << "After Left Factoring: " << op1 << endl;

    cout << "Tushar Bhatia" << endl;
    cout << "A2305221202" << endl;
    return 0;
}

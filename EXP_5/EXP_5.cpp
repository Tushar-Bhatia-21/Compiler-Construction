#include <iostream>
#include <fstream>
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

    for (int i = 0, k = 3; i < input.size(); i++)
    {
        if (input[i] == input[0])
        {
            cout << "Left Recursion Detected" << endl;
            if (input[i] != '#')
            {
                for (int l = k + 1; l < k + size[i]; l++)
                {
                    op2.push_back(input[l]);
                }
                k += size[i] + 1;
                op2.push_back(input[0]);
                op2 += "\'|";
            }
            else
            {
                int j=0;
                cout << "Production " << i + 1 << " does not have left recursion" << endl;
                if (input[i] != '#')
                {
                    for (j = k; j < k + size[i]; j++)
                    {
                        op2.push_back(input[j]);
                    }
                    k = j + 1;
                    op2.push_back(input[0]);
                    op2 += "\'|";
                }
                else
                {
                    op2.push_back(input[0]);
                    op2 += "\'";
                }
            }
        }
    }
    op1 += "#";
    cout << op2 << endl;
    cout << op1 << endl;
    cout<<"Tushar Bhatia"<<endl;
    return 0;
}

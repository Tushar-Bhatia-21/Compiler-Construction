#include<iostream>
#include<cctype>

using namespace std;

class STACK
{
    private:
    int top=-1;
    int arr[100];
    public:
    STACK()
    {
        top=-1;
    }
    void push(int x)
    {
        if(top==99)
        {
            cout<<"Stack Overflow"<<endl;
            return;
        }
        arr[++top]=x;
    }
    void pop()
    {
        if(top==-1)
        {
            cout<<"STACK UNDERFLOW"<<endl;
            return;
        }
        else
        {
            top--;
        }
    }
    int peek()
    {
        if(top==-1)
        {
            cout<<"Stack is empty"<<endl;
            return 0;
        }
        else
        {
            return arr[top];
        }
    }
    bool isEmpty()
    {
        return top==-1;
    }

};

bool isOperator(char c)
{
    return c=='+'||c=='-'||c=='*'||c=='/'||c=='^';
}

int precedence(char operand)
{
    if(operand=='*'||operand=='/')
    {
        return 2;
    }
    else if(operand=='+'||operand=='-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

string infix_To_Postfix(const string& infixExpression)
{
    STACK charSTACK;
    string postfixExpression;
    for(char c: infixExpression)
    {
        if(isdigit(c) || isalpha(c))
        {
            postfixExpression+=c;
        }
        else if(c=='(')
        {
            charSTACK.push(c);
        }
        else if(c==')')
        {
            while(charSTACK.peek()!='(')
            {
                postfixExpression+=charSTACK.peek();
                charSTACK.pop();
            }
            charSTACK.pop();
        }
        else if(isOperator(c))
        {
            while(!charSTACK.isEmpty()&&precedence(c)<=precedence(charSTACK.peek()))
            {
                postfixExpression+=charSTACK.peek();
                charSTACK.pop();
            }
            charSTACK.push(c);
        }
    }
    while(!charSTACK.isEmpty())
    {
        postfixExpression+=charSTACK.peek();
        charSTACK.pop();
    }
    return postfixExpression;
}

int main()
{
    string infixExpression;
    cout<<"Enter the infix expression"<<endl;
    cin>>infixExpression;
    cout<<"The postfix expression is "<<infix_To_Postfix(infixExpression)<<endl;
    return 0;
}
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;


int priority(char a);
void calculate(stack<double> &va, char op);

int main()
{
    stack<char> operand;
    stack<double> value;

    char letter;
    double number;

    cout << "Enter expression: ";
    while (cin.peek() != '\n')
    {
        if (cin.peek() == ' ')
        {
            cin.get();
        }
        else if (isdigit(cin.peek()))
        {
            cin >> number;
            value.push(number);
        }
        else
        {
            cin >> letter;
            switch (letter)
            {
                case '+': case '-': case '*': case '/': case '^':
                    while (!operand.empty() && priority(letter) <= priority(operand.top()))
                    {
                        calculate(value, operand.top());
                        operand.pop();
                    }
                    operand.push(letter);
                    break;

                case 'l':
                    cin >> letter;
                    if (letter == 'n')
                    {
                        cin >> number;
                        value.push(log(number));
                    }
                    break;

                case '(':
                    operand.push(letter);
                    break;

                case ')':
                    while (operand.top() != '(')
                    {
                        calculate(value, operand.top());
                        operand.pop();
                    }
                    operand.pop();
                    break;
            }
        }
    }
    while (!operand.empty())
    {
        calculate(value, operand.top());
        operand.pop();
    }

    cout << "Solution: " << value.top() << endl;



    return 0;
}

int priority(char a)
{
    switch (a)
    {
        case '+':
        case '-': return 1;

        case '*':
        case '/': return 2;

        case '^': return 3;

        default : return 0;
    }
}

void calculate(stack<double> &va, char op)
{
    double a, b;
    b = va.top();
    va.pop();
    a = va.top();
    va.pop();

    switch (op)
    {
        case '+':
            va.push(a+b);
            break;
        case '-':
            va.push(a-b);
            break;
        case '*':
            va.push(a*b);
            break;
        case '/':
            va.push(a/b);
            break;
        case '^':
            va.push(pow(a, b));
            break;
    }
}

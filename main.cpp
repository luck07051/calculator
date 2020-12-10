#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;

const string file_name {"temp.txt"};

int priority(char a);
void calculate(stack<double> &va, char op);

int main()
{
    stack<char> operand;
    stack<double> value;

    char letter;
    double number;

    // keyborad to txt
    fstream fout {file_name, ios::out | ios::trunc};
    string input;
    cout << "Enter expression: ";
    getline(cin, input);
    fout << input;
    fout.close();


    fstream file {file_name, ios::in};
    unsigned int variable_number = 0;
    do
    {
        while (file.peek() != EOF)
        {
            // delete ' '
            if (file.peek() == ' ')
            {
                file.get();
            }
            //
            else if (isdigit(file.peek()))
            {
                file >> number;
                value.push(number);
            }
            //
            else
            {
                file >> letter;
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
                        file >> letter;
                        if (letter == 'n')
                        {
                            file >> number;
                            value.push(log(number));
                        }
                        break;

                    default:
                        ++variable_number;
                        cout << letter << ": ";
                        cin >> number;
                        while (!cin)
                        {
                            cin.clear();
                            cin.sync();
                            return 0;
                        }
                        value.push(number);
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
        value.pop();

        file.clear();
        file.seekg(0, ios::beg);

    } while (variable_number != 0);

    file.close();
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

#include <iostream>
#include <string>
#include "Stack.h"

using std::cin, std::cout, std::endl;
using std::string, std::stod;

int main() {
    Stack s;
    while (true) {
        // read a word (token) from input
        string token;
        cin >> token;
        if (isdigit(token[0]) || token[0] == '.') {
            // TODO: use std::stod() to convert token to double
            double operand = std::stod(token);
            // TODO: push operand onto stack
            push(s, operand);
        } else {
            char c = token[0];
            if (c == '=') {
                break;
            }
            // Otherwise, it should be one of the operators +, -, * /
            // TODO: Pop the value to be the right-hand side of the operator
            double RHS = pop(s);
            // TODO: Pop the value to be the left-hand side of the operator
            double LHS = pop(s);
            // Do the computation and push the result to the stack
            double result;
            switch (c) {
            case '+':
                // TODO: Do plus, and push the result to the stack
                result = LHS + RHS;
                push(s, result);
                break;
            case '-':
                // TODO: Do minus, and push the result to the stack
                result = LHS - RHS;
                push(s, result);
                break;
            case '*':
                // TODO: Do multiplication, and push the result to the stack
                result = LHS * RHS;
                push(s, result);
                break;
            case '/':
                // TODO: Do division, and push the result to the stack
                result = LHS / RHS;
                push(s, result);
                break;
            default:
                cout << "[ERROR] invalid operator: " << c << endl;
                return 1;
            }
        }
    }
    // pop result from stack, and print it to the terminal
    cout << pop(s) << endl;
    
    // free the stack memory
    delete[] s.A;
    
    return 0;
}

/*
 * Name: Charlie Hartsell
 * Date Submitted: Feb. 5, 2021
 * Lab Section: 004
 * Assignment Name: Lab 2: infix to postfix conversion
 */

#include <string>
#include <stack>
#include <iostream>

using namespace std;

// Function to determine if a character is an operator
// Returns precedence if char is operator, returns 0 if not
int isOperator(string op) {
    if(op=="+" || op=="-") {
        return 1;
    } else if(op=="*" || op=="/" || op=="%") {
        return 2;
    } else if(op=="(" || op==")") {
        return 3;
    } else {
        return 0;
    }
}


int infixToPostfix(string infix[], int length, string postfix[])
{
    stack<string> S;
    string test;
    int bal = 0;
    int postnum = 0;

    // Checking for mismatched parenthesis
    for(int count=0;count<length;count++) {
        test = infix[count];
        if(test=="(") {
            bal++;
        } else if(test==")") {
            bal--;
        } else {
            // Do nothing.
        }
    }

    // Quits the function if there are mismatched parenthesis
    if(bal!=0) {
        return 0;
    }

    // Looping through the infix array
    for(int count=0;count<length;count++) {
        test = infix[count];
        switch(isOperator(test)) {
            case 0: // char is a number
                postfix[postnum] = test;
                postnum++;
                break;
            case 1: // char is + or -
                // Empty stack into postfix until empty, or "(", or precedence lower than its own
                while(!S.empty() && isOperator(S.top())>=1 && S.top()!="(") {
                    postfix[postnum] = S.top();
                    postnum++;
                    S.pop();
                }
                // Place operator onto sack
                S.push(test);
                break;
            case 2: // char is * or / or %
                // Empty stack into postfix until empty, or "(", or precedence lower than its own
                while(!S.empty() && isOperator(S.top())>=2 && S.top()!="(") {
                    postfix[postnum] = S.top();
                    postnum++;
                    S.pop();
                }
                // Place operator onto sack
                S.push(test);
                break;
            case 3: // char is ( or )
                if(test=="(") { // Left paren
                    S.push(test);
                } else if(test==")") {
                    // Empty stack until "(" is hit, remove "(" from stack without adding it or "(" to the stack
                    while(!S.empty() && S.top()!="(") {
                        postfix[postnum] = S.top();
                        postnum++;
                        S.pop();
                    }
                    S.pop();
                } else {
                    // Do nothing.
                }
                break;
        }
    }

    // Loop is done, emptying stack into postfix array
    while(!S.empty()) {
        postfix[postnum] = S.top();
        postnum++;
        S.pop();
    }

    return postnum;
}

//Main function to test infixToPostfix()
//Should convert 2 + 3 * 4 + ( 5 - 6 + 7 ) * 8
//            to 2 3 4 * + 5 6 - 7 + 8 * +
int main()
{
    string infixExp[] = {"2", "+", "3", "*", "4", "+", "(",
                         "5", "-", "6", "+", "7", ")", "*",
                         "8"};
    string postfixExp[15];
    int postfixLength;

    cout << "Infix expression: ";
    for (int i=0; i<15; i++)
    {
        cout << infixExp[i] << " ";
    }
    cout << endl;
    cout << "Length: 15" << endl << endl;

    postfixLength = infixToPostfix(infixExp, 15, postfixExp);

    cout << "Postfix expression: ";
    for (int i=0; i<postfixLength; i++)
    {
        cout << postfixExp[i] << " ";
    }
    cout << endl;
    cout << "Length: " << postfixLength << endl;
    
    return 0;
}
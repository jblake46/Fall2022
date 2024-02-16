#include <string>
#include <stack>

using namespace std;


//Calculates a postfix expression with integer operands using a stack
//The expression is represented using an array of strings
//Each string is either an operand or operator symbol
//Operator symbols:
//"+" addition
//"-" subtraction
//"*" multiplication
//"/" divison
//"%" remainder
//Example expression: "8", "5", "-" evaluates to a result of 3:
//1: push 8, 2: push 5,
//3: "-"-> pop top two values, earlier value is the left-side operand: 8 - 5
//The result of the operation (8-5) is 3, push 3 onto stack
//After evaluation of the expression, the final result should be
//the only value on the stack, return 0 if the stack is
//non-empty after popping the result
//Return 0 if expression is zero-length or if there are insufficient operands
//for an operation
//The STL Stack class can be used
//To easily convert a numeric string to an int you may use the stoi() function
//which takes a string as a parameter and returns a string
int calculatePostfixExpression(string expression[], int length)
{
    int valueOfStatement;
    int holder1, holder2;
    stack<int> postStack;


    for(int i = 0; i < length; i++)
    {
        //transfers any ints from the expression to the postStack
        if(expression[i] >= "0" && expression[i] <= "9")
        {
            postStack.push(stoi(expression[i]));
        }
        //moving integers from postStack to int variables
        //so it can perform operations :)
        else
        {
            holder1 = postStack.top();
            postStack.pop();
            holder2 = postStack.top();
            postStack.pop();
        }
        // bunch of if else statements for the operators
        if(expression[i] == "-")
        {
            valueOfStatement = holder2 - holder1;
            postStack.push(valueOfStatement);
        }
        else if(expression[i] == "+")
        {
            valueOfStatement = holder2 + holder1;
            postStack.push(valueOfStatement);
        }
        else if(expression[i] == "*")
        {
            valueOfStatement = holder2 * holder1;
            postStack.push(valueOfStatement);
        }
        else if(expression[i] == "/")
        {
            valueOfStatement = holder2 / holder1;
            postStack.push(valueOfStatement);
        }
        else if(expression[i] == "%")
        {
            valueOfStatement = holder2 % holder1;
            postStack.push(valueOfStatement);
        }


    }
    return postStack.top();
}
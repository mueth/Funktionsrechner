/*
compile: g++ Funktionsrechner.cpp Stack.cpp -o Funktionsrechner

line: curent line from txt file

evaluation rules:
    1. push on stack if its a number, operator, opening bracket
    2. if curent symbol is a closing bracket
        - pop next 3 symbols from stack
        - check if 4th symbol is a opening bracket
            - if true -> goto rule 3.
            - if false -> stop evaluation, evaluate next line
        - if line size > 0 goto rule 1. or 2.
        - if line size 0 and stack size 3 -> goto rule 3.
    3. evaluate math expression and push result on stack
        - if stack size >= 3 and line size > 0 -> goto rule 1. or 2.
        - if stack size >= 3 and line size 0 -> goto rule 3.
        - if stack size 1 -> goto rule 4.
    4. if stack is size 1 -> print result to console
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Stack.h"

//string of numeric values, push on stack, delete respective values from src
void num2string(std::string& src, Stack& stack)
{
    std::string subStr;
    int pos = 0;
    while (std::isdigit(src[pos]) || src[pos] == '.')
    {
        pos++;
    }
    subStr = src.substr(0, pos);
    stack.pushSymbol(subStr);
    src.erase(0, pos);
}

//validate numerical input
bool checkNum(std::string sym)
{
    for (char& c : sym)
    {
        if (std::isdigit(c) == 0 && c != '.')
            return false;
    }
    return true;
}

//validate mathematical expression
bool checkOp(std::string sym)
{
    if (sym == "+" || sym == "-" || sym == "*" || sym == "/")
        return true;
    return false;
}

//remove symbols from stack, evaluate mathematical expression, push result on stack
bool popSymbol(Stack& stack)
{
    std::string sym1, sym2, sym3, symC;
    float f1, f2;

    if (stack.stackSize() >= 3)
    {
        symC = stack._curSymbol; //get curent symbol before popping, looking for bracket
        sym1 = stack.popSymbol();
        sym2 = stack.popSymbol();
        sym3 = stack.popSymbol();

        if (!(checkNum(sym1) && checkNum(sym3) && checkOp(sym2)))
        {
            std::cout << "unexpected symbol, stop evaluation." << std::endl;
            stack.setPrinting(false);
            return false;
        }

        //if symbols left on stack, next symbol musst be a opening bracket
        if (stack.stackSize() > 0)
        {
            std::string symN = stack.nextSymbol();
            //if curent symbol, before popping math expression, is a closing bracket, next symbol musst be a opening bracket, if not -> stop evaluation
            if (stack.nextSymbol() == "(" && symC == ")")
                //pop opening bracket, no longer needed
                stack.popSymbol();
            //missing bracket
            else if ((stack.nextSymbol() == "(" && symC != ")") || (stack.nextSymbol() != "(" && symC == ")"))
            {
                std::cout << "missing bracket, stop evaluation." << std::endl;
                stack.setPrinting(false);
                return false;
            }
        } //else: last 3 symbols popped, stack contains result -> print result to console

        f2 = std::stof(sym1);
        f1 = std::stof(sym3);

        //evaluate expression, push result on stack
        if (sym2 == "+")
            stack.pushSymbol(std::to_string(f1 + f2));
        else if (sym2 == "-")
            stack.pushSymbol(std::to_string(f1 - f2));
        else if (sym2 == "*")
            stack.pushSymbol(std::to_string(f1 * f2));
        else if (sym2 == "/")
            stack.pushSymbol(std::to_string(f1 / f2));
    }
    else
    {
        //too little symbols on stack
        std::cout << "stack size missmatch, stop evaluation." << std::endl;
        stack.setPrinting(false);
        return false;
    }
    return true;
}

int main(int argc, char** argv)
{
    //TODO: check argument for valid txt file
    if (argc == 2)
    {
        std::cout << "you entered following argument: " << argv[1] << std::endl;
        std::string str;
        char symbol;
        int cnt = 0;

        try
        {
            std::ifstream txtFile(argv[1]);
            //error handling
            if (!txtFile)
                throw "cannot open txt file.";
        
            for (std::string line; getline(txtFile, line); )
            {
                //ignores lines with # at the beginning
                if (line[0] != '#')
                {
                    //allocate new stack
                    Stack stack;
                    //enable printing to console
                    stack.setPrinting(true);
                    cnt++;
                    //make a stream for the line itself
                    std::istringstream in(line);
                    in >> str;

                    while (!str.empty())
                    {
                        //first line symbol
                        symbol = str[0];
                        stack._curSymbol = symbol;
                        //number -> push on stack
                        if (std::isdigit(symbol))
                        {
                            num2string(str, stack);
                        }
                        //operator, opening bracket -> push on stack
                        else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '(')
                        {
                            std::string s(1, symbol);
                            stack.pushSymbol(s);
                            str.erase(0, 1);
                        }
                        //closing bracket ) -> eval expression
                        else if (symbol == ')')
                        {
                            //pop symbols from stack
                            if (popSymbol(stack))
                                str.erase(0, 1);
                            else
                            {
                                stack.setPrinting(false);
                                break;
                            }
                        }
                        else //break on not definded symbol
                        {
                            stack.setPrinting(false);
                            std::cout << "not defined symbol, stop evaluation." << std::endl;
                            break;
                        }
                    }
                    //if str is empty, eval remaining symbols on stack
                    while (stack.stackSize() > 1 && str.empty())
                    {
                        if (!popSymbol(stack))
                        {
                            break;
                        }
                    }
                    //print to console
                    if (stack.getPrinting())
                        std::cout << "Term: " << cnt << ", result: " << stack.popSymbol() << std::endl;
                }
            }
        }
        catch (const char* cstr)
        {
            std::cerr << cstr << std::endl;
        }
    }
    else if (argc > 2)
    {
        std::cout << "only one argument possible" << std::endl;
    }
    else
    {
        std::cout << "no argument was entered" << std::endl;
    }
    return 0;
}

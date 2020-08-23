#pragma once
#include <vector>
#include <sstream>
#include <string>
#include <iostream>

class Stack
{
public:
	Stack() {	}
	~Stack() {	}
	std::vector<std::string> getStack(void);
	std::string popSymbol(void);
	void pushSymbol(std::string str);
	int stackSize(void);
	std::string nextSymbol(void);
	std::string _curSymbol;
	void setPrinting(bool val);
	bool getPrinting(void);

private:
	std::vector<std::string> _stack;
	bool _print = false;
};


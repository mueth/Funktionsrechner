#include "Stack.h"

std::string Stack::nextSymbol(void)
{
	return _stack.back();
}

std::string Stack::popSymbol(void)
{
	_curSymbol = _stack.back();
	_stack.pop_back();
	return _curSymbol;
}

void Stack::pushSymbol(std::string str)
{
	_stack.push_back(str);
}

int Stack::stackSize()
{
		return _stack.size();
}

std::vector<std::string> Stack::getStack(void)
{
	return _stack;
}

void Stack::setPrinting(bool val)
{
	_print = val;
}

bool Stack::getPrinting(void)
{
	return _print;
}
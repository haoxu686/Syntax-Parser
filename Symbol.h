#pragma once

class Symbol
{
public:
	virtual int hashCode() = 0;
	virtual bool isTerminalSymbol() = 0;
	virtual int getIndexOfSymbol() = 0;
	virtual bool equals(Symbol *) = 0;
	Symbol(void);
	~Symbol(void);
};

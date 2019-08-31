#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "Ast.h"
class Variable {
public:
	bool _getBoolVal();
	int _getBinVal();

protected:
	std::string _label;
	int _dataType;
	bool _bool_val = false;
	int _bin_val = 0;
	void _setLabel(std::string label);
};

class Integer: public Variable{
public:
	Integer(int val, std::string label);
protected:
	int _val;
	void _setBoolVal();
	void _setBinVal();
	void _setDataType();

};

class String : public Variable {
public:
	String(std::string val, std::string label);
protected:

	bool _is_char = false;

	std::string _val;
	void _setBoolVal();
	void _setBinVal();
	void _setDataType();
};

class Decimal : public Variable {
public:
	Decimal(double val, std::string label);
protected:
	double _val;
	void _setBoolVal();
	void _setBinVal();
	void _setDataType();
};
#endif // !VARIABLE_H
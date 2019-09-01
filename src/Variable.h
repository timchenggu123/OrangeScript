#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "Ast.h"
class Variable {
public:
	virtual ~Variable();
	bool _getBoolVal();
	int _getBinVal();
	int _getType();
	
protected:
	std::string _label;
	int _dataType = Ast::NULL_TYPE;
	bool _bool_val = false;
	int _bin_val = 0;
	void _setLabel(std::string label);
};

class Integer: public Variable{
public:
	Integer(int val, std::string label);
	int getVal();
	void setVal(int val);
protected:
	int _val;
	void _setBoolVal();
	void _setBinVal();
	void _setDataType();

};

class String : public Variable {
public:
	String(std::string val, std::string label);
	std::string getVal();
	void setVal(std::string val);
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
	double getVal();
	void setVal(double val);
protected:
	double _val;
	void _setBoolVal();
	void _setBinVal();
	void _setDataType();
};
#endif // !VARIABLE_H
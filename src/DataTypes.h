#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "Ast.h"

class AbstractDataType {
public:
	virtual ~AbstractDataType();
	bool _getBoolVal();
	int _getBinVal();
	int _getType();

protected:
	int _dataType = Ast::NULL_TYPE;
	bool _bool_val = false;
	bool _valid = true;
	int _bin_val = 0;
};

class Integer : public AbstractDataType {
public:
	Integer(int val);
	int getVal();
	void setVal(int val);
protected:
	int _val;
	void _setBoolVal();
	void _setBinVal();
	void _setDataType();

};

class String : public AbstractDataType {
public:
	String(std::string val);
	std::string getVal();
	void setVal(std::string val);
protected:

	bool _is_char = false;

	std::string _val;
	void _setBoolVal();
	void _setBinVal();
	void _setDataType();
};

class Decimal : public AbstractDataType {
public:
	Decimal(double val);
	double getVal();
	void setVal(double val);
protected:
	double _val;
	void _setBoolVal();
	void _setBinVal();
	void _setDataType();
};
#endif // !VARIABLE_H
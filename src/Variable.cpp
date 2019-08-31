#include "Variable.h"

void Variable::_setLabel(std::string label)
{
	_label = label;
}

bool Variable::_getBoolVal()
{
	return _bool_val;
}

int Variable::_getBinVal()
{
	return _bin_val;
}

Integer::Integer(int val, std::string label) :
	_val(val)
{
	_setLabel(label);
	_setBoolVal();
	_setBinVal();
	_setDataType();
}


void Integer::_setBoolVal()
{
	_bool_val = _val == 1 ? true : false;
}

void Integer::_setBinVal()
{
	_bin_val = _val;
}

void Integer::_setDataType()
{
	_dataType = Ast::INTEGER;
}

String::String(std::string val, std::string label) :
	_val(val),
	_is_char(val.length() == 1 ? true: false)
{
	_setLabel(label);
	_setBoolVal();
	_setBinVal();
	_setDataType();
}

void String::_setBoolVal()
{
	_bool_val = _val == "" ? false : true;
}

void String::_setBinVal()
{
	if (_is_char) {
		_bin_val = _val[0];
	}
	else {
		0;
	}
}

void String::_setDataType()
{
	_dataType = Ast::STRING;
}


Decimal::Decimal(double val, std::string label) :
	_val(val)
{
	_setLabel(label);
	_setBoolVal();
	_setBinVal();
	_setDataType();
}

void Decimal::_setBoolVal()
{
	_bool_val = _val == 0 ? false : true;
}

void Decimal::_setBinVal()
{
	_bin_val = 0;
}

void Decimal::_setDataType()
{
	_dataType = Ast::DECIMAL;
}

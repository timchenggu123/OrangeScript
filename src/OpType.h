#ifndef OPTYPE_H
#define OPTYPE_H

#include <string>

using std::string;
//This class defines the operator types. 
class OpType
{
public:
private:


public:

	enum Type {
		NULL_TYPE,
		FUN, MEM_ACC,
		INC, DEC, B_NOT, L_NOT, INDIR, ADDRESS,
		MUL, DIV, MOD,
		ADD, SUB,
		B_R_SHIFT, B_L_SHIFT,
		LT, GT, LTE, GTE,
		EQ, NOT_EQ,
		B_AND,
		B_XOR,
		B_OR,
		L_AND,
		L_OR,
		ASSIGN,
		COMMA
	};

	OpType();
	~OpType();
	int getPrecedence(int opType);
	int getOpType(string op);
};

#endif

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
		//not all types defined here are implemented 
		//at the moment
		NULL_TYPE,
		FUN_CALL, MEM_ACC,
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

	enum Associtivity {
		RIGHT_ASSOC,
		LEFT_ASSOC,
		INDETERMINATE
	};

	OpType();
	~OpType();
	static  int getPrecedence(int opType);
	static  int getOpType(string op);
	static  bool isBinaryOp(int opType);
	static  bool isUnaryOp(int opType);
	static  int LeftOrRightAssociate(int OpType);
};

#endif

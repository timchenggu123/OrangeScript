#include "OpType.h"



OpType::OpType()
{
}


OpType::~OpType()
{
}

 int OpType::getPrecedence(int opType)
{
	switch (opType) {
		case FUN_CALL:
		case MEM_ACC:
			return 1;
		case INC:
		case DEC:
		case B_NOT:
		case L_NOT:
		case INDIR:
		case ADDRESS:
			return 2;
		case MUL:
		case DIV:
		case MOD:
			return 3;
		case ADD:
		case SUB:
			return 4;
		case B_R_SHIFT:
		case B_L_SHIFT:
			return 5;
		case LT:
		case GT:
		case LTE:
		case GTE:
			return 6;
		case EQ:
		case NOT_EQ:
			return 7;
		case B_AND:
			return 8;
		case B_XOR:
			return 9;
		case L_AND:
			return 10;
		case L_OR:
			return 11;
		case ASSIGN:
			return 12;
		case COMMA:
			return 13;
	}
	return 0;
}

 int OpType::getOpType(string op)
{
	//TODO: complete mapping
	if (op == "+") {
		return ADD;
	}
	else if (op == "-") {
		return SUB;
	}
	else if (op == "*") {
		return MUL;
	}
	else if (op == "/") {
		return DIV;
	}
	else if (op == "%") {
		return MOD;
	}
	else if (op == " == ") {
		return EQ;
	}
	else if (op == "&") {
		return B_AND;
	}
	else if (op == "|") {
		return B_OR;
	}
	else if (op == "&&") {
		return L_AND;
	}
	else if (op == "||") {
		return L_OR;
	}
	else if (op == "=") {
		return ASSIGN;
	}
	else if (op == "<") {
		return LT;
	}
	else if (op == ">") {
		return GT;
	}
	else if (op == ">=") {
		return GTE;
	}
	else if (op == "<=") {
		return LTE;
	}
	else if (op == "_call") {
		return FUN_CALL;
	}
	return 0;
}

 bool OpType::isBinaryOp(int opType)
{
	//TODO need to be expanded
	switch (opType) {
	case ADD:
	case SUB:
	case MUL:
	case DIV:
	case MOD:
	case EQ:
	case NOT_EQ:
	case L_AND:
	case L_OR:
	case B_OR:
	case B_AND:
	case LT:
	case GT:
	case LTE:
	case GTE:
	case ASSIGN:
		return true;
	}
	return 0;
}

 bool OpType::isUnaryOp(int opType)
{
	switch (opType){
	case B_NOT:
	case L_NOT:
		return true;
	}
	return false;
}

 int OpType::LeftOrRightAssociate(int OpType)
 {
	 switch (OpType) {
	 case L_NOT:
	 case B_NOT:
		 return RIGHT_ASSOC;
	 case INC:
	 case DEC:
		 return INDETERMINATE;

	}
 }


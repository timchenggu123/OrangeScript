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
		case FUN:
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


#pragma once
#include <string>
#include "Lexer.h"
#include <list>
#include <string>
using std::string;
class Ast
{
public:
	enum ExpType {
		INTEGER,
		STRING,
		VARIABLE,
		UNARY,
		BINARY,
		CALL,
		PROJECTION,
		RECORD
	};
	struct Exp {
		int expType;
		int opType;
		Exp* left;
		Exp* right;
		string str_attr;
		int int_attr;
		list<Exp>* arguments;
	};
	Exp* makeIntegerExp(int i);
	Exp* makeStringExp(string s);
	Exp* makeVariableExp(string s);
	Exp* makeUnaryExp(int opType, Exp* left);
	Exp* makeBinaryExp(int opType, Exp* left, Exp* right);
	Exp* makeCallExp(string name, list<Exp>* arguments);
	//Exp* makeProjectionExp(list<Lexer::Token> tokens); //These are to be implemented in fur
	//Exp* makeRecordExp(list<Lexer::Token> tokens);
	Ast();
	~Ast();
private:
	Exp* root;
};


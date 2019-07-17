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
		Exp* parent;
		Exp* left;
		Exp* right;
		string str_attr;
		int int_attr;
		list<Exp>* arguments;
	};

	Exp* makeIntegerExp(int i);
	Exp* makeStringExp(string s);
	Exp* makeVariableExp(string s);
	Exp* makeUnaryExp(int opType, Exp* l);
	Exp* makeBinaryExp(int opType, Exp* l, Exp* r);
	Exp* makeCallExp(string name, list<Exp>* args);
	//Exp* makeProjectionExp(list<Lexer::Token> tokens); //These are to be implemented in fur
	//Exp* makeRecordExp(list<Lexer::Token> tokens);
	Ast();
	~Ast();

	Exp* getRoot();

private:
	Exp* root;
};


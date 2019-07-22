#pragma once
#include <string>
#include <list>
#include <string>
#include "Lexer.h"


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

	static Exp* makeIntegerExp(int i);
	static Exp* makeStringExp(string s);
	static Exp* makeVariableExp(string s);
	static Exp* makeUnaryExp(int opType, Exp* l);
	static Exp* makeBinaryExp(int opType, Exp* l, Exp* r);
	static Exp* makeCallExp(string name, list<Exp>* args);
	static int getExpType(Lexer::Token* token);
	//Exp* makeProjectionExp(list<Lexer::Token> tokens); //These are to be implemented in fur
	//Exp* makeRecordExp(list<Lexer::Token> tokens);
	Ast();
	~Ast();

	Exp* getRoot();
	void setRoot(Exp* node);

private:
	Exp* root;
};


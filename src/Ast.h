#pragma once
#include <string>
#include <list>
#include <string>
#include "Lexer.h"
#include <map>

using std::string;
class Ast
{
public:
	enum ExpType {
		NULL_TYPE,
		INTEGER,
		DECLARE,
		DECIMAL,
		STRING,
		VARIABLE,
		UNARY,
		BINARY,
		CALL,
		CODE_BLK,
		FOR,
		WHILE,
		IF,
		PROJECTION,
		RECORD,
		INSTR,
		PRINT,
		FUNCTION
	};

	struct Exp {
		int expType;
		int opType;
		Exp* parent;
		Exp* left;
		Exp* right;
		string str_attr;
		int int_attr;
		double double_attr;
		list<Exp*>* arguments;

		string str_return;
		int int_return;
		double double_return;

		bool is_str_return = false;
		bool is_int_return = false;
		bool is_double_return = false;
		bool is_symbolic_return = false;

		bool is_str_attr = false;
		bool is_int_attr = false;
		bool is_double_attr = false;

		int ln = -1;
		int col = -1;
	};

	static Exp* makeIntegerExp(int i, int ln, int col);
	static Exp* makeDecimalExp(string s, int ln, int col);
	static Exp* makeStringExp(string s, int ln, int col);
	static Exp* makeVariableExp(string s, int ln, int col);
	static Exp* makeUnaryExp(int opType, Exp* l, int ln, int col);
	static Exp* makeBinaryExp(int opType, Exp* l, Exp* r, int ln, int col);
	static Exp* makeCallExp(Ast::Exp* label, list<Exp*>* args, int ln, int col);
	static Exp* makeCodeBlock(list<Exp*>* args, int ln, int col);
	static Exp* makeForLoop(Exp* control, list<Exp*>* args, int ln, int col);
	static Exp* makeIfConditional(Exp* condition, list<Exp*>* args, int ln, int col);
	static Exp* makeWhileLoop(Exp* condition, list<Exp*>* args, int ln, int col);
	static Exp* makeDeclareVar(Exp* assignment, int ln, int col);
	static Exp* makeInstruction(int instruction, int ln, int col);
	static Exp* makeFunction(std::string label, list<Exp*>* params, Exp* codeBlock, int ln, int col);
	
	static int getCodeBlockType(Lexer::Token* token);
	static bool isCodeBlock(Exp* e);

	static void clearReturnVal(Exp* node);
	//Exp* makeProjectionExp(list<Lexer::Token> tokens); //These are to be implemented in fur
	//Exp* makeRecordExp(list<Lexer::Token> tokens);
	Ast();
	~Ast();

	Exp* getRoot();
	void setRoot(Exp* node);

private:
	Exp* root;
};


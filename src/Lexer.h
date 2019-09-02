#ifndef LEXER_H
#define LEXER_H

#include "Trie.h"
#include "CharType.h"
#include "OpType.h"
#include <vector>
#include <fstream>
#include <list>
#include <string>
using std::ifstream;
using std::string;

class Lexer {
public:
	struct Token {
		int type;
		int opType;
		string text;
		int ln;
		int col;
		int id;
		Token* next;
		Token* prev;
	};

	enum Tokens {
		NEW_LINE,
		VARIABLE,
		KEYWORD,
		NUM_LITERAL,
		STR_LITERAL,
		OPERATOR,
		GROUPER_1,
		GROUPER_2,
		BREAK,
		DELIMITER,
	};

	const std::vector<string> keyword_list = {
		"for",
		"break",
		"continue",
		"while",
		"if",
		"else",
		"elseif",
		"end",
		"print"
		"fun"
	};

	Lexer();
	list<Token*>* run(string inputFile);

private:
	//private variables:
	int currentLn;
	int currentCol;
	int currentId;

	//private methods:
	Trie *syntaxTrie;
	void setUp();
	bool isWord(string buffer);
	bool isNum(string buffer);
	bool isKeyword(string buffer);
	bool isOperator(string buffer);
	bool isGrouper_1(string buffer);
	bool isGrouper_2(string buffer);
	bool isdelimiter(string buffer);

	bool checkNewLine(char c);
	void makeToken(list<Token*>* object, string buffer, int type);

	CharType* charType;
	OpType* opType;

	//temp variabels for make token

};

#endif // !LEXTER_h



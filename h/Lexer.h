#ifndef LEXER_H
#define LEXER_H

#include "..\helper_h\Trie.h"
#include "..\h\CharType.h"
#include <vector>
#include <fstream>
#include <list>
#include <string>
using std::ifstream;
using std::string;

class Lexer {
private:
	Trie *syntaxTrie;
	void setUp();
	bool isWord(string buffer);
	bool isNum(string buffer);
	bool isKeyword(string buffer);
	bool isOperator(string buffer);
	bool isGrouper_1(string buffer);
	bool isGrouper_2(string buffer);
	void checkOut(list<pair<int, string>>* object, string buffer, int token);
	CharType* charType;

public:
	enum Tokens {
		NEW_LINE,
		VARIABLE,
		KEYWORD,
		NUM_LITERAL,
		STR_LITERAL,
		OPERATOR,
		GROUPER_1,
		GROUPER_2
	};
	Lexer();
	list<pair<int, string>> run(string inputFile);

};

#endif // !LEXTER_h



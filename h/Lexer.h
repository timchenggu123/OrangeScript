#ifndef LEXER_h
#define LEXER_h

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
	void checkOut(list<pair<int, string>>* object, string buffer, int token);
	CharType* charType;

public:
	enum Tokens {
		VARIABLE,
		KEYWORD,
		NUM_LITERAL,
		STR_LITERAL,
		OPERATOR,
		GROUPER
	};
	Lexer();
	void start(ifstream InputFile);

};

#endif // !LEXTER_h



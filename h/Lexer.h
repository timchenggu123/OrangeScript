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
	bool isKeyword(string buffer);
	CharType* charType;

public:
	Lexer();
	void start(ifstream InputFile);

};

#endif // !LEXTER_h



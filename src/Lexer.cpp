#include "..\helper_h\Trie.h"
#include "..\h\Lexer.h"


#include <fstream>
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
Lexer::Lexer() :
	syntaxTrie(new Trie()),
	charType(new CharType())
{
	setUp;
}

void Lexer::setUp() {
	//TODO: add more 
	syntaxTrie->insert("for");
	syntaxTrie->insert("continue");
	syntaxTrie->insert("break");
	syntaxTrie->insert("while");
	syntaxTrie->insert("if");
	syntaxTrie->insert("elif");
	syntaxTrie->insert("else");
}

void Lexer::start(ifstream inputFile) {
	char c;
	string buffer = "";

	while (inputFile >> c) {

		if (charType->getCharType(c) == CharType::Types::SPACE) {
			if (isKeyword(buffer)) {
				checkOut(*returnStream, buffer);
				buffer = "";
			}
			continue;
		}
		else if (charType->getCharType(c) == CharType::Types::NUM) {

		}
		else if (charType->getCharType(c) == CharType::Types::LETTER) {

		}
		else if (charType->getCharType(c) == CharType::Types::GROUPER) {
		
		}
		else if (charType->getCharType(c) == CharType::Types::DELIMITER) {
		
		}
	
	}
}

bool Lexer::isKeyword(string buffer) {
	//check if the buffer is an empty buffer.
	if (buffer.length() == 0) {
		return false;
	}
	//check if the buffer is all letters; if not, return false
	for (char c : buffer) {
		if (!charType->getCharType(c) == CharType::Types::LETTER) {
			return false;
		}
	}

	//check if the buffer is a memember of the syntax trie;
	//and return the result.

	return syntaxTrie->member(buffer);
}
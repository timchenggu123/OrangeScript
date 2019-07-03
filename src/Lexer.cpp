#include "..\helper_h\Trie.h"
#include "..\h\Lexer.h"


#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <list>

using std::list;
using std::pair;
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
	list < pair <int, string> > *returnObject = new list < pair <int, string> >();

	while (inputFile >> c) {

		if (charType->getCharType(c) == CharType::Types::SPACE) {
			if (isKeyword(buffer)) {
				checkOut(returnObject, buffer, Tokens::KEYWORD);
				buffer = "";
			}
			else if (isWord(buffer)) {
				checkOut(returnObject,buffer, Tokens::VARIABLE);
				buffer = "";
			}
			else if (isNum(buffer)) {
				checkOut(returnObject, buffer, Tokens::NUM_LITERAL);
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

bool Lexer::isWord(string buffer) {
	//checks if buffer contains any non LETTER character
	
	if (buffer.length() == 0) {
		return false;
	}

	for (char c : buffer) {
		if (!charType->getCharType(c) == CharType::Types::LETTER) {
			return false;
		}
	}
	
	return true;
}

bool Lexer::isNum(string buffer) {
	//check if the buffer is an empty buffer.
	if (buffer.length() == 0) {
		return false;
	}
	if (buffer[0] == (int) "-") {
		for (char c : buffer.substr(1,buffer.length())) {
			if (!charType->getCharType(c) == CharType::Types::NUM) {
				return false;
			}
		}
	}
	else {
		for (char c : buffer) {
			if (!charType->getCharType(c) == CharType::Types::NUM) {
				return false;
			}
		}
	}
	return true;
}
bool Lexer::isKeyword(string buffer) {
	//check if the buffer is an empty buffer.
	if (buffer.length() == 0) {
		return false;
	}
	//check if the buffer is all LETTER; if not, return false
	if (!isWord) {
		return false;
	}
	//check if the buffer is a memember of the syntax trie;
	//and return the result.

	return syntaxTrie->member(buffer);
}

void Lexer::checkOut(list<pair<int,string>>* object, string buffer, int token) {
	pair<int, string> item(token, buffer);
	object->push_back(item);
}
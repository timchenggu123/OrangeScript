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
using std::cerr;

Lexer::Lexer() :
	syntaxTrie(new Trie()),
	charType(new CharType())
{
	setUp();
	//initialize vairables
	currentLn = 1;
	currentCol = 1;
	currentId = 1;
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

list<pair<int,string>> Lexer::run(string inputText) {

	char c;
	string buffer = "";
	list < pair <int, string> > returnObject = list < pair <int, string> >();
	bool listening_string = false;
	int current_type = CharType::Types::NULL_TYPE;
	int previous_type = CharType::Types::NULL_TYPE;
	bool check_out = false;
	for (char c: inputText) {
		/*This part of the code uses edge-triggered design to separate
		input string into tokens.
		*/
		checkNewLine(c);

		current_type = charType->getCharType(c);

		if (current_type == CharType::Types::MARKER_1){
			if (listening_string) {
				listening_string = false;
				checkOut(&returnObject, buffer, Tokens::STR_LITERAL);
				previous_type = current_type;
				buffer = "";
				continue;
			}
			else {
				listening_string = true;
				continue;
			}
		}
		if (current_type== CharType::Types::MARKER_2){
			listening_string = false;
			checkOut(&returnObject, buffer, Tokens::STR_LITERAL);
			previous_type = current_type;
			buffer = "";
			continue;
		}
		if (listening_string){
			buffer += c;
			continue;
		}
		
		if (charType->isNullChar(c) &&
			previous_type != current_type){
			check_out = true;
		}

		if (check_out) {
			check_out = false;
			
			if (isKeyword(buffer)) {
				checkOut(&returnObject, buffer, Tokens::KEYWORD);
				buffer = "";
			}
			else if (isWord(buffer)) {
				checkOut(&returnObject,buffer, Tokens::VARIABLE);
				buffer = "";
			}
			else if (isNum(buffer)) {
				checkOut(&returnObject, buffer, Tokens::NUM_LITERAL);
				buffer = "";      
			}
			else if (isOperator(buffer)) {
				checkOut(&returnObject, buffer, Tokens::OPERATOR);
				buffer = "";
			}
			else if (isGrouper_1(buffer)) {
				checkOut(&returnObject, buffer, Tokens::GROUPER_1);
				buffer = "";
			}
			else if (isGrouper_2(buffer)) {
				checkOut(&returnObject, buffer, Tokens::GROUPER_2);
				buffer = "";
			}
			else if (buffer.length() != 0) {
				//TODO show more details 
				cerr << "illegal input:" << buffer << endl;
				exit(1);
			}

		}

		if (charType->isNullChar(c)) {
			previous_type = current_type;
		} else {
			buffer += c;
			previous_type = current_type;
		}
	}
	return returnObject;
}

bool Lexer::isWord(string buffer) {
	//checks if buffer contains any non LETTER character
	
	if (buffer.length() == 0) {
		return false;
	}

	for (char c : buffer) {
		if (charType->getCharType(c) != CharType::Types::LETTER) {
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
			if (charType->getCharType(c) != CharType::Types::NUM) {
				return false;
			}
		}
	}
	else {
		for (char c : buffer) {
			if (charType->getCharType(c) != CharType::Types::NUM) {
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
	if (!isWord(buffer)) {
		return false;
	}
	//check if the buffer is a memember of the syntax trie;
	//and return the result.

	return syntaxTrie->member(buffer);
}

bool Lexer::isOperator(string buffer)
{

	if (buffer.length() == 0) {
		return false;
	}

	for (char c : buffer) {
		if (charType->getCharType(c) != CharType::Types::OPERATOR) {
			return false;
		}
	}

	return true;
}

bool Lexer::isGrouper_1(string buffer)
{

	if (buffer.length() == 0) {
		return false;
	}

	for (char c : buffer) {
		if (charType->getCharType(c) != CharType::Types::GROUPER_1) {
			return false;
		}
	}

	return true;
}

bool Lexer::isGrouper_2(string buffer)
{

	if (buffer.length() == 0) {
		return false;
	}

	for (char c : buffer) {
		if (charType->getCharType(c) != CharType::Types::GROUPER_2) {
			return false;
		}
	}

	return true;
}

void Lexer::checkNewLine(char c){
	if (c == 12){
		currentLn++;
	}
}
void Lexer::checkOut(list<Token>* object, string buffer, int type) {
	Token token;
	token.type = type;
	token.text = buffer;
	token.id = this.currentId;
	token.ln = this.currentLn;
	token.col = this.currentCol;
	//increment id by one after checking out.
	currentId++;

	object->push_back(token);
}
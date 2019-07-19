#include "Trie.h"
#include "Lexer.h"


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
	charType(new CharType()),
	currentLn(1),
	currentCol(1),
	currentId(1)
{
	setUp();
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

list<Lexer::Token> Lexer::run(string inputText) {

	char c;
	string buffer = "";
	list <Token> returnObject = list <Token>();
	bool listening_string = false;
	int* current_type;
	int* previous_type;
	bool check_out = false;;
	for (char c: inputText) {
		/*This part of the code uses edge-triggered design to separate
		input string into tokens.
		*/
		if (checkNewLine(c)) {
			currentLn++;
			buffer = "";
			makeToken(&returnObject, buffer, Tokens::BREAK);
			previous_type = current_type;
			continue;
		 }

		current_type = charType->getCharType(c);

		if (charType->isEqual(current_type, CharType::MARKER_2)){
			if (listening_string) {
				listening_string = false;
				makeToken(&returnObject, buffer, Tokens::STR_LITERAL);
				previous_type = current_type;
				buffer = "";
				continue;
			}
			else {
				listening_string = true;
				continue;
			}
		}
		if (charType->isEqual(current_type, CharType::MARKER_2)){
			listening_string = false;
			makeToken(&returnObject, buffer, Tokens::STR_LITERAL);
			previous_type = current_type;
			buffer = "";
			continue;
		}
		if (listening_string){
			buffer += c;
			continue;
		}
		
		if (!(charType->isNullType(previous_type)) &&
			!charType->isEqual(previous_type,current_type)){
			check_out = true;
		}

		if (check_out) {
			check_out = false;
			
			if (isKeyword(buffer)) {
				makeToken(&returnObject, buffer, Tokens::KEYWORD);
				buffer = "";
			}
			else if (isWord(buffer)) {
				makeToken(&returnObject,buffer, Tokens::VARIABLE);
				buffer = "";
			}
			else if (isOperator(buffer)) {
				makeToken(&returnObject, buffer, Tokens::OPERATOR);
				buffer = "";
			}
			else if (isNum(buffer)) {
				makeToken(&returnObject, buffer, Tokens::NUM_LITERAL);
				buffer = "";
			}
			else if (isGrouper_1(buffer)) {	
				makeToken(&returnObject, buffer, Tokens::GROUPER_1);
				buffer = "";
			}
			else if (isGrouper_2(buffer)) {
				makeToken(&returnObject, buffer, Tokens::GROUPER_2);
				buffer = "";
			}
			else if (buffer.length() != 0) {
				//TODO show more details 
				cerr << "illegal input:" << buffer << endl;
				exit(1);
			}

		}

		if (charType->isNullType(current_type)) {
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
		if (!charType->isEqual(charType->getCharType(c), CharType::LETTER)) {
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
			if (!charType->isEqual(charType->getCharType(c),CharType::NUM)) {
				return false;
			}
		}
	}
	else {
		for (char c : buffer) {
			if (!charType->isEqual(charType->getCharType(c),CharType::NUM)) {
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
		if (!charType->isEqual(charType->getCharType(c),CharType::OPERATOR)) {
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
		if (!charType->isEqual(charType->getCharType(c), CharType::Types::GROUPER_1)) {
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
		if (!charType->isEqual(charType->getCharType(c), CharType::Types::GROUPER_2)) {
			return false;
		}
	}

	return true;
}

bool Lexer::checkNewLine(char c){
	if (c == 12){
		return true;
	}
	return false;
}

void Lexer::makeToken(list<Token>* object, string buffer, int type) {
	Token token;
	if (type == OPERATOR){
		token.type = opType.getOpType(buffer);
	}else{
		token.type = type;
	}

	token.text = buffer;
	token.id = currentId;
	token.ln = currentLn;
	token.col = currentCol;
	token.next = nullptr;
	//increment id by one after checking out.
	currentId++;
	object->back().next = &token;
	token.prev = &object->back();
	object->push_back(token);
}
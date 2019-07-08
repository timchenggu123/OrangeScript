#include "../h/CharType.h"

using std::string;
//Different characters can have different meaning under different context.
//Thus, in the parser, we need a way to tell the context. 
CharType::CharType()
{
	//initialize matrices
	for (int i = 0; i < 128; i++)
	{
		mType[i] = 0;
	}
	setUp();
}

void CharType::setUp() {
	//TODO: store character definitions in a separate file
	//character definitions
	//const int ILLEGAL;

	mType[NEWLINE_CHAR] = Types::NEW_LINE;
	mType[DELIMITER_CHAR] = Types::DELIMITER;
	mType[MARKER_1_CHAR] = Types::MARKER_1;
	mType[MARKER_2_CHAR] = Types::MARKER_2;

	for (int i : SPACE_LIST) {
		mType[i] = Types::SPACE;
	}

	for (int i : OPERATOR_LIST) {
		mType[i] = Types::OPERATOR;
	}

	for (int i : GROUPER_1_LIST) {
		mType[i] = Types::GROUPER_1;
	}

	for (int i : GROUPER_2_LIST){
		mType[i] = Types::GROUPER_2;
	}

	for (int i : NUM_LIST) {
		mType[i] = Types::NUM;
	}

	for (int i : LETTER_LIST) {
		mType[i] = Types::LETTER;
	}
}

bool CharType::isNullChar(char c) {
	//Some characters, such as space, tab, quotation mark, 
	//and comment marker (#) do not hold any actually meaning
	//and therefore need to be marked as null marker for 
	//the lexer. That's is why this function exists.

	for (int i = 0; i < 5; i++) {
		if (NULL_CHARACTERS[i] == c) {
			return true;
		}
	}
	
	return false;
}

int CharType::getCharType(char c) {
	return mType[c];
}
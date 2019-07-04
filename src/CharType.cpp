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
	//character definitions
	const int SPACE_CHAR = 32;
	const int NEWLINE_CHAR = 59;
	const int MARKER_1_CHAR = 34;// ", 
	const int MARKER_2_CHAR = 92;// ", 
	const int OPERATOR_LIST[12] = { 33,37,38,42,43,45,47,60,61,62,94,124 }; //!,%,&,*,+,/,<,=,>,^,|
	const int DELIMITER_CHAR = 44; //,
	const int GROUPER_1_LIST[3] = { 40,91,123 };  // (,),[,],{,}
	const int GROUPER_2_LIST[3] = { 41,93,125 };  // (,),[,],{,}
	const int NUM_LIST[11] = { 46,48,49,50,51,52,53,54,55,56,57 };
	const int LETTER_LIST[53] = { 65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,
		97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,95 };
	//const int SPECIAL; --> to be implemented. 
	//const int ILLEGAL;

	mType[SPACE_CHAR] = Types::SPACE;
	mType[NEWLINE_CHAR] = Types::NEW_LINE;
	mType[DELIMITER_CHAR] = Types::DELIMITER;
	mType[MARKER_1_CHAR] = Types::MARKER_1;
	mType[MARKER_2_CHAR] = Types::MARKER_2;

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

int CharType::getCharType(char c) {
	return mType[c];
}
#include "CharType.h"

using std::string;
//Different characters can have different meaning under different context.
//Thus, in the parser, we need a way to tell the context. 
CharType::CharType()
{
	//initialize matrices
	for (int i = 0; i < 128; i++)
	{
		int m[5];
		mType[i] = m;
		for (int j = 0; j < 5; j++) {
			mType[i][j] == 0;
		}
	}
	setUp();
}

void CharType::setUp() {
	//TODO: store character definitions in a separate file
	//character definitions
	//const int ILLEGAL;

	mType[NEWLINE_CHAR][0] = Types::NEW_LINE;
	mType[DELIMITER_CHAR][0] = Types::DELIMITER;
	mType[MARKER_1_CHAR][0] = Types::MARKER_1;
	mType[MARKER_2_CHAR][0] = Types::MARKER_2;

	for (int i : SPACE_LIST) {
		int j = 0;
		while (mType[i][j] != 0) {
			j++;
		}
		mType[i][j]= Types::SPACE;
	}

	for (int i : OPERATOR_LIST) {
		int j = 0;
		while (mType[i][j] != 0) {
			j++;
		}
		mType[i][j] = Types::OPERATOR;
	}

	for (int i : GROUPER_1_LIST) {
		int j = 0;
		while (mType[i][j] != 0) {
			j++;
		}
		mType[i][j] = Types::GROUPER_1;
	}

	for (int i : GROUPER_2_LIST){
		int j = 0;
		while (mType[i][j] != 0) {
			j++;
		}
		mType[i][j] = Types::GROUPER_2;
	}

	for (int i : NUM_LIST) {
		int j = 0;
		while (mType[i][j] != 0) {
			j++;
		}
		mType[i][j] = Types::NUM;
	}

	for (int i : LETTER_LIST) {
		int j = 0;
		while (mType[i][j] != 0) {
			j++;
		}
		mType[i][j] = Types::LETTER;
	}
}

bool CharType::isNullType(int* type) {
	//Some characters, such as space, tab, quotation mark, 
	//and comment marker (#) do not hold any actually meaning
	//and therefore need to be marked as null marker for 
	//the lexer. That's is why this function exists.

	for (int i = 0; i < 6; i++) {

		if (type[0] == Types::SPACE    ||
			type[0] == Types::NEW_LINE ||
			type[0] == Types::MARKER_1 ||
			type[0] == Types::MARKER_2 ||
			type[0] == Types::NULL_TYPE){
			return true;
		}
	}
	return false;
}

bool CharType::isEqual(int * type_1, int * type_2)
{	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (type_1[i] == type_2[j]
				&& type_1[i] != NULL_TYPE 
				&& type_2[i] != NULL_TYPE) {
				return true;
			}
		}
}
	return false;
}

bool CharType::isEqual(int * type_1, int  type_2)
{
	for (int i = 0; i < 5; i++) {
		if (type_1[i] == type_2
			&& type_1[i] != NULL_TYPE
			&& type_2 != NULL_TYPE) {
			return true;
		}
	}
	return false;
}

int* CharType::getCharType(char c) {
	return mType[c];
}
#include "../h/CharType.h"

CharType::CharType()
{
	//initialize matrices
	for (int i = 0; i < 128; i++)
	{
		mType[i] = 0;
	}
}

void CharType::setUp() {
	//character definitions
	const int SPACE_CHAR = 32;
	const int NEWLINE_CHAR = 59;
	const int MARKER_LIST[2] = { 34,92 };// ", 
	const int OPERATOR_LIST[12] = { 33,37,38,42,43,45,47,60,61,62,94,124 }; //!,%,&,*,+,/,<,=,>,^,|
	const int DELIMITER_CHAR = 44; //,
	const int GROUPER_LIST[6] = { 40,41,91,93,123,125 };  // (,),[,],{,}
	const int NUM_LIST[11] = { 46,48,49,50,51,52,53,54,55,56,57 };
	const int LETTER_LIST[53] = { 65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,
		97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,95 };
	//const int SPECIAL; --> to be implemented. 
	//const int ILLEGAL;
}
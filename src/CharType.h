#ifndef CHARTYPE_H
#define CHARTYPE_H
#include <string>
#include <vector>
using namespace std;

class CharType{
    private:

        //Essentially the ASCII table here
        int* mType[128];
		void setUp();

		// character definitions
		const int SPACE_LIST[2] = { 9,32 }; //we are treating tab as a space here for now. Might need future change
		const int NEWLINE_CHAR = 59;
		const int MARKER_1_CHAR = 34;// ", 
		const int MARKER_2_CHAR = 92;// ", 
		const int OPERATOR_LIST[13] = { 33,37,38,42,43,45,46,47,60,61,62,94,124}; //!,%,&,*,+,/,<,=,>,^,|
		const int DELIMITER_CHAR = 44; //,
		const int GROUPER_1_LIST[3] = { 40,91,123 };  // (,),[,],{,}
		const int GROUPER_2_LIST[3] = { 41,93,125 };  // (,),[,],{,}
		const int NUM_LIST[11] = { 46,48,49,50,51,52,53,54,55,56,57 };
		const int LETTER_LIST[53] = { 65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,
			97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,95 };

		//list of null characters ( see isNullCharacter() definition for more details)
		const int NULL_CHARACTERS[6] = { 9,32,59,32,34,92 };

    public:
		enum Types {
			NULL_TYPE,
			SPACE,
			NEW_LINE,
			DELIMITER,
			GROUPER_1,
			GROUPER_2,
			MARKER_1, //e.g. "" // /* */ in C++.
			MARKER_2,
			OPERATOR,
			NUM,
			LETTER,
			ILLEGAL,
			SPECIAL
		};

        CharType();
        int* getCharType (char c);
		bool isNullType(int* type);
		bool isEqual(int* type_1, int* type_2);
		bool isEqual(int* type_1, int type_2);
};

#endif
#pragma once
#include <string>

using namespace std;

class CharType{
    private:

        //Essentially the ASCII table here
        int mType[128];
		void setUp();
    public:
		enum Types {
			SPACE,
			NEWLINE,
			DELIMITER,
			GROUPER_1,
			GROUPER_2
			MARKER_1, //e.g. "" // /* */ in C++.
			MARKER_2,
			OPERATOR,
			NUM,
			LETTER,
			ILLEGAL,
			SPECIAL,
			NULL
		};

        CharType();
        int getCharType (char c);
};
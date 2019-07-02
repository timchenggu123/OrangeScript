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
			GROUPER,
			MARKER, //e.g. "" // /* */ in C++.
			OPERATOR,
			NUM,
			LETTER,
			ILLEGAL,
			SPECIAL,
		};

        CharType();
        int getCharType (char c);
};
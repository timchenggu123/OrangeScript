#ifndef CHARTYPE_H
#define CHARTYPE_H
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
			SPECIAL,
			NULL_TYPE
		};

        CharType();
        int getCharType (char c);
};

#endif
#pragma once
#include <string>

using namespace std;

class CharType{
    private:
        enum Types{
            SPACE,
            NEWLINE,
			DELIMiTER,
			GROUPER,
            MARKER, //e.g. "" // /* */ in C++.
            OPERATOR,
            NUM,
            LETTER,
            ILLEGAL,
			SPECIAL,
        };

        //Essentially the ASCII table here
        int mType[128];
        char mChar[128];
		void setUp();
    public:
        CharType();
        int lookUp (int args, char* argv);
};
#pragma once
#include <string>

using namespace std;

class CharType{
    private:
        enum Types{
            SPACE,
            NEWLINE,
            STRING,
            COMMENT,
            OPERATOR,
            NUM,
            LETTER,
            ILLEGAL,
        };

        //Essentially the ASCII table here
        int mType[128];
        char mChar[128];
    public:
        CharType();
        int lookUp (int args, char* argv);
        
};
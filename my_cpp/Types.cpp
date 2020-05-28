#include"Types.h"

MalToken::MalToken(tokenType _type) : type(_type){};

MalTokenSymbol::MalTokenSymbol(std::string& _name)
: MalToken(SYMBOL)
, name(_name){};

MalTokenNumber::MalTokenNumber(const std::string& _number)
: MalToken(NUMBER)
, value(stoi(_number)){};

MalTokenList::MalTokenList(const char _end_char)
: MalToken(LIST), close_char(_end_char){
    switch(close_char) {
        case ')':
            open_char = '(';
            break;
        case ']':
            open_char = '[';
            break;
        case '}':
            open_char = '{';
            break;
        case '"':
            open_char = '"';
    }
};


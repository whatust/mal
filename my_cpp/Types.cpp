#include"Types.h"

MalToken::MalToken(tokenType _type) : type(_type){};

MalTokenSymbol::MalTokenSymbol(std::string& _name)
: MalToken(SYMBOL)
, name(_name){};

MalTokenOperator::MalTokenOperator(const std::string& symbol, MalEnv& repl_env)
: MalToken(OPERATOR) {
    op = repl_env.find(symbol)->second;
};

MalTokenNumber::MalTokenNumber(const std::string& _number)
: MalToken(NUMBER)
, value(stoi(_number)){};

MalTokenNumber::MalTokenNumber(int _number)
: MalToken(NUMBER)
, value(_number){};

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


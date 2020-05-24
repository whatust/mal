#include"Types.h"

MalToken::MalToken(tokenType _type) : type(_type){};

MalTokenSymbol::MalTokenSymbol(string& _name)
: MalToken(SYMBOL)
, name(_name){};

MalTokenNumber::MalTokenNumber(const string& _number)
: MalToken(NUMBER)
, value(stoi(_number)){};

MalTokenList::MalTokenList()
: MalToken(LIST){};


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

MalTokenList::MalTokenList()
: MalToken(LIST) {};

MalTokenVector::MalTokenVector()
: MalToken(VECTOR) {};

MalTokenHashMap::MalTokenHashMap()
: MalToken(HASH_MAP) {};


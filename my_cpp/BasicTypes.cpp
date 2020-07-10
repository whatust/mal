#include"BasicTypes.h"

AstToken::AstToken(tokenType _type) : type(_type){};

AstTokenSymbol::AstTokenSymbol(std::string& _name)
: AstToken(SYMBOL)
, name(_name){};

AstTokenOperator::AstTokenOperator(std::string _name, MalFunction _op)
: AstToken(OPERATOR)
, op(_op)
, name(_name){};

std::shared_ptr<AstToken> AstTokenOperator::operator()(MalArgs args, MalArgs end) {
    return op(args, end);
};

AstTokenNumber::AstTokenNumber(const std::string& _number)
: AstToken(NUMBER)
, value(stoi(_number)){};

AstTokenNumber::AstTokenNumber(int _number)
: AstToken(NUMBER)
, value(_number){};

AstTokenList::AstTokenList()
: AstToken(LIST) {};

AstTokenList::AstTokenList(MalArgs init, MalArgs end)
: AstToken(LIST) {
    while(init != end) {
        list.push_back(*init);
        init++;
    }
};

AstTokenVector::AstTokenVector()
: AstToken(VECTOR) {};

AstTokenHashMap::AstTokenHashMap()
: AstToken(HASH_MAP) {};

AstTokenBool::AstTokenBool(const std::string& _value)
: AstToken(BOOL) {
    value = _value == "true" ? true : false;
};

AstTokenBool::AstTokenBool(bool _value)
: AstToken(BOOL)
, value(_value) {};


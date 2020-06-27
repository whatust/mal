#include"Types.h"

AstToken::AstToken(tokenType _type) : type(_type){};

AstTokenSymbol::AstTokenSymbol(std::string& _name)
: AstToken(SYMBOL)
, name(_name){};

AstTokenOperator::AstTokenOperator(MalFunction _op)
: AstToken(OPERATOR)
, op(_op) {};

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

AstTokenFunction::AstTokenFunction(MalEnv* _scope, std::shared_ptr<AstToken> _function)
: AstToken(FUNCTION)
, scope(_scope)
, function(_function) {};

AstTokenFunction::~AstTokenFunction() {};

AstTokenString::AstTokenString(std::string _value)
: AstToken(STRING) {

    for(int i=0; i < (int) _value.length(); i++) {
        if(_value[i] != '\\') {
            value.push_back(_value[i]);
        } else {
            i++;
            if(i < (int) _value.length()) {
                switch (_value[i]) {

                    case 'n':
                        value.push_back('\n');
                        break;
                    case '"':
                        value.push_back('"');
                        break;
                    case '\\':
                        value.push_back('\\');
                        break;
                    default:
                        value.push_back('\\');
                        value.push_back(_value[i]);
                }
            }
        }
    }
}

AstTokenNil::AstTokenNil()
: AstToken(NIL) {};


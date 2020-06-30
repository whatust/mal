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

AstTokenFunction::AstTokenFunction(MalEnv* _scope, std::shared_ptr<AstToken>_params,
                                            std::shared_ptr<AstToken> _function)
: AstToken(FUNCTION)
, scope(_scope)
, function(_function) {

    bool next_args = false;
    std::shared_ptr<AstTokenList> list_ast;
    list_ast = std::static_pointer_cast<AstTokenList>(_params);

    for(auto key : list_ast->list) {

        std::shared_ptr<AstTokenSymbol> symbol;
        symbol = std::static_pointer_cast<AstTokenSymbol>(key);

        if(next_args){
            larg = symbol->name;
            next_args = false;
        }

        if(symbol->name.compare("&") == 0 && larg.empty()){
            next_args = true;
        }else{
            params.push_back(symbol->name);
        }
    }

};

AstTokenFunction::~AstTokenFunction() {
};


AstTokenString::AstTokenString(std::string _value)
: AstToken(STRING)
, value(_value) {};

AstTokenString::AstTokenString(std::string _value, bool clean)
: AstToken(STRING) {

    for(int i=1; i < (int) _value.length()-1; i++) {
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
};

AstTokenKeyword::AstTokenKeyword(std::string _value)
: AstToken(KEYWORD) {
    value = _value.replace(0, 1, "\xff");
};

AstTokenNil::AstTokenNil()
: AstToken(NIL) {};


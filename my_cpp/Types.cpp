#include"Types.h"

AstTokenFunction::AstTokenFunction(std::shared_ptr<MalEnv> _scope, std::shared_ptr<AstToken>_params,
                                            std::shared_ptr<AstToken> _function)
: AstToken(FUNCTION)
, function(_function) {

    scope = _scope;

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

AstTokenAtom::AstTokenAtom(std::shared_ptr<AstToken> _object) 
: AstToken(ATOM) {
    object = _object;
}

AstTokenNil::AstTokenNil()
: AstToken(NIL) {};


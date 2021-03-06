#include"Types.h"

AstTokenOperator::AstTokenOperator() : AstToken(OPERATOR) {
    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);
};

AstTokenOperator::AstTokenOperator(std::string _name, MalFunction _op)
: AstToken(OPERATOR)
, op(_op) , name(_name) {
    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);
};

std::shared_ptr<AstToken> AstTokenOperator::operator()(MalArgs args, MalArgs end) {
    return op(args, end);
};

AstTokenFunction::AstTokenFunction() : AstToken(FUNCTION) {};
AstTokenFunction::AstTokenFunction(std::shared_ptr<MalEnv> _scope, std::shared_ptr<AstToken>_params,
                                            std::shared_ptr<AstToken> _function, bool _macro)
: AstToken(FUNCTION) , function(_function) , is_macro(_macro) {

    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);

    scope = _scope;

    bool next_args = false;
    std::shared_ptr<AstTokenList> list_ast;
    list_ast = as_type<AstTokenList>(_params);

    for(auto key : list_ast->list) {

        std::shared_ptr<AstTokenSymbol> symbol;
        symbol = as_type<AstTokenSymbol>(key);

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
    //std::cout << "SCOPE" << std::endl;
    //scope->print();
};

AstTokenFunction::~AstTokenFunction() {};

AstTokenAtom::AstTokenAtom() : AstToken(ATOM) {};

AstTokenAtom::AstTokenAtom(std::shared_ptr<AstToken> _object)
: AstToken(ATOM) {

    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);

    object = _object;
}

AstTokenHashMap::AstTokenHashMap()
: AstToken(HASH_MAP) {
    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);
};

AstTokenHashMap::AstTokenHashMap(MalArgs init, MalArgs end)
: AstToken(HASH_MAP) {

    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);

    while(init != end) {

        std::string key;

        if((*init)->type == STRING) {
            key = as_type<AstTokenString>(*init++)->value;
        }else if((*init)->type == KEYWORD) {
            key = as_type<AstTokenKeyword>(*init++)->value;
        }

        map[key] = *init++;
    }
};

AstTokenException::AstTokenException(std::shared_ptr<AstToken> _ast)
: AstToken(EXCEPTION) { 

    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);

    ast = _ast;
};


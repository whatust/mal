#ifndef TYPES_H_
#define TYPES_H_

#include<memory>
#include<string>
#include<vector>

#include"BasicTypes.h"
#include"Environment.h"

class AstTokenFunction : public AstToken {
    public:
        const static tokenType ctype = FUNCTION;
        std::shared_ptr<MalEnv> scope;
        std::string larg;
        std::vector<std::string> params;
        std::shared_ptr<AstToken> function;
        bool is_macro;
        AstTokenFunction(std::shared_ptr<MalEnv> _scope, std::shared_ptr<AstToken> _params,
                                    std::shared_ptr<AstToken> _function, bool _macro);
        ~AstTokenFunction();
};

class AstTokenString : public AstToken {
    public:
        const static tokenType ctype = STRING;
        std::string value;
        AstTokenString(std::string _value);
        AstTokenString(std::string _value, bool clean);
};

class AstTokenKeyword : public AstToken {
    public:
        const static tokenType ctype = KEYWORD;
        std::string value;
        AstTokenKeyword(std::string _value);
};

class AstTokenAtom : public AstToken {
    public:
        const static tokenType ctype = ATOM;
        std::shared_ptr<AstToken> object;
        AstTokenAtom(std::shared_ptr<AstToken> _object);
};

class AstTokenNil : public AstToken {
    public:
        const static tokenType ctype = NIL;
        AstTokenNil();
};

template <class T>
std::shared_ptr<T> as_type(std::shared_ptr<AstToken> ast) {

    if(ast->type == T::ctype) {
        return std::static_pointer_cast<T>(ast);
    }

    if(T::ctype == LIST && ast->type == VECTOR) {
        return std::static_pointer_cast<T>(ast);
    }

    if(T::ctype == LIST && ast->type == HASH_MAP) {
        return std::static_pointer_cast<T>(ast);
    }

    throw TokenException(T::ctype, ast->type);
    return std::static_pointer_cast<T>(ast);
}

#endif  //TYPE_H_

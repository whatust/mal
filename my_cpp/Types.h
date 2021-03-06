#ifndef TYPES_H_
#define TYPES_H_

#include<memory>
#include<string>
#include<vector>

#include"BasicTypes.h"
#include"Environment.h"

typedef std::function<std::shared_ptr<AstToken>(MalArgs, MalArgs)> MalFunction;

class AstTokenOperator : public AstToken {
    public:
        const static tokenType ctype = OPERATOR;
        MalFunction op;
        std::string name;
        AstTokenOperator();
        AstTokenOperator(std::string _name, MalFunction _op);
        std::shared_ptr<AstToken> operator()(MalArgs args, MalArgs end);
};

class AstTokenFunction : public AstToken {
    public:
        const static tokenType ctype = FUNCTION;
        std::shared_ptr<MalEnv> scope;
        std::string larg;
        std::vector<std::string> params;
        std::shared_ptr<AstToken> function;
        bool is_macro;
        AstTokenFunction();
        AstTokenFunction(std::shared_ptr<MalEnv> _scope, std::shared_ptr<AstToken> _params,
                                    std::shared_ptr<AstToken> _function, bool _macro);
        ~AstTokenFunction();
};

class AstTokenAtom : public AstToken {
    public:
        const static tokenType ctype = ATOM;
        std::shared_ptr<AstToken> object;
        AstTokenAtom(std::shared_ptr<AstToken> _object);
        AstTokenAtom();
};

class AstTokenException : public AstToken {
    public:
        std::shared_ptr<AstToken> ast;
        const static tokenType ctype = EXCEPTION;
        AstTokenException(std::shared_ptr<AstToken> _ast);
};

class AstTokenHashMap : public AstToken {
    public:
        const static tokenType ctype = HASH_MAP;
        std::unordered_map<std::string, std::shared_ptr<AstToken>> map;
        AstTokenHashMap();
        AstTokenHashMap(MalArgs init, MalArgs end);
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

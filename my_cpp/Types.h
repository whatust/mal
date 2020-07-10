#ifndef TYPES_H_
#define TYPES_H_

#include<iostream>
#include<memory>
#include<string>
#include<vector>

#include"BasicTypes.h"
#include"Environment.h"

class AstTokenFunction : public AstToken {
    public:
        MalEnv* scope;
        std::string larg;
        std::vector<std::string> params;
        std::shared_ptr<AstToken> function;
        AstTokenFunction(MalEnv* _scope, std::shared_ptr<AstToken> _params,
                                    std::shared_ptr<AstToken> _function);
        ~AstTokenFunction();
};

class AstTokenString : public AstToken {
    public:
        std::string value;
        AstTokenString(std::string _value);
        AstTokenString(std::string _value, bool clean);
};

class AstTokenKeyword : public AstToken {
    public:
        std::string value;
        AstTokenKeyword(std::string _value);
};

class AstTokenAtom : public AstToken {
    public:
        std::shared_ptr<AstToken> object;
        AstTokenAtom(std::shared_ptr<AstToken> _object);
};

class AstTokenNil : public AstToken {
    public:
        AstTokenNil();
};

#endif  //TYPE_H_

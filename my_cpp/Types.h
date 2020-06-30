#ifndef TYPES_H_
#define TYPES_H_

#include<functional>
#include<iostream>
#include<memory>
#include<string> 
#include<vector>

class MalEnv;
typedef std::vector<std::string> StringVector;
enum tokenType { SYMBOL, NUMBER, LIST, LIST_V, LIST_H, VECTOR,
                HASH_MAP, OPERATOR, BOOL, FUNCTION, NIL, STRING, KEYWORD };

class AstToken {
    public:
        tokenType type;
        AstToken(tokenType _type);
};

typedef AstToken* AstTokenPtr;
typedef std::vector<std::shared_ptr<AstToken>>::const_iterator MalArgs;
typedef std::function<std::shared_ptr<AstToken>(MalArgs, MalArgs)> MalFunction;

class EmptyInput : public std::exception {};

class AstTokenSymbol : public AstToken {

    public:
        std::string name;
        AstTokenSymbol(std::string& _name);
};

class AstTokenOperator : public AstToken {

    public:
        MalFunction op;
        AstTokenOperator(MalFunction _op);
        std::shared_ptr<AstToken> operator()(MalArgs args, MalArgs end);
};

class AstTokenNumber : public AstToken {
    public:
        int value;
        AstTokenNumber(const std::string& _number);
        AstTokenNumber(int _number);
};

class AstTokenList : public AstToken {
    public:
        std::vector<std::shared_ptr<AstToken>> list;
        AstTokenList();
        AstTokenList(MalArgs init, MalArgs end);
};

class AstTokenVector : public AstToken {
    public:
        std::vector<std::shared_ptr<AstToken>> list;
        AstTokenVector();
};

class AstTokenHashMap : public AstToken {
    public:
        std::unordered_map<std::string, std::shared_ptr<AstToken>> map;
        AstTokenHashMap();
};

class AstTokenBool : public AstToken {
    public:
        bool value;
        AstTokenBool(const std::string& _value);
        AstTokenBool(bool _value);
};

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

class AstTokenNil : public AstToken {
    public:
        AstTokenNil();
};

#endif  //TYPE_H_

#ifndef TYPES_H_
#define TYPES_H_

#include<string>
#include<vector>
#include<memory>
#include<functional>
#include<iostream>

using std::static_pointer_cast;

typedef std::vector<std::string> StringVector;
class EmptyInput : public std::exception {};

enum tokenType { SYMBOL, NUMBER, LIST, LIST_V, LIST_H, VECTOR,
                HASH_MAP, OPERATOR, BOOL, FUNCTION, NIL };

class AstToken {
    public:
        tokenType type;
        AstToken(tokenType _type);
};

typedef AstToken* AstTokenPtr;
typedef std::vector<std::shared_ptr<AstToken>>::const_iterator MalArgs;
typedef std::function<std::shared_ptr<AstToken>(MalArgs, MalArgs)> MalFunction;

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

class AstTokenNil : public AstToken {
    public:
        AstTokenNil();
};

#endif  //TYPE_H_

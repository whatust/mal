#ifndef BASIC_TYPES_H_
#define BASIC_TYPES_H_

#include<functional>
#include<string>
#include<vector>
#include<memory>
#include<iostream>

typedef std::vector<std::string> StringVector;
enum tokenType { SYMBOL, NUMBER, LIST, VECTOR,
                HASH_MAP, OPERATOR, BOOL, FUNCTION, NIL, STRING,
                KEYWORD, ATOM, EXCEPTION };

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
        const static tokenType ctype = SYMBOL;
        std::string name;
        AstTokenSymbol(const std::string& _name);
};

class AstTokenOperator : public AstToken {
    public:
        const static tokenType ctype = OPERATOR;
        MalFunction op;
        std::string name;
        AstTokenOperator(std::string _name, MalFunction _op);
        std::shared_ptr<AstToken> operator()(MalArgs args, MalArgs end);
};

class AstTokenNumber : public AstToken {
    public:
        const static tokenType ctype = NUMBER;
        int value;
        AstTokenNumber(const std::string& _number);
        AstTokenNumber(int _number);
        AstTokenNumber();
};

class AstTokenList : public AstToken {
    public:
        const static tokenType ctype = LIST;
        std::vector<std::shared_ptr<AstToken>> list;
        AstTokenList();
        AstTokenList(MalArgs init, MalArgs end);
};

class AstTokenVector : public AstToken {
    public:
        const static tokenType ctype = VECTOR;
        std::vector<std::shared_ptr<AstToken>> list;
        AstTokenVector();
};

class AstTokenHashMap : public AstToken {
    public:
        const static tokenType ctype = HASH_MAP;
        std::unordered_map<std::string, std::shared_ptr<AstToken>> map;
        AstTokenHashMap();
};

class AstTokenBool : public AstToken {
    public:
        const static tokenType ctype = BOOL;
        bool value;
        AstTokenBool(const std::string& _value);
        AstTokenBool(bool _value);
};

#endif //BASIC_TYPES_H_

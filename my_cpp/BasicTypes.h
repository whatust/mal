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

class EmptyInput : public std::exception {};

class AstTokenSymbol : public AstToken {
    public:
        const static tokenType ctype = SYMBOL;
        std::string name;
        AstTokenSymbol(const std::string& _name);
};

class AstTokenNumber : public AstToken {
    public:
        const static tokenType ctype = NUMBER;
        int value;
        AstTokenNumber(const std::string& _number);
        AstTokenNumber(int _number);
        AstTokenNumber();
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
        AstTokenVector(MalArgs init, MalArgs end);
};

class AstTokenBool : public AstToken {
    public:
        const static tokenType ctype = BOOL;
        bool value;
        AstTokenBool(const std::string& _value);
        AstTokenBool(bool _value);
};

class AstTokenNil : public AstToken {
    public:
        const static tokenType ctype = NIL;
        AstTokenNil();
};

#endif //BASIC_TYPES_H_

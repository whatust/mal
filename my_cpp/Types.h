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

enum tokenType { SYMBOL, NUMBER, LIST, OPERATOR};

class MalToken {

    public:
        tokenType type;
        MalToken(tokenType _type);
};

typedef MalToken* MalTokenPtr;
typedef std::function<std::shared_ptr<MalToken>(std::vector<std::shared_ptr<MalToken>>::const_iterator)> MalFunction;
typedef std::unordered_map<std::string, MalFunction> MalEnv;

class MalTokenSymbol : public MalToken {

    public:
        std::string name;
        MalTokenSymbol(std::string& _name);
};

class MalTokenOperator : public MalToken {

    public:
        MalFunction op;
        MalTokenOperator(const std::string& symbol, MalEnv& repl_env);
};

class MalTokenNumber : public MalToken {
    public:
        int value;
        MalTokenNumber(const std::string& _number);
        MalTokenNumber(int _number);
};

class MalTokenList : public MalToken {
    public:
        char close_char;
        char open_char;
        std::vector<std::shared_ptr<MalToken>> list;
        MalTokenList(const char _end_char);
};

#endif  //TYPE_H_

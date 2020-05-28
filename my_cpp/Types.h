#ifndef TYPES_H_
#define TYPES_H_

#include<string>
#include<vector>
#include<memory>

using std::static_pointer_cast;

typedef std::vector<std::string> StringVector;
class EmptyInput : public std::exception {};

enum tokenType { SYMBOL, NUMBER, LIST };

class MalToken {

    public:
        tokenType type;
        MalToken(tokenType _type);
};

class MalTokenSymbol : public MalToken {

    public:
        std::string name;
        MalTokenSymbol(std::string& _name);
};

class MalTokenNumber : public MalToken {
    public:
        int value;
        MalTokenNumber(const std::string& _number);
};

class MalTokenList : public MalToken {
    public:
        char close_char;
        char open_char;
        std::vector<std::shared_ptr<MalToken>> list;
        MalTokenList(const char _end_char);
};

typedef MalToken* MalTokenPtr;

#endif  //TYPE_H_

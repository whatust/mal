#ifndef TYPES_H_
#define TYPES_H_

#include<string>
#include<vector>
#include<memory>

using std::string;
using std::vector;
using std::shared_ptr;
using std::static_pointer_cast;

typedef vector<string> StringVector;

enum tokenType { SYMBOL, NUMBER, LIST };

class MalToken {

    public:
    tokenType type;
    MalToken(tokenType _type);
};

class MalTokenSymbol : public MalToken {

    public:
    string name;
    MalTokenSymbol(string& _name);
};

class MalTokenNumber : public MalToken {
    public:
    int value;
    MalTokenNumber(const string& _number);
};

class MalTokenList : public MalToken {
    public:
    vector<shared_ptr<MalToken>> list;
    MalTokenList();
};

typedef MalToken* MalTokenPtr;

#endif  //TYPE_H_

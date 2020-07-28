#include"BasicTypes.h"

AstToken::AstToken(tokenType _type) : type(_type){};

AstTokenSymbol::AstTokenSymbol(const std::string& _name)
: AstToken(SYMBOL)
, name(_name){
    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);
};

AstTokenNumber::AstTokenNumber(const std::string& _number)
: AstToken(NUMBER)
, value(stoi(_number)){
    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);
};

AstTokenNumber::AstTokenNumber(int _number)
: AstToken(NUMBER)
, value(_number){
    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);
};

AstTokenNumber::AstTokenNumber()
: AstToken(NUMBER) {
    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);
};

AstTokenString::AstTokenString(std::string _value)
: AstToken(STRING)
, value(_value) {
    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);
};

AstTokenString::AstTokenString(std::string _value, bool clean)
: AstToken(STRING) {

    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);

    for(int i=1; i < (int) _value.length()-1; i++) {
        if(_value[i] != '\\') {
            value.push_back(_value[i]);
        } else {
            i++;
            if(i < (int) _value.length()) {
                switch (_value[i]) {

                    case 'n':
                        value.push_back('\n');
                        break;
                    case '"':
                        value.push_back('"');
                        break;
                    case '\\':
                        value.push_back('\\');
                        break;
                    default:
                        value.push_back('\\');
                        value.push_back(_value[i]);
                }
            }
        }
    }
};

AstTokenKeyword::AstTokenKeyword(std::string _value)
: AstToken(KEYWORD) {
    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);
    value = _value.replace(0, 1, "\xff");
};

AstTokenList::AstTokenList()
: AstToken(LIST) {
    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);
};

AstTokenList::AstTokenList(MalArgs init, MalArgs end)
: AstToken(LIST) {

    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);

    while(init != end) {
        list.push_back(*init);
        init++;
    }
};

AstTokenVector::AstTokenVector()
: AstToken(VECTOR) {
    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);
};

AstTokenVector::AstTokenVector(MalArgs init, MalArgs end)
: AstToken(VECTOR) {

    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);

    while(init != end) {
        list.push_back(*init);
        init++;
    }
};

AstTokenBool::AstTokenBool(const std::string& _value)
: AstToken(BOOL) {

    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);

    value = _value == "true" ? true : false;
};

AstTokenBool::AstTokenBool(bool _value)
: AstToken(BOOL)
, value(_value) {
    AstToken::meta = std::shared_ptr<AstTokenNil>(new AstTokenNil);
};

AstTokenNil::AstTokenNil()
: AstToken(NIL) {};


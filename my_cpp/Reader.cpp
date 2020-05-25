#include<assert.h>

#include"Reader.h"

using std::regex;
using std::smatch;
using std::regex_constants::match_continuous;
using std::begin;
using std::end;
using std::cout;
using std::cerr;
using std::endl;

static const regex WHITESPACES_REGEX("[\\s,]*");
static const regex TOKEN_REGEX[] = {
    regex("~@"),
    regex("[\\[\\]{}()'`~^@]"),
    regex("\"(?:\\\\.|[^\\\\\"])*\""),
    regex("[^\\s\\[\\]{}('\"`,;)]+")};

Reader::Reader(vector<string>&& _tokens)
    : tokens(move(_tokens)),
    s_iter(begin(tokens)),
    s_end(end(tokens)){}

Reader::~Reader(){}

string Reader::peek() {
    assert(!is_eof());
    return *s_iter;
}

string Reader::next() {

    assert(!is_eof());
    string token = peek();
    next_token();

    return token;
}

bool Reader::is_eof() const {
    return s_iter == s_end;
}

void Reader::next_token() {
    s_iter++;
    return;
}

vector<string> tokenize(const string& input) {

    vector<string> tokens;

    for(auto iter = begin(input); iter != end(input);) {

        smatch match;
        auto flag = match_continuous;

        if(regex_search(iter, end(input), match, WHITESPACES_REGEX, flag)) {

            if(match.position(0) == 0 && match.length(0) > 0) {
                iter += match.length(0);
            }
        }

        bool match_found = false;
        for(auto &regex : TOKEN_REGEX) {

            smatch match;
            auto flag = match_continuous;

            if(!regex_search(iter, end(input), match, regex, flag)) continue;
            if(match.position(0) != 0) continue;
            if(match.length(0) < 1) continue;

            tokens.push_back(match.str());
            iter += match.length(0);
            match_found = true;
        }

        if(!match_found)
            cerr << "no match for string\"" << *iter << "\""<< endl;
    }
    return tokens;
}

shared_ptr<MalToken> read_str(const string &input) {

    Reader reader(tokenize(input));
    MalTokenPtr ret;

    if(!reader.empty())
        ret = read_form(reader);
    else
        ret = nullptr;

    shared_ptr<MalToken> ast(ret);

    return ast;
}

MalTokenPtr read_form(Reader& reader) {

    MalTokenPtr ast;

    if(reader.peek()[0] == '(') {
        reader.next();
        ast = read_list(reader);
    }else{
        ast = read_atom(reader);
    }

    return ast;
}

MalTokenPtr read_list(Reader& reader) {

    MalTokenList* ast = new MalTokenList;

    while(reader.peek()[0] != ')')
        ast->list.push_back(shared_ptr<MalToken>(read_form(reader)));
    reader.next();

    return ast;
}

MalTokenPtr read_atom(Reader& reader) {

    string token = reader.next();
    return new MalTokenSymbol(token);
}

void Reader::print_tokens() const {
    for(auto token : tokens)
        cout << token << endl;
    return;
}

bool Reader::empty() const {
    return tokens.empty();
}

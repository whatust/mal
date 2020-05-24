#ifndef READER_H_
#define READER_H_

#include<regex>
#include<vector>
#include<string>
#include<iostream>

#include"Types.h"

using std::string;
using std::vector;

class Reader {

    public:
        string next();
        string peek();
        Reader(vector<string>&& tokens);
        ~Reader();
        void print_tokens() const;

    private:
        vector<string> tokens;
        vector<string>::iterator s_iter;
        vector<string>::iterator s_end;

        void next_token();
        bool is_eof() const;
};

shared_ptr<MalToken> read_str(const string& input);
MalTokenPtr read_form(Reader& reder);       // calls read_list or read_atom
MalTokenPtr read_list(Reader& reader);      // calls red_form
MalTokenPtr read_atom(Reader& reader);      // calls Reader.next
StringVector tokenize(const string& input); // separates input string vector

#endif  // READER_H_

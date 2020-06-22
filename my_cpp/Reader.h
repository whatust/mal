#ifndef READER_H_
#define READER_H_

#include<regex>
#include<vector>
#include<string>
#include<iostream>

#include"Types.h"
#include"Validation.h"

using std::string;
using std::vector;

class Reader {

    public:
        string next();
        string peek();
        Reader(StringVector&& tokens);
        ~Reader();
        void print_tokens() const;
        bool empty() const;
        bool is_eof() const;

    private:
        vector<string> tokens;
        vector<string>::iterator s_iter;
        vector<string>::iterator s_end;

        void next_token();
};

std::shared_ptr<AstToken> read_str(const std::string& input);
AstTokenPtr read_form(Reader& reder);                 // calls read_list or read_atom
AstTokenPtr read_list(Reader& reader, char end_char); // calls red_form
AstTokenPtr read_atom(Reader& reader);                // calls Reader.next
StringVector tokenize(const std::string& input);      // separates input string vector

#endif  // READER_H_

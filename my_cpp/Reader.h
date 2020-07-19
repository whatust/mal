#ifndef READER_H_
#define READER_H_

#include<iostream>
#include<regex>
#include<string>
#include<vector>

#include"Types.h"
#include"Validation.h"

class Reader {

    public:
        std::string next();
        std::string peek();
        Reader(StringVector&& tokens);
        ~Reader();
        void print_tokens() const;
        bool empty() const;
        bool is_eof() const;

    private:
        std::vector<std::string> tokens;
        std::vector<std::string>::iterator s_iter;
        std::vector<std::string>::iterator s_end;

        void next_token();
};

std::shared_ptr<AstToken> read_str(const std::string& input);
AstTokenPtr read_form(Reader& reder);                 // calls read_list or read_atom
AstTokenPtr read_list(Reader& reader, char end_char); // calls red_form
AstTokenPtr read_atom(Reader& reader);                // calls Reader.next
StringVector tokenize(const std::string& input);      // separates input string vector

#endif  // READER_H_

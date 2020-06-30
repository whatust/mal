#include"Reader.h"

using std::regex_constants::match_continuous;

static const std::regex WHITESPACES_REGEX("[\\s,]+");
static const std::regex NUMBER_REGEX("^[-+]?[0-9]+");
static const std::regex TOKEN_REGEX[] = {
    std::regex("~@"),                        // Special two characters
    std::regex("[\\[\\]{}()'`~^@]"),         // Special single characters
    std::regex("\"(?:\\\\.|[^\\\\\"])*\""),  // Balanced strings
    std::regex("[^\\s\\[\\]{}('\"`,;)]+"),   // Symbols numbers constants
    std::regex(";.*")                        // Comments
};

Reader::Reader(StringVector&& _tokens)
    : tokens(move(_tokens)),
    s_iter(std::begin(tokens)),
    s_end(std::end(tokens)){}

Reader::~Reader(){}

std::string Reader::peek() {
    return *s_iter;
}

std::string Reader::next() {

    std::string token = peek();
    next_token();

    return token;
}

void Reader::next_token() {
    s_iter++;
    return;
}

bool Reader::is_eof() const{
    return s_iter == s_end;
}

StringVector tokenize(const std::string& input) {

    StringVector tokens;

    for(auto iter = std::begin(input); iter != std::end(input);) {

        std::smatch match;
        auto flag = match_continuous;

        // Remove whitespaces
        if(std::regex_search(iter, std::end(input), match, WHITESPACES_REGEX, flag)) {
            if(match.position(0) == 0 && match.length(0) > 0) {
                iter += match.length(0);
            }
        }

        if(iter == std::end(input)) // Check end of line with whitespaces
            continue;

        bool match_found = false;
        for(auto &regex : TOKEN_REGEX) {

            std::smatch match;
            auto flag = match_continuous;

            if(!std::regex_search(iter, std::end(input), match, regex, flag)) continue;
            if(match.position(0) != 0) continue;
            if(match.length(0) < 1) continue;

            tokens.push_back(match.str());
            iter += match.length(0);
            match_found = true;
        }

        // Check
        check_list_balance(!match_found, "\"", "EOF");
    }
    return tokens;
}

std::shared_ptr<AstToken> read_str(const std::string &input) {

    Reader reader(tokenize(input));
    //reader.print_tokens();
    AstTokenPtr ret;

    if(!reader.empty()){
        ret = read_form(reader);
    }else{
        throw EmptyInput();
    }

    std::shared_ptr<AstToken> ast(ret);

    return ast;
}

AstTokenPtr read_form(Reader& reader) {

    AstTokenPtr ast;

    switch(reader.peek()[0]) {
        case '(':
        case '[':
        case '{':
            ast = read_list(reader, reader.peek()[0]);
            break;
        default:
            ast = read_atom(reader);
    }
    return ast;
}

AstTokenPtr read_list(Reader& reader, char open_char) {

    std::string end_str;
    AstTokenList* ast = new AstTokenList();

    if (open_char == '(') {
        end_str = ")";
        ast->type = LIST;
    } else if (open_char == '[') {
        end_str = "]";
        ast->type = LIST_V;
    } else {
        end_str = "}";
        ast->type = LIST_H;
    }

    reader.next();
    check_list_balance(reader.is_eof(), end_str, "EOF");

    while(reader.peek() != end_str) {
        ast->list.push_back(std::shared_ptr<AstToken>(read_form(reader)));
        check_list_balance(reader.is_eof(), end_str, "EOF");
    }
    reader.next();

    return ast;
}

AstTokenPtr read_quote(std::string token, Reader& reader) {

    AstTokenList* ast = new AstTokenList();
    ast->list.push_back(std::shared_ptr<AstToken>(new AstTokenSymbol(token)));
    check_valid_expression(reader.is_eof(), "expression", "EOF");
    ast->list.push_back(std::shared_ptr<AstToken>(read_form(reader)));

    return ast;
}

AstTokenPtr read_meta(std::string token, Reader& reader) {

    AstTokenPtr aux;
    AstTokenList* ast = new AstTokenList();

    ast->list.push_back(std::shared_ptr<AstToken>(new AstTokenSymbol(token)));

    check_valid_expression(reader.is_eof(), "expression", "EOF");
    aux = read_form(reader);

    check_valid_expression(reader.is_eof(), "expression", "EOF");
    ast->list.push_back(std::shared_ptr<AstToken>(read_form(reader)));

    ast->list.push_back(std::shared_ptr<AstToken>(aux));

    return ast;
}

AstTokenPtr read_atom(Reader& reader) {

    AstTokenPtr ast;
    std::string token = reader.next();

    switch (token[0]) {
        case '`':
            ast = read_quote("quasiquote", reader);
            break;
        case '\'':
            ast = read_quote("quote", reader);
            break;
        case '~':
            if (token.size() == 1)
                ast = read_quote("unquote", reader);
            else
                ast = read_quote("splice-unquote", reader);
            break;
        case '^':
            ast = read_meta("with-meta", reader);
            break;
        case '@':
            ast = read_quote("deref", reader);
            break;
        case '"':
            ast = new AstTokenString(token, true);
            break;
        default:

            std::smatch match;
            auto flag = match_continuous;

            if (regex_search(token, match, NUMBER_REGEX, flag)) {
                ast = new AstTokenNumber(token);
            } else if (token == "true") {
                ast = new AstTokenBool(true);
            } else if (token == "false") {
                ast = new AstTokenBool(false);
            } else if (token == "nil") {
                ast = new AstTokenNil();
            } else {
                ast = new AstTokenSymbol(token);
            }
    }
    return ast;
}

void Reader::print_tokens() const {
    for(auto token : tokens)
        std::cout << token << std::endl;
    return;
}

bool Reader::empty() const {
    return tokens.empty();
}


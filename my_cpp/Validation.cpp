#include"Validation.h"

const char *token_to_str[] = { "SYMBOL", "NUMBER", "LIST",
                                "VECTOR", "HASH_MAP", "OPERATOR",
                                "BOOL", "FUNCTION", "NIL", "STRING",
                                "KEYWORD", "ATOM" };

const char*
TokenException::what() const noexcept {

    const char* _error = "Error: Invalid token got %s, expected: %s";

    char* error = (char*)malloc(strlen(_error) + strlen(token_to_str[got]) +
                                        strlen(token_to_str[expected] + 1));
    sprintf(error, _error, token_to_str[got], token_to_str[expected]);

    return error;
}

const char*
ArgumentException::what() const noexcept {

    const char* _error = "Error: Wrong number of arguments got %i arguments expected: %i";

    char* error = (char*)malloc(strlen(_error) + 11 + 11 + 1);
    sprintf(error, _error, got, expected);

    return error;
}

const char*
MapException::what() const noexcept {

    const char* error = "Error: Hashmap needs even number of arguments (key:value)";

    return error;
}

const char*
SymException::what() const noexcept {

    const char* _error = "Error: Symbol %s not found";

    char* error = (char*)malloc(strlen(_error) + symbol.length() + 1);
    sprintf(error, _error, symbol.c_str());

    return error;
}

const char*
BalException::what() const noexcept {

    const char* _error = "Error: Expected %s got EOF";

    char* error = (char*)malloc(strlen(_error) + expected.length() + 1);
    sprintf(error, _error, expected.c_str());

    return error;
}

void arg_assert(bool expr, ArgumentException e){
    if(expr) return;
    throw e;
}

void map_assert(bool expr, MapException e){
    if(expr) return;
    throw e;
}

void sym_assert(bool expr, SymException e){
    if(expr) return;
    throw e;
}

void bal_assert(bool expr, BalException e) {
    if(expr) return;
    throw e;
}

void unimplemented_comparison(const tokenType& token_a, const tokenType& token_b) {

    std::string error = "Error: Unimplemented comparison between %s and %s";
    std::string str_a(token_to_str[token_a]);
    std::string str_b(token_to_str[token_b]);

    char* aux_message = new char[error.length() + str_a.length() + str_b.length() + 1];

    sprintf(aux_message, error.c_str(), str_a.c_str(), str_b.c_str());
    std::string error_message(std::move(aux_message));

    throw error_message;
}


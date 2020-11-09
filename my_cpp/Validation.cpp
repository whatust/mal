#include"Validation.h"

const char *token_to_str[] = { "SYMBOL", "NUMBER", "LIST",
                                "VECTOR", "HASH_MAP", "OPERATOR",
                                "BOOL", "FUNCTION", "NIL", "STRING",
                                "KEYWORD", "ATOM", "EXCEPTION" };

const char*
TokenException::what() const noexcept {

    const char* _error = "Error: Invalid token got %s, expected: %s";

    char* error = (char*)malloc(strlen(_error) + strlen(token_to_str[got]) +
                                        strlen(token_to_str[expected] + 1));

    if(error)
        sprintf(error, _error, token_to_str[got], token_to_str[expected]);

return error;
}

const char*
ArgumentException::what() const noexcept {

    const char* _error = "Error: Wrong number of arguments got %i arguments expected: %i";

    char* error = (char*)malloc(strlen(_error) + 11 + 11 + 1);

    if(error)
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

    const char* _error = "'%s' not found";

    char* error = (char*)malloc(strlen(_error) + symbol.length() + 1);

    if(error)
        sprintf(error, _error, symbol.c_str());

    return error;
}

const char*
BalException::what() const noexcept {

    const char* _error = "Error: Expected %s got EOF";

    char* error = (char*)malloc(strlen(_error) + expected.length() + 1);

    if(error)
        sprintf(error, _error, expected.c_str());

    return error;
}

const char*
UncException::what() const noexcept {

    const char* _error = "Error: Unimplemented comparison between %s and %s";

    char* error = (char*)malloc(strlen(_error) + strlen(token_to_str[a]) +
                                            strlen(token_to_str[b]) + 1);

    if(error)
        sprintf(error, _error, token_to_str[a], token_to_str[b]);

    return error;
};

const char*
MacroException::what() const noexcept {

    const char* _error = "Error: Macro erro expected type FUNCTION got %s";

    char* error = (char*)malloc(strlen(_error) + strlen(token_to_str[expected]) + 1);

    if(error)
        sprintf(error, _error, token_to_str[expected]);

    return error;
};

const char*
OutRangeException::what() const noexcept {

    const char* _error = "Error: Out of range index %i out of range (list size %i)";

    char* error = (char*)malloc(strlen(_error) + 11 + 11 + 1);

    if(error)
        sprintf(error, _error, index, size);

    return error;
}

const char*
TryException::what() const noexcept {

    const char* error = "Error: Try expression has to follow format (try* A (catch* B C))";

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


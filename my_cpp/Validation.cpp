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

void assert_args(bool expr, ArgumentException e){

    if(expr) {
        return;
    }

    throw e;
}

void check_list_balance(bool condition, const std::string& expected, const std::string& got) {

    if (condition) {
        std::string error = "Error: Expected %s got: %s";
        char* aux_message = new char[error.length() + expected.length() + got.length() + 1];

        sprintf(aux_message, error.c_str(), expected.c_str(), got.c_str());
        std::string error_message(std::move(aux_message));
        throw error_message;
    }
    return;
}

void check_valid_expression(bool condition, const std::string& expected, const std::string& got) {

    if (condition) {

        std::string error = "Error: Expected %s got: %s";
        char* aux_message = new char[error.length() + expected.length() + got.length() + 1];

        sprintf(aux_message, error.c_str(), expected.c_str(), got.c_str());
        std::string error_message(std::move(aux_message));
        throw error_message;
    }
    return;
}

void check_valid_symbol(bool condition, const std::string& error, const std::string &symbol) {

    char* aux_message = new char[error.length() + symbol.length() + 1];

    if (condition)  {
        sprintf( aux_message, error.c_str(), symbol.c_str());
        std::string error_message(std::move(aux_message));
        throw error_message;
    }
    delete[] aux_message;
    return;
}

void check_token(bool condition, const tokenType& token_expected, const tokenType& token_got) {

    if (condition) {

        std::string error = "Error: Expected Token type: %s got: %s";
        std::string str_expected(token_to_str[token_expected]);
        std::string str_got(token_to_str[token_got]);

        char* aux_message = new char[error.length() + str_expected.length() + str_got.length() + 1];

        sprintf(aux_message, error.c_str(), str_expected.c_str(), str_got.c_str());
        std::string error_message(std::move(aux_message));
        throw error_message;
    }
    return;
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

void check_arguments(bool condition, const std::string& expected, const std::string& got) {

    if (condition) {

        std::string error = "Error: Insuficient number of arguments expected %s arguments got: %s";
        char* aux_message = new char[error.length() + expected.length() + got.length() + 1];

        sprintf(aux_message, error.c_str(), expected.c_str(), got.c_str());
        std::string error_message(std::move(aux_message));
        throw error_message;
    }
    return;
}

void check_map(bool condition) {

    std::string error_message("Invalid number of parameters entry on hash map");

    if (condition) {

        throw error_message;
    }
    return;
}


#include"Validation.h"

void check_list_balance(bool condition, const std::string& error, char expected, const std::string& got) {
    char* aux_message = new char[error.length() + got.length() + 2];

    if (condition) {
        sprintf(aux_message, error.c_str(), expected, got.c_str());
        std::string error_message(std::move(aux_message));
        throw error_message;
    }
    delete[] aux_message;
    return;
}

void check_valid_expression(bool condition, const std::string& error, const std::string& got) {

    char* aux_message = new char[error.length() + got.length() + 1];

    if (condition) {
        sprintf(aux_message, error.c_str(), got.c_str());
        std::string error_message(std::move(aux_message));
        throw error_message;
    }
    delete[] aux_message;
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

void check_token(bool condition, const std::string& error, tokenType& token) {

    const char *token_type[] = { "SYMBOL", "NUMBER", "LIST", "VECTOR", "HASH_MAP", "OPERATOR"};
    std::string str_token_type(token_type[token]);

    char* aux_message = new char[error.length() + str_token_type.length() + 1];

    if (condition) {
        sprintf( aux_message, error.c_str(), str_token_type.c_str());
        std::string error_message(std::move(aux_message));
        throw error_message;
    }
    delete[] aux_message;
    return;
}

void check_arguments(bool condition, const std::string& error) {

    if (condition) {
        throw error;
    }
    return;
}

void check_map(bool condition, const std::string& error) {

    if (condition) {
        throw error;
    }
    return;
}


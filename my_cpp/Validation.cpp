#include"Validation.h"

const char *token_type_str[] = { "SYMBOL", "NUMBER", "LIST", "LIST_V",
                                    "LIST_H", "VECTOR", "HASH_MAP", "OPERATOR",
                                    "BOOL", "FUNCTION", "NIL", "STRING", "KEYWORD"};

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
        std::string str_expected(token_type_str[token_expected]);
        std::string str_got(token_type_str[token_got]);

        char* aux_message = new char[error.length() + str_expected.length() + str_got.length() + 1];

        sprintf(aux_message, error.c_str(), str_expected.c_str(), str_got.c_str());
        std::string error_message(std::move(aux_message));
        throw error_message;
    }
    return;
}

void unimplemented_comparison(const tokenType& token_a, const tokenType& token_b) {

    std::string error = "Error: Unimplemented comparison between %s and %s";
    std::string str_a(token_type_str[token_a]);
    std::string str_b(token_type_str[token_b]);

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


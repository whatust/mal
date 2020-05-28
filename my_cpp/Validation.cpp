#include"Validation.h"

void check_list_balance(bool condition, const std::string& error, char expected, const std::string& got) {

    char* aux_message = new char[error.length() + got.length() + 2];

    if (condition) {
        sprintf(aux_message, error.c_str(), expected, got.c_str());
        std::string error_message(aux_message);
        throw error_message;
    }
    return;
}

void check_valid_expression(bool condition, const std::string& error, const std::string& got) {

    char* aux_message = new char[error.length() + got.length() + 1];

    if (condition) {
        sprintf(aux_message, error.c_str(), got.c_str());
        std::string error_message(aux_message);
        throw error_message;
    }
    return;
}


#ifndef VALIDATION_H_
#define VALIDATION_H_

#include<iostream>
#include<stdio.h>
#include<string.h>

#include"BasicTypes.h"

class TokenException : public std::exception {
    private:
        tokenType expected;
        tokenType got;

    public:
        TokenException(tokenType _expected, tokenType _got)
            : expected(_expected), got(_got) {};
        const char* what() const noexcept;
};

class ArgumentException : public std::exception {
    private:
        int expected;
        int got;

    public:
        ArgumentException(int _expected, int _got)
            : expected(_expected), got(_got) {};
        const char* what() const noexcept;
};

void assert_args(bool expr, ArgumentException e);

void check_list_balance(bool condition, const std::string& expected, const std::string& got);
void check_valid_expression(bool condition, const std::string& error, const std::string& got);
void check_valid_symbol(bool condition, const std::string& error, const std::string &symbol);
void check_token(bool condition, const tokenType& token_expected, const tokenType& token_got);
void unimplemented_comparison(const tokenType& token_a, const tokenType& token_b);
void check_arguments(bool condition, const std::string& expected, const std::string& got);
void check_map(bool condition);

#endif //VALIDATION_H_

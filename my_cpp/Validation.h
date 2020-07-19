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

class MapException : public std::exception {
    private:
    public:
        const char* what() const noexcept;
};

class SymException : public std::exception {
    private:
        std::string symbol;
    public:
        const char* what() const noexcept;
        SymException(std::string _symbol) : symbol(_symbol) {};
};

class BalException : public std::exception {
    private:
        std::string expected;
    public:
        const char* what() const noexcept;
        BalException(std::string _expected) : expected(_expected) {};
};

void arg_assert(bool expr, ArgumentException e);
void map_assert(bool expr, MapException e);
void sym_assert(bool expr, SymException e);
void bal_assert(bool expr, BalException e);

void unimplemented_comparison(const tokenType& token_a, const tokenType& token_b);

#endif //VALIDATION_H_

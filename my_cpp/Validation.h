#ifndef VALIDATION_H_
#define VALIDATION_H_

#include<iostream>
#include<stdio.h>
#include<string>

#include"BasicTypes.h"

void check_list_balance(bool condition, const std::string& expected, const std::string& got);
void check_valid_expression(bool condition, const std::string& error, const std::string& got);
void check_valid_symbol(bool condition, const std::string& error, const std::string &symbol);
void check_token(bool condition, const tokenType& token_expected, const tokenType& token_got);
void unimplemented_comparison(const tokenType& token_a, const tokenType& token_b);
void check_arguments(bool condition, const std::string& expected, const std::string& got);
void check_map(bool condition);

#endif //VALIDATION_H_

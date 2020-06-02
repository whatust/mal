#ifndef VALIDATION_H_
#define VALIDATION_H_

#include<iostream>
#include<stdio.h>
#include<string>

#include"Types.h"

void check_list_balance(bool condition, const std::string& error, char expected, const std::string& got);
void check_valid_expression(bool condition, const std::string& error, const std::string& got);
void check_valid_symbol(bool condition, const std::string& error, const std::string &symbol);
void check_token(bool condition, const std::string& error, tokenType& token);

#endif //VALIDATION_H_

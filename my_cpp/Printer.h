#ifndef PRINTER_H_
#define PRINTER_H_

#include<algorithm>
#include<iostream>

#include"Types.h"

std::string pr_str(std::shared_ptr<AstToken> ast, bool print_readably);

#endif  // PRINTER_H_

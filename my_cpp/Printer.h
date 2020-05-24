#ifndef PRINTER_H_
#define PRINTER_H_

#include<iostream>

#include"Types.h"

using std::cout;
using std::endl;

string pr_str(shared_ptr<MalToken> ast);

#endif  // PRINTER_H_

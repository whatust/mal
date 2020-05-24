#include"Printer.h"

string pr_str(shared_ptr<MalToken> ast){

    string ret;

    switch(ast->type) {

        case SYMBOL: {
            shared_ptr<MalTokenSymbol> symbol_ast;
            symbol_ast = static_pointer_cast<MalTokenSymbol>(ast);
            ret = symbol_ast->name;
            break;
        }

        case NUMBER: {
            shared_ptr<MalTokenNumber> number_ast;
            number_ast = static_pointer_cast<MalTokenNumber>(ast);
            ret = number_ast->value;
            break;
        }

        case LIST: {
            shared_ptr<MalTokenList> list_ast;
            list_ast = static_pointer_cast<MalTokenList>(ast);

            ret = "(";
            for(auto token : list_ast->list)
                ret += pr_str(token);
            ret += ")";
            break;
       }
    }
    return ret;
}

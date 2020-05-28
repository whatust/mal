#include"Printer.h"

std::string pr_str(std::shared_ptr<MalToken> ast){

    std::string ret = "";

    if(ast != nullptr) {
        switch(ast->type) {

            case SYMBOL: {
                std::shared_ptr<MalTokenSymbol> symbol_ast;
                symbol_ast = static_pointer_cast<MalTokenSymbol>(ast);
                ret = symbol_ast->name;
                break;
            }

            case NUMBER: {
                std::shared_ptr<MalTokenNumber> number_ast;
                number_ast = static_pointer_cast<MalTokenNumber>(ast);
                ret = number_ast->value;
                break;
            }

            case LIST: {
                std::shared_ptr<MalTokenList> list_ast;
                list_ast = static_pointer_cast<MalTokenList>(ast);

                ret = list_ast->open_char;
                for(auto token : list_ast->list)
                    ret += pr_str(token) + " ";

                // Erase space after the last element of the list
                auto index = std::find(std::rbegin(ret), std::rend(ret), ' ');
                if(index != std::rend(ret)) {
                    // conversion between reverse iterator and iterator needs to
                    // account for rbegin to become end and rend become begin
                    ret.erase(--index.base());
                }
                ret += list_ast->close_char;
                break;
           }
        }
    }
    return ret;
}


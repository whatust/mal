#include"Printer.h"

template<class T>
void pr_list(std::string& ret, std::shared_ptr<T> ast) {

    for(auto token : ast->list)
        ret += pr_str(token) + " ";

    // Erase space after the last element of the list
    auto index = std::find(std::rbegin(ret), std::rend(ret), ' ');
    if(index != std::rend(ret)) {
        // conversion between reverse iterator and iterator needs to
        // account for rbegin to become end and rend become begin
        ret.erase(--index.base());
    }
    return;
}

template<class T>
void pr_hash(std::string& ret, std::shared_ptr<T> ast) {

    for(auto it : ast->map) {
        ret += it.first + " ";
        ret += pr_str(it.second) + " ";
    }

    // Erase space after the last element of the list
    auto index = std::find(std::rbegin(ret), std::rend(ret), ' ');
    if(index != std::rend(ret)) {
        // conversion between reverse iterator and iterator needs to
        // account for rbegin to become end and rend become begin
        ret.erase(--index.base());
    }
    return;
}

std::string pr_str(std::shared_ptr<AstToken> ast){

    std::string ret = "";

    if(ast != nullptr) {
        switch(ast->type) {

            case SYMBOL: {
                std::shared_ptr<AstTokenSymbol> symbol_ast;
                symbol_ast = static_pointer_cast<AstTokenSymbol>(ast);
                ret = symbol_ast->name;
                break;
            }

            case NUMBER: {
                std::shared_ptr<AstTokenNumber> number_ast;
                number_ast = static_pointer_cast<AstTokenNumber>(ast);
                ret = std::to_string(number_ast->value);
                break;
            }

            case LIST_H:
            case LIST: {
                std::shared_ptr<AstTokenList> list_ast;
                list_ast = static_pointer_cast<AstTokenList>(ast);

                ret = ast->type == LIST ? "(" : "{";
                pr_list(ret, list_ast);
                ret += ast->type == LIST ? ")" : "}";

                break;
            }
            case LIST_V:
            case VECTOR: {
                std::shared_ptr<AstTokenVector> vect_ast;
                vect_ast = static_pointer_cast<AstTokenVector>(ast);

                ret = "[";
                pr_list(ret, vect_ast);
                ret += "]";

                break;
           }
           case HASH_MAP: {
                std::shared_ptr<AstTokenHashMap> hash_ast;
                hash_ast = static_pointer_cast<AstTokenHashMap>(ast);

                ret = "{";
                pr_hash(ret, hash_ast);
                ret += "}";

                break;
           }
           case OPERATOR: {
                throw "Unexpected Operator";
            }
        }
    }
    return ret;
}


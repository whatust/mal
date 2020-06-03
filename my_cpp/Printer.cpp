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

    for(size_t i=0; i < ast->key.size(); i++) {
        ret += pr_str(ast->key[i]) + " ";
        ret += pr_str(ast->value[i]) + " ";
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
                ret = std::to_string(number_ast->value);
                break;
            }

            case LIST: {
                std::shared_ptr<MalTokenList> list_ast;
                list_ast = static_pointer_cast<MalTokenList>(ast);

                ret = "(";
                pr_list(ret, list_ast);
                ret += ")";

                break;
            }
            case VECTOR: {
                std::shared_ptr<MalTokenVector> vect_ast;
                vect_ast = static_pointer_cast<MalTokenVector>(ast);

                ret = "[";
                pr_list(ret, vect_ast);
                ret += "]";

                break;
           }
           case HASH_MAP: {
                std::shared_ptr<MalTokenHashMap> hash_ast;
                hash_ast = static_pointer_cast<MalTokenHashMap>(ast);

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


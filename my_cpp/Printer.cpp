#include"Printer.h"

template<class T>
void pr_list(std::string& ret, std::shared_ptr<T> ast, bool print_readably) {

    for(auto token : ast->list)
        ret += pr_str(token, print_readably) + " ";

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
void pr_hash(std::string& ret, std::shared_ptr<T> ast, bool print_readably) {

    for(auto it : ast->map) {
        if(it.first[0] == '\xff') {
            ret += ":" + it.first.substr(1, it.first.length()-1) + " ";
        } else {
            ret += "\"" + it.first + "\" ";
        }
        ret += pr_str(it.second, print_readably) + " ";
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

std::string pr_str(std::shared_ptr<AstToken> ast, bool print_readably){

    std::string ret = "";

    if(ast != nullptr) {
        switch(ast->type) {

            case SYMBOL: {
                std::shared_ptr<AstTokenSymbol> symbol_ast;
                symbol_ast = std::static_pointer_cast<AstTokenSymbol>(ast);
                ret = symbol_ast->name;
                break;
            }

            case NUMBER: {
                std::shared_ptr<AstTokenNumber> number_ast;
                number_ast = std::static_pointer_cast<AstTokenNumber>(ast);
                ret = std::to_string(number_ast->value);
                break;
            }

            case LIST_H:
            case LIST: {
                std::shared_ptr<AstTokenList> list_ast;
                list_ast = std::static_pointer_cast<AstTokenList>(ast);

                ret = ast->type == LIST ? "(" : "{";
                pr_list(ret, list_ast, print_readably);
                ret += ast->type == LIST ? ")" : "}";

                break;
            }
            case LIST_V:
            case VECTOR: {
                std::shared_ptr<AstTokenVector> vect_ast;
                vect_ast = std::static_pointer_cast<AstTokenVector>(ast);

                ret = "[";
                pr_list(ret, vect_ast, print_readably);
                ret += "]";

                break;
           }
           case HASH_MAP: {
                std::shared_ptr<AstTokenHashMap> hash_ast;
                hash_ast = std::static_pointer_cast<AstTokenHashMap>(ast);

                ret = "{";
                pr_hash(ret, hash_ast, print_readably);
                ret += "}";

                break;
           }
           case BOOL: {
                std::shared_ptr<AstTokenBool> bool_ast;
                bool_ast = std::static_pointer_cast<AstTokenBool>(ast);
                ret = bool_ast->value ? "true" : "false";

                break;
           }
           case STRING: {

                std::shared_ptr<AstTokenString> str_ast;
                str_ast = std::static_pointer_cast<AstTokenString>(ast);
                std::string readably_str;

                if(print_readably){
                    for(int i=0; i < (int) str_ast->value.size(); i++) {
                        switch (str_ast->value[i]) {
                            case '\\':
                                readably_str.push_back('\\');
                                readably_str.push_back('\\');
                                break;
                            case '"':
                                readably_str.push_back('\\');
                                readably_str.push_back('"');
                                break;
                            case '\n':
                                readably_str.push_back('\\');
                                readably_str.push_back('n');
                                break;
                            default:
                                readably_str.push_back(str_ast->value[i]);
                        }
                    }
                    readably_str = "\"" + readably_str + "\"";
                }else{
                    readably_str = str_ast->value;
                }
                ret = readably_str;
                break;
           }
           case NIL: {
                ret = "nil";
                break;
           }
           case FUNCTION: {
                ret = "#<function>";
                break;
           }
           case KEYWORD: {
                std::shared_ptr<AstTokenKeyword> key_ast;
                key_ast = std::static_pointer_cast<AstTokenKeyword>(ast);
                ret = key_ast->value.replace(0, 1, ":");
                break;
           }
           case OPERATOR: {
                throw std::string("Unexpected Operator");
           }
        }
    }
    return ret;
}


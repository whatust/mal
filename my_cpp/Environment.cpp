#include "Environment.h"

MalEnv::MalEnv(MalEnv* _outer, std::shared_ptr<AstToken> _param) : outer(_outer) {

    check_token(_param->type != LIST, LIST, _param->type);

    bool next_args = false;
    std::shared_ptr<AstTokenList> list_ast;
    list_ast = std::static_pointer_cast<AstTokenList>(_param);

    for(auto key : list_ast->list) {

        std::shared_ptr<AstTokenSymbol> symbol;
        symbol = std::static_pointer_cast<AstTokenSymbol>(key);

        if(next_args){
            largs = symbol->name;
            next_args = false;
        }

        if(symbol->name.compare("&") == 0 && largs.empty()){
            next_args = true;
        }else{
            params.push_back(symbol->name);
        }
    }
}

std::shared_ptr<AstToken>
MalEnv::find(const std::string& key) {

    if(bindings.find(key) != end(bindings))
        return bindings.find(key)->second;

    if(data.find(key) != end(data))
        return data.find(key)->second;

    check_valid_symbol(outer == nullptr, "'%s' not found.", key);

    return outer->find(key);
}

void
MalEnv::set(const std::string& key, std::shared_ptr<AstToken> value) {

    data[key] = value;

    return;
}

std::shared_ptr<AstToken>
MalEnv::get(const std::string& key) {
    return find(key);
}

void
MalEnv::set_bindings(MalArgs init, MalArgs end) {

    check_arguments(end - init < (int) params.size() - (int) !largs.empty(),
            std::to_string(params.size() - (int) !largs.empty()), std::to_string(end - init));

    for(auto it = std::begin(params); it != std::end(params); it++) {

        if(it->compare(largs) == 0){
            bindings[*it] = std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenList>(new AstTokenList(init, end)));
        } else {
            bindings[*it] = *init++;
        }
    }

    return;
}

MalEnv*
MalEnv::get_outer() {
    MalEnv* aux;

    aux = this;
    while(aux->outer != nullptr)
        aux = aux->outer;

    return aux;
}

void MalEnv::print() {
    std::cout << "Printing Env" << std::endl;
    std::cout << "data:" << std::endl;
    for(auto entry : data) {
        std::cout << "key: " << entry.first << std::endl;
    }

    std::cout << "bindings:" << std::endl;
    for(auto entry : bindings) {
        std::cout << "key: " << entry.first << std::endl;
    }

    return;
}


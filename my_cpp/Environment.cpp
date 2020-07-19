#include "Environment.h"

std::shared_ptr<AstToken>
MalEnv::find(const std::string& key) {

    if(bindings.find(key) != end(bindings))
        return bindings.find(key)->second;

    if(data.find(key) != end(data))
        return data.find(key)->second;

    if(outer == nullptr)
        return std::shared_ptr<AstToken>(nullptr);

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
MalEnv::set_bindings(const std::vector<std::string>& params, std::string largs, MalArgs init, MalArgs end) {

    arg_assert(end - init >= (int) params.size() - (int) !largs.empty(),
            ArgumentException(params.size() - (int) !largs.empty(), end - init));

    for(auto it = std::begin(params); it != std::end(params); it++) {

        if(it->compare(largs) == 0){
            bindings[*it] = std::shared_ptr<AstTokenList>(new AstTokenList(init, end));
        } else {
            bindings[*it] = *init++;
        }
    }
    return;
}

void MalEnv::print() {
    std::cout << "data:" << std::endl;
    for(auto entry : data) {
        std::cerr << "key: " << entry.first << std::endl;
    }

    std::cout << "bindings:" << std::endl;
    for(auto entry : bindings) {
        std::cout << "key: " << entry.first << std::endl;
    }

    if(outer)
        outer->print();

    return;
}


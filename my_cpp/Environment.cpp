#include "Environment.h"

std::shared_ptr<AstToken>
MalEnv::find(const std::string& key) {

    if(data.find(key) != end(data))
        return data.find(key)->second;

    check_valid_symbol(outer == nullptr, "Unknown symbol: %s", key);

    return outer->find(key);
};

void
MalEnv::set(const std::string& key, std::shared_ptr<AstToken> value) {

    data.insert(std::pair<std::string, std::shared_ptr<AstToken>>(key, value));
    return;
}

std::shared_ptr<AstToken>
MalEnv::get(const std::string& key) {
    return find(key);
}


#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include<string>
#include<memory>
#include "Types.h"
#include "Validation.h"

class MalEnv {
private:
    MalEnv *outer;
    std::unordered_map<std::string, std::shared_ptr<AstToken>> bindings;
    std::unordered_map<std::string, std::shared_ptr<AstToken>> data;
public:
    MalEnv() : outer(nullptr) {};
    MalEnv(MalEnv* _outer) : outer(_outer) {};
    std::shared_ptr<AstToken> find(const std::string& key);
    void set(const std::string& key, std::shared_ptr<AstToken> value);
    std::shared_ptr<AstToken> get(const std::string& key);
    void print();
};

#endif //ENVIRONMENT_H_

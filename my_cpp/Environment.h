#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include<string>
#include<memory>
#include "Types.h"
#include "Validation.h"

class MalEnv {
private:
    MalEnv *outer;
    std::string largs;
    std::vector<std::string> params;
    std::unordered_map<std::string, std::shared_ptr<AstToken>> data;
    std::unordered_map<std::string, std::shared_ptr<AstToken>> bindings;
public:
    MalEnv() : outer(nullptr) {};
    MalEnv(MalEnv* _outer) : outer(_outer) {};
    MalEnv(MalEnv* _outer, std::shared_ptr<AstToken> _param);
    std::shared_ptr<AstToken> find(const std::string& key);
    std::shared_ptr<AstToken> get(const std::string& key);
    void set(const std::string& key, std::shared_ptr<AstToken> value);
    void set_bindings(MalArgs init, MalArgs end);
    MalEnv* get_outer();
    void print();
};

#endif //ENVIRONMENT_H_

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include<string>
#include<memory>

#include"BasicTypes.h"
#include"Validation.h"

class MalEnv {
private:
    MalEnv* outer;
    std::unordered_map<std::string, std::shared_ptr<AstToken>> data;
    std::unordered_map<std::string, std::shared_ptr<AstToken>> bindings;
public:
    MalEnv() : outer(nullptr) {};
    MalEnv(MalEnv* _outer) : outer(_outer) {};
    std::shared_ptr<AstToken> find(const std::string& key);
    std::shared_ptr<AstToken> get(const std::string& key);
    void set(const std::string& key, std::shared_ptr<AstToken> value);
    void set_bindings(const std::vector<std::string>& params, std::string largs,
                                                    MalArgs init, MalArgs end);
    MalEnv* get_outer();
    void print();
};

extern MalEnv* outer_env;

#endif //ENVIRONMENT_H_

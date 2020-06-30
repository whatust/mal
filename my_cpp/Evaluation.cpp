#include"Evaluation.h"

std::shared_ptr<AstToken> eval_ast (std::shared_ptr<AstToken> ast, MalEnv& repl_env) {

    std::shared_ptr<AstToken> ret;
    //std::cout << "Printing Env" << std::endl;
    //repl_env.print();
    //std::cerr << "=============" << std::endl;

    switch (ast->type) {
        case SYMBOL: {
            std::string symbol;
            std::shared_ptr<AstTokenSymbol> symbol_ast;

            symbol_ast = static_pointer_cast<AstTokenSymbol> (ast);
            symbol = symbol_ast->name;

            ret = repl_env.get(symbol);
            break;
        }
        case LIST: {
            std::shared_ptr<AstTokenList> list_ast;
            list_ast = static_pointer_cast<AstTokenList>(ast);
            std::shared_ptr<AstTokenList> new_list_ast(new AstTokenList());

            for (auto token : list_ast->list) {
                new_list_ast->list.push_back(eval(token, repl_env));
            }
            ret = std::static_pointer_cast<AstToken>(new_list_ast);
            break;
        }
        case LIST_V: {
            std::shared_ptr<AstTokenList> list_ast;
            list_ast = static_pointer_cast<AstTokenList>(ast);
            std::shared_ptr<AstTokenVector> vect_ast(new AstTokenVector);

            for (auto token : list_ast->list) {
                vect_ast->list.push_back(eval(token, repl_env));
            }
            ret = std::static_pointer_cast<AstToken>(vect_ast);
            break;
        }
        case LIST_H: {
            std::shared_ptr<AstTokenList> list_ast;
            list_ast = static_pointer_cast<AstTokenList>(ast);
            std::shared_ptr<AstTokenHashMap> hash_ast(new AstTokenHashMap);

            auto token=std::begin(list_ast->list);
            //check_map((std::end(list_ast->list) - token) % 2 || std::end(list_ast->list) - token == 0);
            check_map((std::end(list_ast->list) - token) % 2);

            while (token != std::end(list_ast->list)) {

                std::shared_ptr<AstToken> key_token = eval(*(token++), repl_env);
                std::string key; 

                if(key_token->type == STRING){
                    key = std::static_pointer_cast<AstTokenString>(key_token)->value;
                }else{
                    key = std::static_pointer_cast<AstTokenKeyword>(key_token)->value;
                }

                hash_ast->map.insert(std::pair<std::string,
                    std::shared_ptr<AstToken>>(std::move(key), eval(*(token++), repl_env)));
            }

            ret = std::static_pointer_cast<AstToken>(hash_ast);
            break;
        }
        default: {
            ret = ast;
        }
    }
    return ret;
}

std::shared_ptr<AstToken> eval(std::shared_ptr<AstToken> ast, MalEnv& repl_env) {

    std::shared_ptr<AstToken> ret;

    switch (ast->type) {
        case LIST: {

            std::shared_ptr<AstTokenList> list_ast = std::static_pointer_cast<AstTokenList>(ast);

            if(!list_ast->list.empty() && list_ast->list[0]->type == SYMBOL &&
                std::static_pointer_cast<AstTokenSymbol>(list_ast->list[0])->name == "def!"){

                check_arguments(list_ast->list.size() - 1 != 2, "2", std::to_string(list_ast->list.size() - 1));
                check_token(list_ast->list[1]->type != SYMBOL, SYMBOL, list_ast->list[1]->type);

                std::string key_token = std::static_pointer_cast<AstTokenSymbol>(list_ast->list[1])->name;
                std::shared_ptr<AstToken> value = eval(list_ast->list[2], repl_env);
                repl_env.set(key_token, value);

                ret = value;
            } else if(!list_ast->list.empty() && list_ast->list[0]->type == SYMBOL &&
                std::static_pointer_cast<AstTokenSymbol>(list_ast->list[0])->name == "let*"){

                check_arguments(list_ast->list.size() - 1 != 2, "2", std::to_string(list_ast->list.size() - 1));
                check_token(list_ast->list[1]->type != LIST && list_ast->list[1]->type != LIST_V,
                                                                LIST, list_ast->list[1]->type);

                MalEnv new_repl_env(&repl_env);
                std::shared_ptr<AstTokenList> bindings;

                bindings = std::static_pointer_cast<AstTokenList>(list_ast->list[1]);
                check_map(bindings->list.size() % 2);

                for(auto it=std::begin(bindings->list); it != std::end(bindings->list);){

                    check_token((*it)->type != SYMBOL, SYMBOL, (*it)->type);
                    std::string key = std::static_pointer_cast<AstTokenSymbol>(*(it++))->name;
                    new_repl_env.set(key, eval(*(it++), new_repl_env));
                }
                ret = eval(list_ast->list[2], new_repl_env);
            } else if(!list_ast->list.empty() && list_ast->list[0]->type == SYMBOL &&
                    std::static_pointer_cast<AstTokenSymbol>(list_ast->list[0])->name == "do") {

                check_arguments(list_ast->list.size() < 2, "1", std::to_string(list_ast->list.size() - 1));

                for(int i=1; i < (int) list_ast->list.size() - 1; i++){
                    eval(list_ast->list[i], repl_env);
                }

                ret = eval(list_ast->list.back(), repl_env);

            } else if(!list_ast->list.empty() && list_ast->list[0]->type == SYMBOL &&
                    std::static_pointer_cast<AstTokenSymbol>(list_ast->list[0])->name == "if") {

                check_arguments(list_ast->list.size() < 3, "2", std::to_string(list_ast->list.size() - 1));

                std::shared_ptr<AstToken> condition;

                condition = eval(list_ast->list[1], repl_env);

                if(condition->type == NIL || (condition->type == BOOL &&
                    !std::static_pointer_cast<AstTokenBool>(condition)->value)) {

                    if (list_ast->list.size() < 4)
                        ret = std::shared_ptr<AstToken>(new AstTokenNil());
                    else
                        ret = eval(list_ast->list[3], repl_env);

                } else {
                    ret = eval(list_ast->list[2], repl_env);
                }
            } else if(!list_ast->list.empty() && list_ast->list[0]->type == SYMBOL &&
                    std::static_pointer_cast<AstTokenSymbol>(list_ast->list[0])->name == "fn*") {

                check_arguments(list_ast->list.size() < 3, "2", std::to_string(list_ast->list.size() - 1));
                check_token(list_ast->list[1]->type != LIST && list_ast->list[1]->type != LIST_V,
                                                                LIST, list_ast->list[1]->type);

                ret = std::static_pointer_cast<AstToken>(std::shared_ptr<AstTokenFunction>(
                            new AstTokenFunction(&repl_env, list_ast->list[1], list_ast->list[2])));
                //std::cerr << "function" <<std::endl;
            } else {
                list_ast = static_pointer_cast<AstTokenList> (eval_ast(ast, repl_env));

                if (list_ast->list.empty()) {
                    ret = ast;
                    break;
                }

                if(list_ast->list[0]->type == OPERATOR) {
                    std::shared_ptr<AstTokenOperator> opToken;

                    opToken = std::static_pointer_cast<AstTokenOperator>(eval(list_ast->list[0], repl_env));
                    ret = (*opToken)(++(std::cbegin(list_ast->list)), std::cend(list_ast->list));
                } else if(list_ast->list[0]->type == FUNCTION) {
                    std::shared_ptr<AstTokenFunction> funToken;


                    funToken = std::static_pointer_cast<AstTokenFunction>(eval(list_ast->list[0], repl_env));

                    MalEnv* new_repl_env = new MalEnv(funToken->scope);
                    new_repl_env->set_bindings(funToken->params, funToken->larg,
                        ++(std::cbegin(list_ast->list)), std::cend(list_ast->list));
                    ret = eval(funToken->function, *new_repl_env);
                } else {
                    ret = ast;
                }
            }

            break;
        }
        default:
            ret = eval_ast(ast, repl_env);
    }
    return ret;
}


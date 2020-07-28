#include"Evaluation.h"

std::shared_ptr<AstToken> eval_ast (std::shared_ptr<AstToken> ast, std::shared_ptr<MalEnv> repl_env) {

    std::shared_ptr<AstToken> ret;
    //std::cout << "Printing Env" << std::endl;
    //repl_env.print();
    //std::cerr << "=============" << std::endl;

    switch (ast->type) {
        case SYMBOL: {
            std::string symbol;
            std::shared_ptr<AstTokenSymbol> symbol_ast;

            symbol_ast = as_type<AstTokenSymbol> (ast);
            symbol = symbol_ast->name;

            ret = repl_env->get(symbol);

            if(ret != nullptr) break;
            throw SymException(symbol);
        }
        case LIST: {
            std::shared_ptr<AstTokenList> list_ast;
            list_ast = as_type<AstTokenList>(ast);
            std::shared_ptr<AstTokenList> new_list_ast(new AstTokenList());

            for (auto token : list_ast->list) {
                new_list_ast->list.push_back(eval(token, repl_env));
            }
            ret = new_list_ast;
            break;
        }
        case VECTOR: {
            std::shared_ptr<AstTokenList> list_ast;
            list_ast = as_type<AstTokenList>(ast);
            std::shared_ptr<AstTokenVector> vect_ast(new AstTokenVector);

            for (auto token : list_ast->list) {
                vect_ast->list.push_back(eval(token, repl_env));
            }
            ret = vect_ast;
            break;
        }
        case HASH_MAP: {
            std::shared_ptr<AstTokenList> list_ast;
            list_ast = as_type<AstTokenList>(ast);
            std::shared_ptr<AstTokenHashMap> hash_ast(new AstTokenHashMap);

            auto token=std::begin(list_ast->list);
            map_assert((std::end(list_ast->list) - token) % 2 == 0, MapException());

            while (token != std::end(list_ast->list)) {

                std::shared_ptr<AstToken> key_token = eval(*(token++), repl_env);
                std::string key;

                if(key_token->type == STRING){
                    key = as_type<AstTokenString>(key_token)->value;
                }else{
                    key = as_type<AstTokenKeyword>(key_token)->value;
                }

                hash_ast->map.insert(std::pair<std::string,
                    std::shared_ptr<AstToken>>(std::move(key), eval(*(token++), repl_env)));
            }

            ret = hash_ast;
            break;
        }
        default: {
            ret = ast;
        }
    }
    return ret;
}

bool is_pair(std::shared_ptr<AstToken> ast, int pos) {
    return (ast->type == LIST || ast->type == VECTOR) &&
        (as_type<AstTokenList>(ast)->list.size() - pos) > 0;
}

std::shared_ptr<AstToken> quasiquote(std::shared_ptr<AstToken> ast, int pos) {

    if(!is_pair(ast, pos)) {

        std::shared_ptr<AstTokenList> aux_ast(new AstTokenList());

        aux_ast->list.push_back(std::shared_ptr<AstTokenSymbol>(new AstTokenSymbol("quote")));

        if(ast->type == LIST || ast->type == VECTOR){
            aux_ast->list.push_back(std::shared_ptr<AstTokenList>(new AstTokenList()));
        }else{
            aux_ast->list.push_back(ast);
        }

        return aux_ast;

    }else{
        std::shared_ptr<AstTokenList> list_ast;
        list_ast = as_type<AstTokenList> (ast);

        if(list_ast->list[pos]->type == SYMBOL &&
            as_type<AstTokenSymbol>(list_ast->list[pos])->name =="unquote") {

            arg_assert(list_ast->list.size() - pos >= 2, ArgumentException(
                                        1, list_ast->list.size() - pos - 1));

            return list_ast->list[pos + 1];

        } else if(is_pair(list_ast->list[pos], 0) && as_type<AstTokenList>(list_ast->list[pos])->list[0]->type == SYMBOL &&
                as_type<AstTokenSymbol>(as_type<AstTokenList>(list_ast->list[pos])->list[0])->name == "splice-unquote") {

            arg_assert(as_type<AstTokenList>(list_ast->list[pos])->list.size() >= 2,
                                    ArgumentException(1, list_ast->list.size() - 1));

            std::shared_ptr<AstTokenList> aux_ast(new AstTokenList());

            aux_ast->list.push_back(std::shared_ptr<AstTokenSymbol>(new AstTokenSymbol("concat")));
            aux_ast->list.push_back(as_type<AstTokenList>(list_ast->list[pos])->list[1]);
            aux_ast->list.push_back(quasiquote(ast, pos + 1));

            return aux_ast;
        }
        std::shared_ptr<AstTokenList> aux_ast(new AstTokenList());
        aux_ast->list.push_back(std::shared_ptr<AstTokenSymbol>(new AstTokenSymbol("cons")));
        aux_ast->list.push_back(quasiquote(list_ast->list[pos], 0));
        aux_ast->list.push_back(quasiquote(ast, pos + 1));

        return aux_ast;
    }
}

bool is_macro_call(std::shared_ptr<AstToken> ast, std::shared_ptr<MalEnv> repl_env) {

    if(ast->type == LIST) {
        std::shared_ptr<AstTokenList> list_ast;
        list_ast = as_type<AstTokenList>(ast);

        if(!list_ast->list.empty() && list_ast->list[0]->type == SYMBOL) {
            std::string symbol = as_type<AstTokenSymbol>(list_ast->list[0])->name;
            std::shared_ptr<AstToken>raw_ast = repl_env->get(symbol);

            if(raw_ast != nullptr && raw_ast->type == FUNCTION) {
                std::shared_ptr<AstTokenFunction> fun_ast;
                fun_ast = as_type<AstTokenFunction>(raw_ast);

                return fun_ast->is_macro;
            }
        }
    }

    return false;
}

std::shared_ptr<AstToken> macroexpand(std::shared_ptr<AstToken> ast, std::shared_ptr<MalEnv> repl_env) {

    std::shared_ptr<AstToken> ret = ast;

    while(is_macro_call(ret, repl_env)) {
        //std::cerr  << "Error" << std::endl;

        std::shared_ptr<AstTokenList> list_ast = as_type<AstTokenList>(ret);
        std::string symbol = as_type<AstTokenSymbol>(list_ast->list[0])->name;
        std::shared_ptr<AstTokenFunction> fun_ast = as_type<AstTokenFunction>(repl_env->get(symbol));

        if(fun_ast == nullptr) throw SymException(symbol);

        std::shared_ptr<MalEnv> new_repl_env = std::shared_ptr<MalEnv>(
                                            new MalEnv(fun_ast->scope));

        new_repl_env->set_bindings(fun_ast->params, fun_ast->larg,
                ++(std::cbegin(list_ast->list)), std::cend(list_ast->list));
        ret = eval(fun_ast->function, new_repl_env);
    }

    return ret;
}

std::shared_ptr<AstToken> eval(std::shared_ptr<AstToken> ast, std::shared_ptr<MalEnv> repl_env) {

    bool loop = true;
    std::shared_ptr<AstToken> ret;
    std::shared_ptr<AstToken> token;
    std::shared_ptr<MalEnv> env = repl_env;
    token = ast;

    while(loop){

        token = macroexpand(token, repl_env);

        if (token->type == LIST) {

            std::shared_ptr<AstTokenList> list_ast = as_type<AstTokenList>(token);

            if(!list_ast->list.empty() && list_ast->list[0]->type == SYMBOL &&
                as_type<AstTokenSymbol>(list_ast->list[0])->name == "def!"){

                arg_assert(list_ast->list.size() - 1 == 2, ArgumentException(
                                                2, list_ast->list.size() - 1));

                std::string key_token = as_type<AstTokenSymbol>(list_ast->list[1])->name;
                std::shared_ptr<AstToken> value = eval(list_ast->list[2], env);
                env->set(key_token, value);

                ret = value;
                loop = false;

            } else if(!list_ast->list.empty() && list_ast->list[0]->type == SYMBOL &&
                as_type<AstTokenSymbol>(list_ast->list[0])->name == "let*"){

                arg_assert(list_ast->list.size() - 1 == 2, ArgumentException(
                                                2, list_ast->list.size() - 1));

                std::shared_ptr<MalEnv> new_repl_env(new MalEnv(env));
                std::shared_ptr<AstTokenList> bindings;

                bindings = as_type<AstTokenList>(list_ast->list[1]);
                map_assert(bindings->list.size() % 2 == 0, MapException());

                for(auto it=std::begin(bindings->list); it != std::end(bindings->list);){

                    std::string key = as_type<AstTokenSymbol>(*(it++))->name;
                    new_repl_env->set(key, eval(*(it++), new_repl_env));
                }
                token = list_ast->list[2];
                env = new_repl_env;
                continue;

            } else if(!list_ast->list.empty() && list_ast->list[0]->type == SYMBOL &&
                    as_type<AstTokenSymbol>(list_ast->list[0])->name == "do") {

                arg_assert(list_ast->list.size() >= 2, ArgumentException(
                                            1, list_ast->list.size() - 1));

                for(int i=1; i < (int) list_ast->list.size() - 1; i++){
                    eval(list_ast->list[i], env);
                }

                token = list_ast->list.back();
                continue;

            } else if(!list_ast->list.empty() && list_ast->list[0]->type == SYMBOL &&
                    as_type<AstTokenSymbol>(list_ast->list[0])->name == "if") {

                arg_assert(list_ast->list.size() >= 3, ArgumentException(
                                        2, (list_ast->list.size() - 1)));

                std::shared_ptr<AstToken> condition;

                condition = eval(list_ast->list[1], env);

                if(condition->type == NIL || (condition->type == BOOL &&
                    !as_type<AstTokenBool>(condition)->value)) {

                    if (list_ast->list.size() < 4){
                        ret = std::shared_ptr<AstToken>(new AstTokenNil());
                    } else {
                        token = list_ast->list[3];
                        continue;
                    }
                } else {
                    token = list_ast->list[2];
                    continue;
                }
                loop = false;

            } else if(!list_ast->list.empty() && list_ast->list[0]->type == SYMBOL &&
                    as_type<AstTokenSymbol>(list_ast->list[0])->name == "fn*") {

                arg_assert(list_ast->list.size() >= 3, ArgumentException(
                                            2, list_ast->list.size() - 1));

                ret = std::shared_ptr<AstTokenFunction>(new AstTokenFunction(env, list_ast->list[1],
                                                                        list_ast->list[2], false));
                loop = false;

            } else if(!list_ast->list.empty() && list_ast->list[0]->type == SYMBOL &&
                    as_type<AstTokenSymbol>(list_ast->list[0])->name == "quote") {

                arg_assert(list_ast->list.size() == 2, ArgumentException(
                                        1, (list_ast->list.size() - 1)));

                ret = list_ast->list[1];
                loop = false;
                continue;

            } else if(!list_ast->list.empty() && list_ast->list[0]->type == SYMBOL &&
                    as_type<AstTokenSymbol>(list_ast->list[0])->name == "quasiquote") {

                arg_assert(list_ast->list.size() >= 2, ArgumentException(
                                            1, list_ast->list.size() - 1));

                token = quasiquote(list_ast->list[1], 0);
                continue;

            } else if(!list_ast->list.empty() && list_ast->list[0]->type == SYMBOL &&
                    as_type<AstTokenSymbol>(list_ast->list[0])->name == "defmacro!") {

                arg_assert(list_ast->list.size() - 1 == 2, ArgumentException(
                                                2, list_ast->list.size() - 1));

                std::string key_token = as_type<AstTokenSymbol>(list_ast->list[1])->name;
                std::shared_ptr<AstToken> value = eval(list_ast->list[2], env);

                if(value->type == FUNCTION) {

                    std::shared_ptr<AstTokenFunction> fun_ast;
                    fun_ast = as_type<AstTokenFunction>(value);

                    std::shared_ptr<AstTokenFunction> macro_ast(new AstTokenFunction);

                    macro_ast->scope = fun_ast->scope;
                    macro_ast->larg = fun_ast->larg;
                    macro_ast->function = fun_ast->function;
                    macro_ast->is_macro = true;

                   std::copy(std::cbegin(fun_ast->params), std::cend(fun_ast->params),
                                   std::back_inserter(macro_ast->params));

                    env->set(key_token, macro_ast);
                } else {
                    throw MacroException(value->type);
                }

                ret = value;
                loop = false;

            } else if(!list_ast->list.empty() && list_ast->list[0]->type == SYMBOL &&
                    as_type<AstTokenSymbol>(list_ast->list[0])->name == "macroexpand") {
                arg_assert(list_ast->list.size() == 2, ArgumentException(1, list_ast->list.size()-1));

                return macroexpand(list_ast->list[1], repl_env);

            } else if(!list_ast->list.empty() && list_ast->list[0]->type == SYMBOL &&
                    as_type<AstTokenSymbol>(list_ast->list[0])->name == "try*") {

                arg_assert(list_ast->list.size() >= 2, ArgumentException(1, list_ast->list.size()-1));

                try{
                    ret = eval(list_ast->list[1], repl_env);
                } catch(std::shared_ptr<AstTokenException> e) {

                    if(list_ast->list.size() < 3)
                        throw e;

                    std::shared_ptr<AstTokenList> catch_list_ast;
                    catch_list_ast = as_type<AstTokenList>(list_ast->list[2]);

                    std::shared_ptr<AstTokenSymbol> catch_ast;
                    catch_ast = as_type<AstTokenSymbol>(catch_list_ast->list[0]);

                    if(catch_ast->name == "catch*") {

                        std::vector<std::string> excp_name;
                        excp_name.push_back(as_type<AstTokenSymbol>(catch_list_ast->list[1])->name);

                        std::shared_ptr<MalEnv> new_repl_env = std::shared_ptr<MalEnv>(new MalEnv(outer_env));

                        std::vector<std::shared_ptr<AstToken>> params;
                        params.push_back(eval(e->ast, repl_env));

                        new_repl_env->set_bindings(excp_name, std::string(""),
                                    std::cbegin(params), std::cend(params));

                        ret = eval(catch_list_ast->list[2],new_repl_env);
                    }else {
                        throw TryException();
                    }

                } catch(std::exception& e) {

                    if(list_ast->list.size() < 3) {
                        std::cerr << e.what() << std::endl;
                        throw EmptyInput();
                    }

                    std::string error(e.what());

                    std::shared_ptr<AstTokenList> catch_list_ast;
                    catch_list_ast = as_type<AstTokenList>(list_ast->list[2]);

                    std::shared_ptr<AstTokenSymbol> catch_ast;
                    catch_ast = as_type<AstTokenSymbol>(catch_list_ast->list[0]);

                    if(catch_ast->name == "catch*") {

                        std::vector<std::string> excp_name;
                        excp_name.push_back(as_type<AstTokenSymbol>(catch_list_ast->list[1])->name);

                        std::shared_ptr<MalEnv> new_repl_env = std::shared_ptr<MalEnv>(new MalEnv(outer_env));

                        std::vector<std::shared_ptr<AstToken>> params;
                        params.push_back(std::shared_ptr<AstTokenString>(new AstTokenString(error)));

                        new_repl_env->set_bindings(excp_name, std::string(""),
                                    std::cbegin(params), std::cend(params));

                        ret = eval(catch_list_ast->list[2],new_repl_env);
                    }else {
                        throw TryException();
                    }
                }

            } else {
                list_ast = as_type<AstTokenList> (eval_ast(token, env));

                if (list_ast->list.empty()) {
                    ret = token;
                    loop = false;
                    continue;
                }

                if(list_ast->list[0]->type == OPERATOR) {
                    std::shared_ptr<AstTokenOperator> opToken;

                    opToken = as_type<AstTokenOperator>(eval(list_ast->list[0], env));
                    ret = (*opToken)(++(std::cbegin(list_ast->list)), std::cend(list_ast->list));
                } else if(list_ast->list[0]->type == FUNCTION) {
                    std::shared_ptr<AstTokenFunction> funToken;

                    funToken = as_type<AstTokenFunction>(eval(list_ast->list[0], env));

                    std::shared_ptr<MalEnv> new_repl_env = std::shared_ptr<MalEnv>(
                                                        new MalEnv(funToken->scope));
                    new_repl_env->set_bindings(funToken->params, funToken->larg,
                        ++(std::cbegin(list_ast->list)), std::cend(list_ast->list));
                    ret = eval(funToken->function, new_repl_env);
                } else {
                    ret = token;
                }
            }
            loop = false;
        }else{
            ret = eval_ast(token, env);
            loop = false;
        }
    }
    return ret;
}


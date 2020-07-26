#include"Core.h"

void start_outer_env(std::shared_ptr<MalEnv> repl_env) {

    repl_env->set("+", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("+", &addOperator)));
    repl_env->set("-", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("-", &subOperator)));
    repl_env->set("*", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("*", &mulOperator)));
    repl_env->set("/", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("/", &divOperator)));
    repl_env->set("=", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("=", &eqOperator)));
    repl_env->set(">", std::shared_ptr<AstTokenOperator>(new AstTokenOperator(">", &gtOperator)));
    repl_env->set(">=", std::shared_ptr<AstTokenOperator>(new AstTokenOperator(">=", &gteOperator)));
    repl_env->set("<", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("<", &ltOperator)));
    repl_env->set("<=", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("<=", &lteOperator)));
    repl_env->set("list", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("list", &listOperator)));
    repl_env->set("list?", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("list?", &listqOperator)));
    repl_env->set("empty?", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("empty?", &emptyOperator)));
    repl_env->set("count", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("count", &countOperator)));
    repl_env->set("prn", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("prn", &prnOperator)));
    repl_env->set("str", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("str", &strOperator)));
    repl_env->set("pr-str", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("pr-str", &prstrOperator)));
    repl_env->set("println", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("println", &printlnOperator)));
    repl_env->set("read-string", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("read-string", &readstrOperator)));
    repl_env->set("slurp", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("slurp", &slurpOperator)));
    repl_env->set("eval", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("eval", &evalOperator)));
    repl_env->set("atom", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("atom", &atomOperator)));
    repl_env->set("atom?", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("atom?", &atomqOperator)));
    repl_env->set("deref", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("deref", &derefOperator)));
    repl_env->set("reset!", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("reset!", &resetOperator)));
    repl_env->set("swap!", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("swap!", &swapOperator)));
    repl_env->set("cons", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("cons", &consOperator)));
    repl_env->set("concat", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("concat", &concatOperator)));
    repl_env->set("nth", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("nth", &nthOperator)));
    repl_env->set("first", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("first", &firstOperator)));
    repl_env->set("rest", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("rest", &restOperator)));
    repl_env->set("throw", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("throw", &throwOperator)));

    repl_env->set("apply", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("apply", &applyOperator)));
    repl_env->set("map", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("map", &mapOperator)));

    repl_env->set("symbol?", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("symbol?", &symbolqOperator)));
    repl_env->set("false?", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("false?", &falseqOperator)));
    repl_env->set("true?", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("true?", &trueqOperator)));
    repl_env->set("nil?", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("nil?", &nilqOperator)));

    repl_env->set("symbol", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("symbol", &symbolOperator)));
    repl_env->set("keyword", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("keyword", &keywordOperator)));
    repl_env->set("keyword?", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("keyword?", &keywordqOperator)));

    repl_env->set("vector", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("vector", &vectorOperator)));
    repl_env->set("vector?", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("vector?", &vectorqOperator)));
    repl_env->set("sequential?", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("sequential?", &sequentialOperator)));
    repl_env->set("hash-map", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("hash-map", &hashmapOperator)));
    repl_env->set("map?", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("map?", mapqOperator)));

    repl_env->set("get", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("get", getOperator)));
    repl_env->set("assoc", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("assoc", assocOperator)));
    repl_env->set("dissoc", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("dissoc", dissocOperator)));
    repl_env->set("contains?", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("contains?", containsqOperator)));
    repl_env->set("keys", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("keys", keysOperator)));
    repl_env->set("vals", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("vals", valsOperator)));

    repl_env->set("readline", std::shared_ptr<AstTokenOperator>(new AstTokenOperator("readline", readlineOperator)));

    outer_env = repl_env;
    return;
}

std::shared_ptr<AstToken> addOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 2, ArgumentException(2, end - args)); int num_a = as_type<AstTokenNumber>(*args++)->value;
    int num_b = as_type<AstTokenNumber>(*args)->value;

    return std::shared_ptr<AstTokenNumber>(new AstTokenNumber(num_a + num_b));
}

std::shared_ptr<AstToken> subOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 2, ArgumentException(2, end - args));
    int num_a = as_type<AstTokenNumber>(*args++)->value;
    int num_b = as_type<AstTokenNumber>(*args)->value;

    return std::shared_ptr<AstTokenNumber>(new AstTokenNumber(num_a - num_b)); }

std::shared_ptr<AstToken> mulOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 2, ArgumentException(2, end - args));
    int num_a = as_type<AstTokenNumber>(*args++)->value;
    int num_b = as_type<AstTokenNumber>(*args)->value;

    return std::shared_ptr<AstTokenNumber>(new AstTokenNumber(num_a * num_b));
}

std::shared_ptr<AstToken> divOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 2, ArgumentException(2, end - args));
    int num_a = as_type<AstTokenNumber>(*args++)->value;
    int num_b = as_type<AstTokenNumber>(*args)->value;

    return std::shared_ptr<AstTokenNumber>(new AstTokenNumber(num_a / num_b));
}


bool equal(std::shared_ptr<AstToken> a, std::shared_ptr<AstToken> b) {

    if(a->type == NIL && b->type == NIL) {

        return true;

    }else if(a->type == NUMBER && b->type == NUMBER) {

        int num_a = as_type<AstTokenNumber>(a)->value;
        int num_b = as_type<AstTokenNumber>(b)->value;

        return num_a == num_b;

    }else if(a->type == BOOL && b->type == BOOL) {

        bool ba = as_type<AstTokenBool>(a)->value;
        bool bb = as_type<AstTokenBool>(b)->value;

        return ba == bb;

    }else if(a->type == STRING && b->type == STRING) {

        std::string string_a = as_type<AstTokenString>(a)->value;
        std::string string_b = as_type<AstTokenString>(b)->value;

        return string_a == string_b;

    }else if(a->type == SYMBOL && b->type == SYMBOL) {

        std::string name_a = as_type<AstTokenSymbol>(a)->name;
        std::string name_b = as_type<AstTokenSymbol>(b)->name;

        return name_a == name_b;

    }else if(a->type == KEYWORD && b->type == KEYWORD) {

        std::string keyword_a = as_type<AstTokenKeyword>(a)->value;
        std::string keyword_b = as_type<AstTokenKeyword>(b)->value;

        return keyword_a == keyword_b;

    }else if((a->type == LIST || a->type == VECTOR) && (b->type == LIST || b->type == VECTOR)) {

        std::shared_ptr<AstTokenList>list_a;
        std::shared_ptr<AstTokenList>list_b;

        list_a = as_type<AstTokenList>(a);
        list_b = as_type<AstTokenList>(b);

        if(list_a->list.size() != list_b->list.size())
            return false;

        auto it_a = std::begin(list_a->list);
        auto it_b = std::begin(list_b->list);

        while(it_a != std::end(list_a->list) && it_b != std::end(list_b->list)) {

            if(!equal(*it_a, *it_b))
                return false;

            it_a++;
            it_b++;
        }
        return true;
    }else if(a->type == HASH_MAP && b->type == HASH_MAP) {

        std::shared_ptr<AstTokenHashMap>hash_a;
        std::shared_ptr<AstTokenHashMap>hash_b;

        hash_a = as_type<AstTokenHashMap>(a);
        hash_b = as_type<AstTokenHashMap>(b);

        if(hash_a->map.size() != hash_b->map.size())
            return false;

        for(auto entry_a : hash_a->map) {

            if(hash_b->map.find(entry_a.first) != std::end(hash_b->map)) {
                if(!equal(entry_a.second, hash_b->map[entry_a.first])){
                    return false;
                }
            } else {
                return false;
            }
        }
        return true;
    }else if(a->type != b->type) {
        return false;
    }

    throw UncException(a->type, b->type);
}

std::shared_ptr<AstToken> eqOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 2, ArgumentException(2, end - args));
    std::shared_ptr<AstToken> a = (*args++);
    std::shared_ptr<AstToken> b = (*args);

    return std::shared_ptr<AstTokenBool>(new AstTokenBool(equal(a, b)));
}

std::shared_ptr<AstToken> ltOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 2, ArgumentException(2, end - args));
    int num_a = as_type<AstTokenNumber>(*args++)->value;
    int num_b = as_type<AstTokenNumber>(*args)->value;

    return std::shared_ptr<AstTokenBool>(new AstTokenBool(num_a < num_b));
}

std::shared_ptr<AstToken> lteOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 2, ArgumentException(2, end - args));
    int num_a = as_type<AstTokenNumber>(*args++)->value;
    int num_b = as_type<AstTokenNumber>(*args)->value;

    return std::shared_ptr<AstTokenBool>(new AstTokenBool(num_a <= num_b));
}

std::shared_ptr<AstToken> gtOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 2, ArgumentException(2, end - args));
    int num_a = as_type<AstTokenNumber>(*args++)->value;
    int num_b = as_type<AstTokenNumber>(*args)->value;

    return std::shared_ptr<AstTokenBool>(new AstTokenBool(num_a > num_b));
}

std::shared_ptr<AstToken> gteOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 2, ArgumentException(2, end - args));
    int num_a = as_type<AstTokenNumber>(*args++)->value;
    int num_b = as_type<AstTokenNumber>(*args)->value;

    return std::shared_ptr<AstTokenBool>(new AstTokenBool(num_a >= num_b));
}

std::shared_ptr<AstToken> listOperator(MalArgs args, MalArgs end) {

    return std::shared_ptr<AstTokenList>(new AstTokenList(args, end));

}

std::shared_ptr<AstToken> listqOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    return std::shared_ptr<AstTokenBool>(new AstTokenBool((*args)->type == LIST));
}

std::shared_ptr<AstToken> emptyOperator(MalArgs args, MalArgs end) {

    std::shared_ptr<AstTokenList> list_ast;
    list_ast = as_type<AstTokenList>(*args);

    return std::shared_ptr<AstTokenBool>(new AstTokenBool(list_ast->list.empty()));
}

std::shared_ptr<AstToken> countOperator(MalArgs args, MalArgs end) {

    int size = 0;

    if((*args)->type == NIL)
        return std::shared_ptr<AstTokenNumber>(new AstTokenNumber(0));

    if((*args)->type == LIST || (*args)->type == VECTOR) {

        std::shared_ptr<AstTokenList> list_ast;
        list_ast = as_type<AstTokenList>(*args);
        size = list_ast->list.size();
    } else if((*args)->type == HASH_MAP) {

        std::shared_ptr<AstTokenHashMap> hash_ast;
        hash_ast = as_type<AstTokenHashMap>(*args);
        size = hash_ast->map.size();
    } else {
        throw TokenException(LIST, (*args)->type);
    }

    return std::shared_ptr<AstTokenNumber>(new AstTokenNumber(size));
}

std::shared_ptr<AstToken> prnOperator(MalArgs args, MalArgs end) {

    std::string results;

    if(args != end)
        results = pr_str(*args++, true);

    while(args != end) {
        results += " ";
        results += pr_str(*args++, true);
    }

    std::cout << results << "\n";

    return std::shared_ptr<AstTokenNil>(new AstTokenNil());
}
std::shared_ptr<AstToken> strOperator(MalArgs args, MalArgs end) {

    std::string results;

    while(args != end) {
        results += pr_str(*args++, false);
    }

    return std::shared_ptr<AstTokenString>(new AstTokenString(results));
}

std::shared_ptr<AstToken> prstrOperator(MalArgs args, MalArgs end) {

    std::string results;
    std::string ret;
    std::shared_ptr<AstToken> node;

    if(args == end)
        return std::shared_ptr<AstTokenString>(new AstTokenString(""));

    node = *args++;
    ret = pr_str(node, true);

    results += ret;

    while(args != end) {

        node = *args++;
        ret =  pr_str(node, true);

        results += " ";
        results += ret;
    }

    return std::shared_ptr<AstTokenString>(new AstTokenString(results));
}

std::shared_ptr<AstToken> printlnOperator(MalArgs args, MalArgs end) {

    std::string results;

    if(args != end) {
        results = pr_str(*args++, false);

        while(args != end) {
            results += " ";
            results += pr_str(*args++, false);
        }
    }

    std::cout << results << std::endl;;

    return std::shared_ptr<AstTokenNil>(new AstTokenNil());
}

std::shared_ptr<AstToken> readstrOperator(MalArgs args, MalArgs end) {

    std::string str = as_type<AstTokenString>(*args)->value;

    return read_str(str);
}

std::shared_ptr<AstToken> slurpOperator(MalArgs args, MalArgs end) {

    std::string filename = as_type<AstTokenString>(*args)->value;

    std::ifstream filestream;
    filestream.open(filename);

    std::string str((std::istreambuf_iterator<char>(filestream)),
                    (std::istreambuf_iterator<char>()));

    return std::shared_ptr<AstTokenString>(new AstTokenString(str));
}

std::shared_ptr<AstToken> evalOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    return eval((*args), outer_env);
}

std::shared_ptr<AstToken> atomOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    return std::shared_ptr<AstTokenAtom>(new AstTokenAtom(*args));
}

std::shared_ptr<AstToken> atomqOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    return std::shared_ptr<AstTokenBool>(new AstTokenBool((*args)->type == ATOM));
}

std::shared_ptr<AstToken> derefOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    std::shared_ptr<AstTokenAtom> atom_ast;
    atom_ast = as_type<AstTokenAtom>(*args);

    return atom_ast->object;
}

std::shared_ptr<AstToken> resetOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 2, ArgumentException(2, end - args));

    std::shared_ptr<AstTokenAtom> atom_ast;
    atom_ast = as_type<AstTokenAtom>(*args);
    atom_ast->object = args[1];

    return args[1];
}

std::shared_ptr<AstToken> swapOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args >= 2, ArgumentException(2, end - args));

    std::shared_ptr<AstTokenList> list_ast;
    list_ast = std::shared_ptr<AstTokenList>(new AstTokenList);

    std::shared_ptr<AstTokenAtom> atom_ast;
    atom_ast = as_type<AstTokenAtom>(args[0]);

    list_ast->list.push_back(args[1]);
    list_ast->list.push_back(atom_ast->object);

    for(args = args + 2; args != end; args++){
        list_ast->list.push_back(*args);
    }

    atom_ast->object = eval(list_ast, outer_env);

    return atom_ast->object;
}

std::shared_ptr<AstToken> consOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 2, ArgumentException(2, end - args));

    std::shared_ptr<AstTokenList> list_ast;
    list_ast = std::shared_ptr<AstTokenList>(new AstTokenList);

    list_ast->list.push_back(args[0]);

    std::shared_ptr<AstTokenList> aux_ast;
    aux_ast = as_type<AstTokenList>(args[1]);

    std::copy(std::begin(aux_ast->list), std::end(aux_ast->list), back_inserter(list_ast->list));

    return list_ast;
}

std::shared_ptr<AstToken> concatOperator(MalArgs args, MalArgs end) {

    std::shared_ptr<AstTokenList> list_ast;
    list_ast = std::shared_ptr<AstTokenList>(new AstTokenList);

    for(auto it=args; it != end; it++){

        std::shared_ptr<AstTokenList> aux_ast;
        aux_ast = as_type<AstTokenList>(*it);

        std::copy(std::begin(aux_ast->list), std::end(aux_ast->list), std::back_inserter(list_ast->list));

    }
    return list_ast;
}

std::shared_ptr<AstToken> nthOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 2, ArgumentException(2, end - args));

    std::shared_ptr<AstTokenList> list_ast;

    list_ast = as_type<AstTokenList>(*args++);
    int idx = as_type<AstTokenNumber>(*args)->value;

    if(idx < (int) list_ast->list.size()){
        return list_ast->list[idx];
    }

    throw OutRangeException(idx, list_ast->list.size());
}

std::shared_ptr<AstToken> firstOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    if((*args)->type ==  NIL )
        return std::shared_ptr<AstTokenNil>(new AstTokenNil);

    std::shared_ptr<AstTokenList> list_ast;
    list_ast = as_type<AstTokenList>(*args);

    if(list_ast->list.size() == 0){
        return std::shared_ptr<AstTokenNil>(new AstTokenNil);
    }

    return list_ast->list[0];
}


std::shared_ptr<AstToken> restOperator(MalArgs args, MalArgs end) {

    std::shared_ptr<AstTokenList> new_list_ast(new AstTokenList);

    if((*args)->type == NIL)
        return new_list_ast;

    std::shared_ptr<AstTokenList> list_ast = as_type<AstTokenList>(*args);
    std::copy(std::begin(list_ast->list)+1, std::end(list_ast->list),
                            std::back_inserter(new_list_ast->list));

    return new_list_ast;
}

std::shared_ptr<AstToken> throwOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    std::shared_ptr<AstTokenException> exception(new AstTokenException(args[0]));

    throw exception;
}

std::shared_ptr<AstToken> applyOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args >= 2,  ArgumentException(2, end - args));

    std::shared_ptr<AstToken> ret;
    std::shared_ptr<AstTokenList> list_ast(new AstTokenList());
    std::shared_ptr<AstToken> holder_ast = *args++;

    while(args != end) {
        if((*args)->type == LIST || (*args)->type == VECTOR) {

            std::shared_ptr<AstTokenList> aux_list_ast;
            aux_list_ast = as_type<AstTokenList>(*args);

            for(auto l : aux_list_ast->list){
                list_ast->list.push_back(l);
            }
        } else {
            list_ast->list.push_back(*args);
        }
        args++;
    }

    if(holder_ast->type == FUNCTION){

        std::shared_ptr<AstTokenFunction> fun_ast;
        fun_ast = as_type<AstTokenFunction>(holder_ast);

        std::shared_ptr<MalEnv> new_repl_env = std::shared_ptr<MalEnv>(
                                            new MalEnv(fun_ast->scope));
        new_repl_env->set_bindings(fun_ast->params, fun_ast->larg,
                std::cbegin(list_ast->list), std::cend(list_ast->list));

        ret = eval(fun_ast->function, new_repl_env);

    } else if(holder_ast->type == OPERATOR) {

        std::shared_ptr<AstTokenOperator> op_ast;
        op_ast = as_type<AstTokenOperator>(holder_ast);

        ret = (*op_ast) (std::cbegin(list_ast->list), std::cend(list_ast->list));
    } else {
        throw TokenException(FUNCTION, holder_ast->type);
    }

    return ret;
}

std::shared_ptr<AstToken> mapOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 2, ArgumentException(2, end - args));

    std::shared_ptr<AstTokenList> list_ast;
    std::shared_ptr<AstTokenList> new_list_ast(new AstTokenList);

    if(args[0]->type == FUNCTION) {

        std::shared_ptr<AstTokenFunction> fun_ast;
        fun_ast = as_type<AstTokenFunction>(*args++);

        std::shared_ptr<MalEnv> new_repl_env = std::shared_ptr<MalEnv>(
                                            new MalEnv(fun_ast->scope));

        list_ast = as_type<AstTokenList>(*args);

        for(auto it = std::cbegin(list_ast->list); it != std::cend(list_ast->list); it++) {

            new_repl_env->set_bindings(fun_ast->params, fun_ast->larg, it, it + 1);
            new_list_ast->list.push_back(eval(fun_ast->function, new_repl_env));
        }
    } else if(args[0]->type == OPERATOR) {

        std::shared_ptr<AstTokenOperator> op_ast;
        op_ast = as_type<AstTokenOperator> (*args++);

        list_ast = as_type<AstTokenList>(*args);

        for(auto it = std::cbegin(list_ast->list); it != std::cend(list_ast->list); it++) {
            new_list_ast->list.push_back((*op_ast)(it, it + 1));
        }
    } else {
        throw TokenException(FUNCTION, args[0]->type);
    }

    return new_list_ast;
}

std::shared_ptr<AstToken> symbolqOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    return std::shared_ptr<AstTokenBool> (new AstTokenBool(args[0]->type == SYMBOL));
}

std::shared_ptr<AstToken> falseqOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    if(args[0]->type != BOOL)
        return std::shared_ptr<AstTokenBool> (new AstTokenBool(false));

    std::shared_ptr<AstTokenBool> bool_ast;
    bool_ast = as_type<AstTokenBool>(args[0]);

    return std::shared_ptr<AstTokenBool> (new AstTokenBool(!bool_ast->value));
}

std::shared_ptr<AstToken> trueqOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    if(args[0]->type != BOOL)
        return std::shared_ptr<AstTokenBool> (new AstTokenBool(false));

    std::shared_ptr<AstTokenBool> bool_ast;
    bool_ast = as_type<AstTokenBool>(args[0]);

    return std::shared_ptr<AstTokenBool> (new AstTokenBool(bool_ast->value));
}

std::shared_ptr<AstToken> nilqOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    return std::shared_ptr<AstTokenBool> (new AstTokenBool(args[0]->type == NIL));
}

std::shared_ptr<AstToken> symbolOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    std::shared_ptr<AstTokenString> str_ast;
    str_ast = as_type<AstTokenString>(args[0]);

    return std::shared_ptr<AstTokenSymbol> (new AstTokenSymbol(str_ast->value));
}

std::shared_ptr<AstToken> keywordOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));
    std::string key;

    if(args[0]->type == STRING) {
        std::shared_ptr<AstTokenString> str_ast;
        str_ast = as_type<AstTokenString>(args[0]);
        key = ":" + str_ast->value;

    } else if(args[0]->type == KEYWORD) {
        std::shared_ptr<AstTokenKeyword> key_ast;
        key_ast = as_type<AstTokenKeyword>(args[0]);
        key = key_ast->value;
    }

    return std::shared_ptr<AstTokenKeyword> (new AstTokenKeyword(key));
}

std::shared_ptr<AstToken> keywordqOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    return std::shared_ptr<AstTokenBool> (new AstTokenBool(args[0]->type == KEYWORD));
}

std::shared_ptr<AstToken> vectorOperator(MalArgs args, MalArgs end) {

    return std::shared_ptr<AstTokenVector>(new AstTokenVector(args, end));

}

std::shared_ptr<AstToken> vectorqOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    return std::shared_ptr<AstTokenBool> (new AstTokenBool(args[0]->type == VECTOR));
}


std::shared_ptr<AstToken> sequentialOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    return std::shared_ptr<AstTokenBool> (new AstTokenBool(
                            args[0]->type == VECTOR || args[0]->type == LIST));
}

std::shared_ptr<AstToken> hashmapOperator(MalArgs args, MalArgs end) {

    map_assert((end - args) % 2 == 0,  MapException());

    return std::shared_ptr<AstTokenHashMap> (new AstTokenHashMap(args, end));
}

std::shared_ptr<AstToken> mapqOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    return std::shared_ptr<AstTokenBool> (new AstTokenBool(args[0]->type == HASH_MAP));
}

std::shared_ptr<AstToken> getOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 2, ArgumentException(1, end - args));

    if((*args)->type == NIL)
        return *args;

    std::string str;
    std::shared_ptr<AstTokenHashMap> hash_ast;
    hash_ast = as_type<AstTokenHashMap>(*args++);

    if((*args)->type == STRING) {
        str = as_type<AstTokenString>(*args)->value;
    } else if((*args)->type == KEYWORD) {
        str = as_type<AstTokenKeyword>(*args)->value;
    }

    if(hash_ast->map.find(str) == std::end(hash_ast->map)) {
        return std::shared_ptr<AstTokenNil> (new AstTokenNil);
    }

    return hash_ast->map[str];

}

std::shared_ptr<AstToken> assocOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args >= 1, ArgumentException(1, end - args));

    std::shared_ptr<AstTokenHashMap> hash_ast;
    hash_ast = as_type<AstTokenHashMap>(*args++);

    std::shared_ptr<AstTokenHashMap> new_hash_ast(new AstTokenHashMap);

    for(auto entry : hash_ast->map) {
        new_hash_ast->map[entry.first] = entry.second;
    }

    map_assert((end - args) % 2 == 0,  MapException());

    while(args != end) {

        std::string key;

        if((*args)->type == STRING) {
            key = as_type<AstTokenString>(*args++)->value;
        }else if((*args)->type == KEYWORD) {
            key = as_type<AstTokenKeyword>(*args++)->value;
        }

        new_hash_ast->map[key] = *args++;
    }

    return new_hash_ast;
}

std::shared_ptr<AstToken> dissocOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args >= 1, ArgumentException(1, end - args));

    std::shared_ptr<AstTokenHashMap> hash_ast;
    hash_ast = as_type<AstTokenHashMap> (*args++);

    std::shared_ptr<AstTokenHashMap> new_hash_ast(new AstTokenHashMap);

    for(auto entry : hash_ast->map) {
        new_hash_ast->map[entry.first] = entry.second;
    }

    while(args != end) {

        std::string key;

        if((*args)->type == STRING) {
            key = as_type<AstTokenString>(*args++)->value;
        }else if((*args)->type == KEYWORD) {
            key = as_type<AstTokenKeyword>(*args++)->value;
        }

        new_hash_ast->map.erase(key);
    }
    return new_hash_ast;
}

std::shared_ptr<AstToken> containsqOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 2, ArgumentException(2, end - args));

    std::shared_ptr<AstTokenHashMap> hash_ast;
    hash_ast = as_type<AstTokenHashMap> (*args++);

    std::string key;

    if((*args)->type == STRING) {
        key = as_type<AstTokenString>(*args++)->value;
    }else if((*args)->type == KEYWORD) {
        key = as_type<AstTokenKeyword>(*args++)->value;
    }

    return std::shared_ptr<AstTokenBool> (new AstTokenBool(
                    hash_ast->map.find(key) != std::end(hash_ast->map)));
}

std::shared_ptr<AstToken> keysOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    std::shared_ptr<AstTokenHashMap> hash_ast;
    hash_ast = as_type<AstTokenHashMap> (args[0]);

    std::shared_ptr<AstTokenList> list_ast(new AstTokenList);

    for(auto const& entry : hash_ast->map) {

        if(entry.first[0] == '\xff') {
            list_ast->list.push_back(std::shared_ptr<AstTokenKeyword>(new AstTokenKeyword(entry.first.substr(1))));
        } else {
            list_ast->list.push_back(std::shared_ptr<AstTokenString>(new AstTokenString(entry.first)));
        }
    }
    return list_ast;
}

std::shared_ptr<AstToken> valsOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    std::shared_ptr<AstTokenHashMap> hash_ast;
    hash_ast = as_type<AstTokenHashMap> (args[0]);

    std::shared_ptr<AstTokenList> list_ast(new AstTokenList);

    for(auto& entry : hash_ast->map) {

        list_ast->list.push_back(entry.second);
    }
    return list_ast;
}

std::shared_ptr<AstToken> readlineOperator(MalArgs args, MalArgs end) {

    arg_assert(end - args == 1, ArgumentException(1, end - args));

    std::shared_ptr<AstTokenString> str_ast;
    str_ast = as_type<AstTokenString> (args[0]);

    std::string input;

    std::cout << str_ast->value;
    std::cin >> input;

    std::shared_ptr<AstTokenString> input_ast(new AstTokenString(input));

    return input_ast;
}


#include"Core.h"

void start_outer_env(MalEnv & repl_env) {

   repl_env.set("+", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&addOperator))));
    repl_env.set("-", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&subOperator))));
    repl_env.set("*", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&mulOperator))));
    repl_env.set("/", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&divOperator))));
    repl_env.set("=", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&eqOperator))));
    repl_env.set(">", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&gtOperator))));
    repl_env.set(">=", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&gteOperator))));
    repl_env.set("<", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&ltOperator))));
    repl_env.set("<=", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&lteOperator))));
    repl_env.set("list", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&listOperator))));
    repl_env.set("list?", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&listqOperator))));
    repl_env.set("empty?", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&emptyOperator))));
    repl_env.set("count", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&countOperator))));
    repl_env.set("prn", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&prnOperator))));
    repl_env.set("str", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&strOperator))));
    repl_env.set("pr-str", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&prstrOperator))));
    repl_env.set("println", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&printlnOperator))));
    repl_env.set("read-string", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&readstrOperator))));
    repl_env.set("slurp", std::static_pointer_cast<AstToken>(
                std::shared_ptr<AstTokenOperator>(new AstTokenOperator(&slurpOperator))));
    return;
}

std::shared_ptr<AstToken> addOperator(MalArgs args, MalArgs end) {

    check_arguments(end - args != 2, "2", std::to_string(end - args));
    int num_a = std::static_pointer_cast<AstTokenNumber>(*args++)->value;
    int num_b = std::static_pointer_cast<AstTokenNumber>(*args)->value;

    return std::shared_ptr<AstTokenNumber>(new AstTokenNumber(num_a + num_b));
}

std::shared_ptr<AstToken> subOperator(MalArgs args, MalArgs end) {

    check_arguments(end - args != 2, "2", std::to_string(end - args));
    int num_a = std::static_pointer_cast<AstTokenNumber>(*args++)->value;
    int num_b = std::static_pointer_cast<AstTokenNumber>(*args)->value;

    return std::shared_ptr<AstTokenNumber>(new AstTokenNumber(num_a - num_b)); }

std::shared_ptr<AstToken> mulOperator(MalArgs args, MalArgs end) {

    check_arguments(end - args != 2, "2", std::to_string(end - args));
    int num_a = std::static_pointer_cast<AstTokenNumber>(*args++)->value;
    int num_b = std::static_pointer_cast<AstTokenNumber>(*args)->value;

    return std::shared_ptr<AstTokenNumber>(new AstTokenNumber(num_a * num_b));
}

std::shared_ptr<AstToken> divOperator(MalArgs args, MalArgs end) {

    check_arguments(end - args != 2, "2", std::to_string(end - args));
    int num_a = std::static_pointer_cast<AstTokenNumber>(*args++)->value;
    int num_b = std::static_pointer_cast<AstTokenNumber>(*args)->value;

    return std::shared_ptr<AstTokenNumber>(new AstTokenNumber(num_a / num_b));
}


bool equal(std::shared_ptr<AstToken> a, std::shared_ptr<AstToken> b) {

    if(a->type == NIL && b->type == NIL) {

        return true;

    }else if(a->type == NUMBER && b->type == NUMBER) {

        int num_a = std::static_pointer_cast<AstTokenNumber>(a)->value;
        int num_b = std::static_pointer_cast<AstTokenNumber>(b)->value;

        return num_a == num_b;

    }else if(a->type == BOOL && b->type == BOOL) {

        bool ba = std::static_pointer_cast<AstTokenBool>(a)->value;
        bool bb = std::static_pointer_cast<AstTokenBool>(b)->value;

        return ba == bb;

    }else if(a->type == STRING && b->type == STRING) {

        std::string string_a = std::static_pointer_cast<AstTokenString>(a)->value;
        std::string string_b = std::static_pointer_cast<AstTokenString>(b)->value;

        return string_a.compare(string_b) == 0;

    }else if(a->type == KEYWORD && b->type == KEYWORD) {

        std::string keyword_a = std::static_pointer_cast<AstTokenKeyword>(a)->value;
        std::string keyword_b = std::static_pointer_cast<AstTokenKeyword>(b)->value;

        return keyword_a.compare(keyword_b) == 0;

    }else if((a->type == LIST || a->type == VECTOR) && (b->type == LIST || b->type == VECTOR)) {

        std::shared_ptr<AstTokenList>list_a;
        std::shared_ptr<AstTokenList>list_b;

        list_a = std::static_pointer_cast<AstTokenList>(a);
        list_b = std::static_pointer_cast<AstTokenList>(b);

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
    }else if(a->type != b->type) {
        return false;
    }

    unimplemented_comparison(a->type, b->type);
    return false;
}

std::shared_ptr<AstToken> eqOperator(MalArgs args, MalArgs end) {

    check_arguments(end - args != 2, "2", std::to_string(end - args));

    std::shared_ptr<AstToken> a = (*args++);
    std::shared_ptr<AstToken> b = (*args);

    return std::static_pointer_cast<AstToken>(std::shared_ptr<AstTokenBool>(new AstTokenBool(equal(a, b))));
}

std::shared_ptr<AstToken> ltOperator(MalArgs args, MalArgs end) {

    check_arguments(end - args != 2, "2", std::to_string(end - args));
    int num_a = std::static_pointer_cast<AstTokenNumber>(*args++)->value;
    int num_b = std::static_pointer_cast<AstTokenNumber>(*args)->value;

    return std::shared_ptr<AstTokenBool>(new AstTokenBool(num_a < num_b));
}

std::shared_ptr<AstToken> lteOperator(MalArgs args, MalArgs end) {

    check_arguments(end - args != 2, "2", std::to_string(end - args));
    int num_a = std::static_pointer_cast<AstTokenNumber>(*args++)->value;
    int num_b = std::static_pointer_cast<AstTokenNumber>(*args)->value;

    return std::shared_ptr<AstTokenBool>(new AstTokenBool(num_a <= num_b));
}

std::shared_ptr<AstToken> gtOperator(MalArgs args, MalArgs end) {

    check_arguments(end - args != 2, "2", std::to_string(end - args));
    int num_a = std::static_pointer_cast<AstTokenNumber>(*args++)->value;
    int num_b = std::static_pointer_cast<AstTokenNumber>(*args)->value;

    return std::shared_ptr<AstTokenBool>(new AstTokenBool(num_a > num_b));
}

std::shared_ptr<AstToken> gteOperator(MalArgs args, MalArgs end) {

    check_arguments(end - args != 2, "2", std::to_string(end - args));
    int num_a = std::static_pointer_cast<AstTokenNumber>(*args++)->value;
    int num_b = std::static_pointer_cast<AstTokenNumber>(*args)->value;

    return std::shared_ptr<AstTokenBool>(new AstTokenBool(num_a >= num_b));
}

std::shared_ptr<AstToken> listOperator(MalArgs args, MalArgs end) {

    return std::shared_ptr<AstTokenList>(new AstTokenList(args, end));

}

std::shared_ptr<AstToken> listqOperator(MalArgs args, MalArgs end) {

    check_arguments(end - args != 1, "1", std::to_string(end - args));

    return std::shared_ptr<AstTokenBool>(new AstTokenBool((*args)->type == LIST));
}

std::shared_ptr<AstToken> emptyOperator(MalArgs args, MalArgs end) {

    check_token((*args)->type != LIST && (*args)->type != VECTOR, LIST,
            (*args)->type);
    std::shared_ptr<AstTokenList> list_ast;
    list_ast = std::static_pointer_cast<AstTokenList>(*args);


    return std::shared_ptr<AstTokenBool>(new AstTokenBool(list_ast->list.empty()));

}

std::shared_ptr<AstToken> countOperator(MalArgs args, MalArgs end) {

    check_token((*args)->type != LIST && (*args)->type != VECTOR && (*args)->type != NIL,
            LIST, (*args)->type);

    if((*args)->type == NIL)
        return std::shared_ptr<AstTokenNumber>(new AstTokenNumber(0));

    std::shared_ptr<AstTokenList> list_ast;
    list_ast = std::static_pointer_cast<AstTokenList>(*args);

    return std::shared_ptr<AstTokenNumber>(new AstTokenNumber(list_ast->list.size()));

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

    return std::static_pointer_cast<AstToken>(std::shared_ptr<AstTokenNil>(new AstTokenNil()));
}
std::shared_ptr<AstToken> strOperator(MalArgs args, MalArgs end) {

    std::string results;

    while(args != end) {
        results += pr_str(*args++, false);
    }

    return std::static_pointer_cast<AstToken>(std::shared_ptr<AstTokenString>(new AstTokenString(results)));
}

std::shared_ptr<AstToken> prstrOperator(MalArgs args, MalArgs end) {

    std::string results;
    std::string ret;
    std::shared_ptr<AstToken> node;

    if(args == end)
        return std::static_pointer_cast<AstToken>(std::shared_ptr<AstTokenString>(new AstTokenString("")));

    node = *args++;
    ret = pr_str(node, true);

    results += ret;

    while(args != end) {

        node = *args++;
        ret =  pr_str(node, true);

        results += " ";
        results += ret;
    }

    return std::static_pointer_cast<AstToken>(std::shared_ptr<AstTokenString>(new AstTokenString(results)));
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

    return std::static_pointer_cast<AstToken>(std::shared_ptr<AstTokenNil>(new AstTokenNil()));
}

std::shared_ptr<AstToken> readstrOperator(MalArgs args, MalArgs end) {

    check_token((*args)->type != STRING, STRING, (*args)->type);
    std::string str = std::static_pointer_cast<AstTokenString>(*args)->value;

    return read_str(str);
}

std::shared_ptr<AstToken> slurpOperator(MalArgs args, MalArgs end) {

    check_token((*args)->type != STRING, STRING, (*args)->type);
    std::string filename = std::static_pointer_cast<AstTokenString>(*args)->value;

    std::ifstream filestream;
    filestream.open(filename);

    std::string str((std::istreambuf_iterator<char>(filestream)),
                    (std::istreambuf_iterator<char>()));

    return std::static_pointer_cast<AstToken>(std::shared_ptr<AstTokenString>(new AstTokenString(str)));
}


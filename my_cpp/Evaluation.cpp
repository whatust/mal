#include"Evaluation.h"

std::shared_ptr<MalToken> eval_ast (std::shared_ptr<MalToken> ast, MalEnv& repl_env) {

    std::shared_ptr<MalToken> ret;

    switch (ast->type) {
        case SYMBOL: {
            std::string symbol;
            std::shared_ptr<MalTokenSymbol> symbol_ast;

            symbol_ast = static_pointer_cast<MalTokenSymbol> (ast);
            symbol = symbol_ast->name;

            check_valid_symbol(repl_env.find(symbol) == std::end(repl_env), "Unknown symbol: %s", symbol);

            ret = std::shared_ptr<MalToken>(new MalTokenOperator(symbol, repl_env));
            break;
        }
        case LIST: {
            std::shared_ptr<MalTokenList> list_ast;
            list_ast = static_pointer_cast<MalTokenList> (ast);
            std::shared_ptr<MalTokenList> new_list_ast(new MalTokenList(list_ast->close_char));

            for (auto token : list_ast->list) {
                new_list_ast->list.push_back(eval(token, repl_env));
            }
            ret = std::static_pointer_cast<MalToken>(new_list_ast);
            break;
        }
        default: {
            ret = ast;
        }
    }
    return ret;
}

std::shared_ptr<MalToken> eval(std::shared_ptr<MalToken> ast, MalEnv& repl_env) {

    std::shared_ptr<MalToken> ret;

    switch (ast->type) {
        case LIST: {
            std::shared_ptr<MalTokenList> list_ast;
            list_ast = static_pointer_cast<MalTokenList> (eval_ast(ast, repl_env));

            if (list_ast->list.empty()) {
                ret = ast;
                break;
            }

            check_token (list_ast->list[0]->type != OPERATOR,
                    "Expected token type OPERATOR got: %s", list_ast->list[0]->type);
            std::shared_ptr<MalTokenOperator> opToken;

            opToken = std::static_pointer_cast<MalTokenOperator>(eval(list_ast->list[0], repl_env));
            ret = opToken->op(++(std::cbegin(list_ast->list)));

            break;
       }
        default:
            ret = eval_ast(ast, repl_env);
    }
    return ret;
}


std::shared_ptr<MalToken> addFunction(std::vector<std::shared_ptr<MalToken>>::const_iterator args) {

    int num_a = std::static_pointer_cast<MalTokenNumber>(*args++)->value;
    int num_b = std::static_pointer_cast<MalTokenNumber>(*args)->value;

    return std::shared_ptr<MalTokenNumber>(new MalTokenNumber(num_a + num_b));
}

std::shared_ptr<MalToken> subFunction(std::vector<std::shared_ptr<MalToken>>::const_iterator args) {

    int num_a = std::static_pointer_cast<MalTokenNumber>(*args++)->value;
    int num_b = std::static_pointer_cast<MalTokenNumber>(*args)->value;

    return std::shared_ptr<MalTokenNumber>(new MalTokenNumber(num_a - num_b));
}

std::shared_ptr<MalToken> mulFunction(std::vector<std::shared_ptr<MalToken>>::const_iterator args) {

    int num_a = std::static_pointer_cast<MalTokenNumber>(*args++)->value;
    int num_b = std::static_pointer_cast<MalTokenNumber>(*args)->value;

    return std::shared_ptr<MalTokenNumber>(new MalTokenNumber(num_a * num_b));
}

std::shared_ptr<MalToken> divFunction(std::vector<std::shared_ptr<MalToken>>::const_iterator args) {

    int num_a = std::static_pointer_cast<MalTokenNumber>(*args++)->value;
    int num_b = std::static_pointer_cast<MalTokenNumber>(*args)->value;

    return std::shared_ptr<MalTokenNumber>(new MalTokenNumber(num_a / num_b));
}

#include<iostream>
#include<string>
#include"ReadLine.h"
#include"Reader.h"
#include"Types.h"
#include"Printer.h"
#include"Validation.h"
#include"Evaluation.h"
#include"Core.h"

std::string rep(const std::string& input, MalEnv& repl_env);
std::shared_ptr<AstToken> READ(const std::string& input);
std::shared_ptr<AstToken> EVAL(std::shared_ptr<AstToken> ast, MalEnv& repl_env);
std::string PRINT(std::shared_ptr<AstToken> ast);

static ReadLine readLine("~/.cache/mymal/");

int main(int argc, char* argv[]) {

    std::string prompt = "user> ";
    std::string input;

    MalEnv repl_env;
    start_outer_env(repl_env);

    while(readLine.read(prompt, input)) {

        std::string out;

        try {
            out = rep(input, repl_env);
        }
        catch(EmptyInput&) {
            continue;
        }
        catch(std::string& error) {
            std::cerr << error << std::endl;
            continue;
        }
        std::cout << out << std::endl;
    }
    return 0;
}

std::string rep(const std::string& input, MalEnv& repl_env) {
        return PRINT(EVAL(READ(input), repl_env));
}

std::shared_ptr<AstToken> READ(const std::string& input) {
    return read_str(input);
}

std::shared_ptr<AstToken> EVAL(std::shared_ptr<AstToken> ast, MalEnv& repl_env) {
    return eval(ast,repl_env);
}

std::string PRINT(std::shared_ptr<AstToken> ast) {
    return pr_str(ast, true);
}


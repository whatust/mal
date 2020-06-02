#include<iostream>
#include<string>
#include"ReadLine.h"
#include"Reader.h"
#include"Types.h"
#include"Printer.h"
#include"Validation.h"
#include"Evaluation.h"

std::string rep(const std::string& input, MalEnv& repl_env);
std::shared_ptr<MalToken> READ(const std::string& input);
std::shared_ptr<MalToken> EVAL(std::shared_ptr<MalToken> ast, MalEnv& repl_env);
std::string PRINT(std::shared_ptr<MalToken> ast);

static ReadLine readLine("~/.cache/mymal/");

int main(int argc, char* argv[]) {

    std::string prompt = "user> ";
    std::string input;

    MalEnv repl_env;
    repl_env.insert(std::make_pair<std::string, MalFunction>("+", &addFunction));
    repl_env.insert(std::make_pair<std::string, MalFunction>("-", &subFunction));
    repl_env.insert(std::make_pair<std::string, MalFunction>("*", &mulFunction));
    repl_env.insert(std::make_pair<std::string, MalFunction>("/", &divFunction));

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

std::shared_ptr<MalToken> READ(const std::string& input) {
    return read_str(input);
}

std::shared_ptr<MalToken> EVAL(std::shared_ptr<MalToken> ast, MalEnv& repl_env) {
    return eval(ast,repl_env);
}

std::string PRINT(std::shared_ptr<MalToken> ast) {
    return pr_str(ast);
}


#include<iostream>
#include<string>
#include"ReadLine.h"
#include"Reader.h"
#include"Types.h"
#include"Printer.h"
#include"Validation.h"

std::string rep(const std::string& input);
std::shared_ptr<AstToken> READ(const std::string& input);
std::shared_ptr<AstToken> EVAL(std::shared_ptr<AstToken> ast);
std::string PRINT(std::shared_ptr<AstToken> ast);

static ReadLine readLine("~/.cache/mymal/");

int main(int argc, char* argv[]) {

    std::string prompt = "user> ";
    std::string input;

        while(readLine.read(prompt, input)) {

            std::string out;

            try {
                out = rep(input);
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

std::string rep(const std::string& input) {
        return PRINT(EVAL(READ(input)));
}

std::shared_ptr<AstToken> READ(const std::string& input) {
    return read_str(input);
}

std::shared_ptr<AstToken> EVAL(std::shared_ptr<AstToken> ast) {
    return ast;
}

std::string PRINT(std::shared_ptr<AstToken> ast) {
    return pr_str(ast, false);
}


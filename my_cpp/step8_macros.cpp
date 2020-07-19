#include<iostream>
#include<string>
#include"ReadLine.h"
#include"Reader.h"
#include"Types.h"
#include"Printer.h"
#include"Validation.h"
#include"Evaluation.h"
#include"Core.h"

std::string rep(const std::string& input, std::shared_ptr<MalEnv> repl_env);
std::shared_ptr<AstToken> READ(const std::string& input);
std::shared_ptr<AstToken> EVAL(std::shared_ptr<AstToken> ast, std::shared_ptr<MalEnv> repl_env);
std::string PRINT(std::shared_ptr<AstToken> ast);

static ReadLine readLine("~/.cache/mymal/");

int main(int argc, char* argv[]) {

    std::string prompt = "user> ";
    std::string input;
    std::string args;
    std::string filename;

    std::shared_ptr<MalEnv> repl_env(new MalEnv(nullptr));
    start_outer_env(repl_env);

    if(argc > 1) { filename = argv[1]; }
    for(int i=2; i < argc; i++) { args += "\""; args += argv[i]; args += "\""; }

    rep(std::string("(def! not(fn* (a) (if a false true)))"), repl_env);
    rep(std::string("(def! load-file (fn* (f) (eval (read-string (str \"(do \" (slurp f) \"\nnil)\")))))"), repl_env);
    rep(std::string("(def! *ARGV*(" + args + "))"), repl_env);
    rep(std::string("(defmacro! cond (fn* (& xs) (if (> (count xs) 0) (list 'if (first xs) (if (> (count xs) 1) (nth xs 1) (throw \"odd number of forms to cond\")) (cons 'cond (rest (rest xs)))))))"), repl_env);

    if(filename.compare("") != 0) {
        rep(std::string("(load-file \"" + filename + "\")"), repl_env);
    } else {
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
            catch(TokenException& error){
                std::cerr << error.what() << std::endl;
                continue;
            }
            catch(ArgumentException& error){
                std::cerr << error.what() << std::endl;
                continue;
            }
            catch(SymException& error){
                std::cerr << error.what() << std::endl;
                continue;
            }
            catch(std::exception& error){
                std::cerr << error.what() << std::endl;
                continue;
            }
            std::cout << out << std::endl;
        }
    }
    return 0;
}

std::string rep(const std::string& input, std::shared_ptr<MalEnv>repl_env) {
        return PRINT(EVAL(READ(input), repl_env));
}

std::shared_ptr<AstToken> READ(const std::string& input) {
    //std::cout << pr_str(read_str(input), true) << std::endl;
    return read_str(input);
}

std::shared_ptr<AstToken> EVAL(std::shared_ptr<AstToken> ast, std::shared_ptr<MalEnv> repl_env) {
    return eval(ast,repl_env);
}

std::string PRINT(std::shared_ptr<AstToken> ast) {
    return pr_str(ast, true);
}


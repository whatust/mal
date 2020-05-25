#include<iostream>
#include<string>

#include"ReadLine.h"
#include"Reader.h"
#include"Types.h"
#include"Printer.h"

using std::cout;
using std::endl;
using std::string;

string rep(const string& input);
shared_ptr<MalToken> READ(const string& input);
shared_ptr<MalToken> EVAL(shared_ptr<MalToken> ast);
string PRINT(shared_ptr<MalToken> ast);

static ReadLine readLine("~/.cache/mymal/");

int main(int argc, char* argv[]) {

        string prompt = "> ";
        string input;

        while(readLine.read(prompt, input)) {

            string ret = rep(input);
            cout << ret;

            if(ret != "")
                cout << endl;

        }
        return 0;
}

string rep(const string& input) {
        return PRINT(EVAL(READ(input)));
}

shared_ptr<MalToken> READ(const string& input) {
    return read_str(input);
}

shared_ptr<MalToken> EVAL(shared_ptr<MalToken> ast) {
    return ast;
}

string PRINT(shared_ptr<MalToken> ast) {
    return pr_str(ast);
}


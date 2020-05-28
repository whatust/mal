#include<iostream>
#include<string>

#include"ReadLine.h"

using std::cout;
using std::endl;
using std::string;

string rep(const string& input);
string READ(const string& input);
string EVAL(const string& ast);
string PRINT(const string& ast);

static ReadLine readLine("/home/whatust/.cache/mymal/");

int main(int argc, char* argv[]) {

    string prompt = "user> ";
    string input;

    while(readLine.read(prompt, input)) {
        cout << rep(input) << '\n';
    }
    return 0;
}

string rep(const string& input) {
    return PRINT(EVAL(READ(input)));
}

string READ(const string& input) {
    return input;
}

string EVAL(const string& ast) {
    return ast;
}

string PRINT(const string& ast) {
    return ast;
}


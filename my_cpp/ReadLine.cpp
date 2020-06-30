#include"ReadLine.h"
#include<filesystem>
#include<readline/readline.h>
#include<readline/history.h>
#include<readline/tilde.h>
#include<iostream>

namespace fs = std::filesystem;

ReadLine::ReadLine(const std::string& cache_folder)
: hist_path(tilde_expand((cache_folder+"history").c_str())) {
        fs::create_directory(tilde_expand(cache_folder.c_str()));
        read_history(hist_path.c_str());
        write_history(hist_path.c_str());
        stifle_history(1000);
}

ReadLine::~ReadLine() {
        write_history(hist_path.c_str());
}

bool ReadLine::read(const std::string& prompt, std::string& input) {

        char * line = readline(prompt.c_str());
        if(line == nullptr)
                return false;
        add_history(line);

        input = line;
        return true;
}


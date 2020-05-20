#include"ReadLine.h"
#include<experimental/filesystem>
#include<readline/readline.h>
#include<readline/history.h>
#include<readline/tilde.h>

//namespace fs = std::filesystem;

ReadLine::ReadLine(const string& cache_folder)
: hist_path(tilde_expand(cache_folder.c_str())) {
        //fs::create_directory(cache_folder);
        read_history(hist_path.c_str());
}

ReadLine::~ReadLine() {}

bool ReadLine::read(const string& prompt, string& input) {

        char * line = readline(prompt.c_str());
        if(line == nullptr)
                return false;
        add_history(line);
        append_history(1, hist_path.c_str());
        input = line;
        return true;
}


#ifndef READLINE_H_
#define READLINE_H_

#include<filesystem>
#include<readline/readline.h>
#include<readline/history.h>
#include<readline/tilde.h>
#include<iostream>
#include<string>

class ReadLine {
    public:
        ReadLine(const std::string& cache_directory);
        ~ReadLine();
        bool read(const std::string& prompt, std::string& line);

    private:
        std::string hist_path;
};

#endif  // REDLINE_H_

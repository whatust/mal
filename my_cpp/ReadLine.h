#ifndef READLINE_H_
#define READLINE_H_

#include<string>

using std::string;

class ReadLine {
        public:
                ReadLine(const string& cache_directory);
                ~ReadLine();
                bool read(const string& prompt, string& line);

        private:
                string hist_path;
};

#endif  // REDLINE_H_

#pragma once
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


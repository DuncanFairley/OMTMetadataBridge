#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <string>
#include <fstream>

#define INFO 1
#define WARN 2
#define ERROR 3
#define DEBUG 4


class Logging
{
    public:
        Logging(unsigned int level, const std::string& filename);
        ~Logging();
        void Log(unsigned int type, const std::string& msg);
        void setLogLevel(unsigned int level);
    private:
        unsigned int level;
        std::string whatLevel(unsigned int level);
        std::string Now();
        std::ofstream logstream;
};

#endif // LOGGING_HPP

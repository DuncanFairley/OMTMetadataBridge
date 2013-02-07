#include "Logging.hpp"
#include <iostream>

Logging::Logging(unsigned int level, const std::string& filename)
{
    logstream.open(filename.c_str(), std::ofstream::out | std::ofstream::app);
    setLogLevel(level);
}
Logging::~Logging()
{
    logstream.close();
}
void Logging::setLogLevel(unsigned int level)
{
    this->level = level;
}
std::string Logging::whatLevel(unsigned int level)
{
    switch(level)
    {
        case INFO: return "Info";
        case WARN: return "Warn";
        case ERROR: return "Error";
        case DEBUG: return "Debug";
    }
    return "";
}
std::string Logging::Now()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    strftime (buffer,80,"%d/%b/%Y %I:%M%p",timeinfo);
    return buffer;
}
void Logging::Log(unsigned int type, const std::string& msg)
{
    if(type <= level)
    {
        logstream << "(" <<whatLevel(type) << ") " << Now() <<": " << msg << "\n";
    }
    else
        std::cout << "Don't log it";
}

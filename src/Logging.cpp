#include "Logging.hpp"
#include <iostream>


using boost::property_tree::ptree;

void Logging::init()
{
    setLogLevel(configtree.get("config.logging.level", 1));//Defaults to INFO if not present in config
    setLogFile(configtree.get("config.logging.file","log.log")); //Defaults to log.log
}

void Logging::setLogFile(const std::string& filename)
{
    if(logstream.is_open())
        logstream.close();
    logstream.open(filename.c_str(), std::ofstream::out | std::ofstream::app);
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

    strftime (buffer,80,"%d/%b/%Y %I:%M:%S%p",timeinfo);
    return buffer;
}
void Logging::Log(unsigned int type, const std::string& msg)
{
    if(type <= level)
    {
        logstream << "(" <<whatLevel(type) << ") " << Now() <<": " << msg << "\n";
    }
    logstream.flush();
}

#ifndef STATION_HPP
#define STATION_HPP
#include <vector>
#include <string>

class Station
{
    public:
        Station(const unsigned short port);
        bool hasCategory(const std::string& category);
        void addCategory(const std::string& category);
    private:
        const unsigned short port;
        std::vector<std::string> music_categories;
};


#endif // STATION_HPP

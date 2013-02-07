#ifndef STATION_HPP
#define STATION_HPP
#include <vector>
#include <string>

class Station
{
    public:
        Station(const unsigned short port, const std::string mountpoint);
        bool hasCategory(const std::string& category);
        void addCategory(const std::string category);
        const unsigned short port;
        const std::string mountpoint;
    private:
        std::vector<std::string> music_categories;
};


#endif // STATION_HPP

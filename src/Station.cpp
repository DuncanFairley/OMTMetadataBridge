#include "Station.hpp"
#include <algorithm>

Station::Station(const unsigned short port) : port(port)
{
    music_categories.push_back("test");
}
void Station::addCategory(const std::string& category)
{
    music_categories.push_back(category);
}
bool Station::hasCategory(const std::string& category)
{
    return (std::find(music_categories.begin(), music_categories.end(), category) != music_categories.end());
}

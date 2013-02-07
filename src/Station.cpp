#include "Station.hpp"
#include <algorithm>

Station::Station(boost::asio::io_service& io_service, const unsigned short port, const std::string mountpoint) : socket_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), port(port), mountpoint(mountpoint)
{
    music_categories.push_back("test");
}
void Station::addCategory(const std::string category)
{
    music_categories.push_back(category);
}
bool Station::hasCategory(const std::string& category)
{
    return (std::find(music_categories.begin(), music_categories.end(), category) != music_categories.end());
}

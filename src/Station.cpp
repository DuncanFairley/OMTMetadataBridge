#include "Station.hpp"
#include <algorithm>

Station::Station(boost::asio::io_service& io_service, const unsigned short port, const std::string mountpoint) : socket_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), port(port), mountpoint(mountpoint)
{
    //music_categories.push_back("test");
    start_receive();
}
void Station::start_receive()
{
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), remote_endpoint_,
        boost::bind(&Station::receive_handler, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}
void Station::receive_handler(const boost::system::error_code& error, std::size_t)
{
    if (!error || error == boost::asio::error::message_size)
    {
        std::cout << "Received data on " << port << std::endl;
        start_receive();
    }
}
void Station::addCategory(const std::string category)
{
    music_categories.push_back(category);
}
bool Station::hasCategory(const std::string& category)
{
    return (std::find(music_categories.begin(), music_categories.end(), category) != music_categories.end());
}

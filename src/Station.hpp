#ifndef STATION_HPP
#define STATION_HPP
#include "Logging.hpp"
#include <vector>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#define max_buffer 1024
class Station
{
    private:
        std::vector<std::string> music_categories;
        boost::asio::ip::udp::socket socket_;
        boost::asio::ip::udp::endpoint remote_endpoint_;
        char data_[max_buffer];
        void start_receive();
        void receive_handler(const boost::system::error_code& error, std::size_t);
    public:
        Station(boost::asio::io_service& io_service, const unsigned short port, const std::string mountpoint);
        bool hasCategory(const std::string& category);
        void addCategory(const std::string category);
        const unsigned short port;
        const std::string mountpoint;
};


#endif // STATION_HPP

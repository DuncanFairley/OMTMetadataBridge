#ifndef SONG_HPP
#define SONG_HPP
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/asio.hpp>
class Song
{
    public:
        Song(boost::asio::io_service& io_service, boost::property_tree::ptree& Entry);
        void updateIcecast(std::string& mountpoint, std::string& icecastAdminUser, std::string& icecastAdminPassword);
    private:

        std::string Title;
        std::string Artist;
        std::string Album;
        unsigned int Duration;
        std::string StartTime;

        boost::asio::ip::tcp::resolver resolver_;
        boost::asio::ip::tcp::socket socket_;
        boost::asio::streambuf request_;
        boost::asio::streambuf response_;
};

#endif // SONG_HPP

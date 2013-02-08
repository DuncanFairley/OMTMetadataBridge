#include "Station.hpp"
#include "Logging.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <algorithm>

using boost::property_tree::ptree;

Station::Station(boost::asio::io_service& io_service, const unsigned short port, const std::string mountpoint) : socket_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), port(port), mountpoint(mountpoint)
{
    //music_categories.push_back("test");
    start_receive();
}
void Station::start_receive()
{
    socket_.async_receive_from(
        boost::asio::buffer(rec_data, max_buffer), remote_endpoint_,
        boost::bind(&Station::receive_handler, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}
void Station::parse_data(std::stringstream& data_stream)
{
    ptree playlist;
    read_xml(data_stream, playlist);
    BOOST_FOREACH(ptree::value_type &Entry, playlist.get_child("PlayList"))
    {
        if(Entry.second.get<std::string>("<xmlattr>.Type") == "Playing")
            std::cout << "Type is Playing" << std::endl;
        if(hasCategory(Entry.second.get<std::string>("<xmlattr>.Category")))
            std:: cout << "Has category: " << Entry.second.get<std::string>("<xmlattr>.Category") << std::endl;
    }
}
void Station::receive_handler(const boost::system::error_code& error, std::size_t reclen)
{
    if (!error || error == boost::asio::error::message_size)
    {
        rec_data[std::min(max_buffer,(int)reclen)] = '\0';//Don't null terminate somewhere above the buffer size
        if(reclen >= max_buffer)
            Logger.Log(WARN,"Recieved data exceeding max length.");
        std::stringstream data_stream;
        data_stream << rec_data;
        parse_data(data_stream);
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

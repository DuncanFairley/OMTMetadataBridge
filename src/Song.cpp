#include "Song.hpp"
#include <boost/bind.hpp>

using boost::asio::ip::tcp;
using boost::property_tree::ptree;


Song::Song(boost::asio::io_service& io_service, ptree& Entry) : resolver_(io_service),socket_(io_service)
{
    Artist = Entry.get<std::string>("Artist");
    Title = Entry.get<std::string>("Title");
    Album = Entry.get<std::string>("Album");
    Duration = Entry.get<unsigned int>("Duration");
    StartTime = Entry.get<std::string>("StartTime");
}
std::string urlencode(const std::string &s)
{
    const std::string unreserved = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_.~";

    std::string escaped="";
    for(size_t i=0; i<s.length(); i++)
    {
        if (unreserved.find_first_of(s[i]) != std::string::npos)
        {
            escaped.push_back(s[i]);
        }
        else
        {
            escaped.append("%");
            char buf[3];
            sprintf(buf, "%.2X", s[i]);
            escaped.append(buf);
        }
    }
    return escaped;
}
void Song::updateIcecast(std::string& mountpoint)
{
    std::ostream request_stream(&request_);
    request_stream << "GET " << "/admin/metadata?song=" << urlencode(Title+" - "+Artist) << "&mount=" << mountpoint << "&mode=updinfo HTTP/1.0\r\n";
    request_stream << "Host: " << "hotdogradio.com:8000" << "\r\n";
    request_stream << "Authorization: Basic " <<
    request_stream << "Accept: */*\r\n";
    request_stream << "Connection: close\r\n\r\n";
    //Todo continue with http://www.boost.org/doc/libs/1_47_0/doc/html/boost_asio/example/http/client/async_client.cpp
}

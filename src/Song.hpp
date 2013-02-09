#ifndef SONG_HPP
#define SONG_HPP
#include <string>
#include <boost/property_tree/ptree.hpp>

class Song
{
    public:
        Song(boost::property_tree::ptree& Entry);
    private:
        std::string Title;
        std::string Artist;
        std::string Album;
        unsigned int Duration;
        std::string StartTime;
};

#endif // SONG_HPP

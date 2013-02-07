#ifndef SONG_HPP
#define SONG_HPP
#include <string>
#include "Station.hpp"

class Song
{
    public:
        std::string Title;
        std::string Artist;
        unsigned int StartTime;
        Song(const std::string& XmlData, Station& Station);

};
#endif // SONG_HPP

#include "Song.hpp"

using boost::property_tree::ptree;

Song::Song(ptree& Entry)
{
    Artist = Entry.get<std::string>("Artist");
    Title = Entry.get<std::string>("Title");
    Album = Entry.get<std::string>("Album");
    Duration = Entry.get<unsigned int>("Duration");
    StartTime = Entry.get<std::string>("StartTime");
    std::cout << "Artist: " << Artist << std::endl;
    std::cout << "Title: " << Title << std::endl;
    std::cout << "Album: " << Album << std::endl;
    std::cout << "Duration: " << Duration+1 << std::endl;
    std::cout << "StartTime: " << StartTime << std::endl;
}

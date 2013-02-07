#include <iostream>
#include "Logging.hpp"
#include "Station.hpp"
#include "Song.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
using boost::property_tree::ptree;
using namespace std;

int main()
{
    ptree configtree;
    read_xml("config.xml", configtree);
    Logging Logger(configtree.get("config.logging.level", 1),//Defaults to INFO if not present in config
                    configtree.get("config.logging.file","log.log")); //Defaults to log.log
    Logger.Log(INFO,"Started.");
    std::vector<Station> Stations;
    BOOST_FOREACH(ptree::value_type &Entry, configtree.get_child("config.stations"))
    {
        Station station(Entry.second.get<unsigned short>("port"),
                        Entry.second.get<std::string>("mountpoint"));
        BOOST_FOREACH(ptree::value_type &Category, Entry.second.get_child("categories."))
        {
            station.addCategory(Category.second.data());
        }
        Logger.Log(DEBUG,"Retrieved " + station.mountpoint + " from config.xml.");
        Stations.push_back(station);
    }
    BOOST_FOREACH(Station &station, Stations)
    {
        std::cout << "Found station" << std::endl;
    }
    Logger.Log(INFO,"Closed.");
    return 0;
}

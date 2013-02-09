#include <iostream>
#include "Logging.hpp"
#include "Station.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
using boost::property_tree::ptree;
using namespace std;
Logging Logger;
int main()
{
    ptree configtree;
    read_xml("config.xml", configtree);
    //TODO: Logging class reads the config.xml too. Avoid the extra parsing.

    boost::asio::io_service io_service;
    Logger.Log(INFO,"Started.");
    boost::ptr_vector<Station> Stations;
    BOOST_FOREACH(ptree::value_type &Entry, configtree.get_child("config.stations"))
    {
        Station * station = new Station(io_service, Entry.second.get<unsigned short>("port"),
                        Entry.second.get<std::string>("mountpoint"));

        BOOST_FOREACH(ptree::value_type &Category, Entry.second.get_child("categories."))
        {
            station->addCategory(Category.second.data());
        }
        Stations.push_back(station);
        Logger.Log(DEBUG,"Retrieved " + station->mountpoint + " from config.xml.");
    }
    io_service.run();
    Logger.Log(INFO,"Closed.");
    return 0;
}

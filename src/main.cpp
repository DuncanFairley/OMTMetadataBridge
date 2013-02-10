#include <iostream>
#include "Logging.hpp"
#include "Station.hpp"
#include "Song.hpp"


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <boost/foreach.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

using boost::property_tree::ptree;
using namespace std;
Logging Logger;
ptree configtree;
int main()
{

    read_xml("config.xml", configtree);
    Logger.init(); //Relies on configtree
    Logger.Log(INFO,"Started.");
    std::string icecast_admin_user, icecast_admin_password, icecast_hostname;
    if(configtree.get_optional<std::string>("config.icecast"))
    {
        Logger.Log(DEBUG, "Reading Icecast block in config.xml");
        try
        {
            icecast_admin_user = configtree.get<std::string>("config.icecast.admin_user");
            icecast_admin_password = configtree.get<std::string>("config.icecast.admin_password");
            icecast_hostname = configtree.get<std::string>("config.icecast.hostname");
        }
        catch(boost::property_tree::ptree_bad_path& e)
        {
            std::string invalidpath = e.path<boost::property_tree::path>().dump();
            std::cerr << "(Fatal) " << invalidpath << " doesn't exist." << std::endl;
            Logger.Log(ERROR,invalidpath + " needs to exist if config.icecast is defined.");
            return 1;
        }
    }

    boost::asio::io_service io_service;

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

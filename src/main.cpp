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
    return 0;

    cout << "Enter XML" << endl;
    std::string input = "";
    cin >> input;
    Station Station(8000);
    if(Station.hasCategory("test"))
        cout << "Found eet.";
    return 0;
    Song Song(input, Station);
    cout << "Done" << endl;
    Logger.Log(INFO,"Closed.");
    return 0;
}

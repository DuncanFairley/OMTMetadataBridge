#include "Song.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

using boost::property_tree::ptree;

Song::Song(const std::string& XmlData, Station& Station)
{

    ptree pt;
    std::istringstream XmlDatas ("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?><PlayList><Entry Event=\"00\" Type=\"Playing\" Category=\"WLN\" Id=\"WT00\" Title=\"BEST SOUTHERN BEST COUNTRY\" Artist=\"TOP HOUR\" Album=\"\" Composer=\"\" MusicId=\"\" Duration=\"28000\" StartTime=\"Wed Jan 16 14:05:16 2013\"/><Entry Event=\"01\" Type=\"Playing\" Category=\"WMS\" Id=\"Q294\" Title=\"Should\'ve Said No\" Artist=\"Taylor Swift\" Album=\"\" Composer=\"\" MusicId=\"\" Duration=\"223000\" StartTime=\"Wed Jan 16 14:05:41 2013\"/></PlayList>");
    read_xml(XmlDatas, pt);
    BOOST_FOREACH(ptree::value_type &Entry, pt.get_child("PlayList"))
    {
            if(Entry.second.get<std::string>("<xmlattr>.Type") == "Playing"
               && Station.hasCategory(Entry.second.get<std::string>("<xmlattr>.Category")))
            {

            }
    }
}

#include "Config.hpp"

bool Config::init()
{
    try
    {
        read_xml("config.xml", configPtree);
    }
    catch(...)
    {
        return 0;
    }
    return 1;
}

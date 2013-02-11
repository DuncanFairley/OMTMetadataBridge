#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <boost/property_tree/ptree.hpp>

class Config
{
    public:
        bool init();
    private:
        boost::property_tree::ptree configPtree;
};

extern Config Config;
#endif // CONFIG_HPP

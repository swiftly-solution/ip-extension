#ifndef _ipclass_h
#define _ipclass_h

#include <string>

class PluginIPAPI
{
private:
    std::string plugin_name;

public:
    PluginIPAPI(std::string m_plugin_name);

    std::string GetIsoCode(std::string ip);
    std::string GetContinent(std::string ip);
    std::string GetCountry(std::string ip);
    std::string GetRegion(std::string ip);
    std::string GetCity(std::string ip);
    std::string GetTimezone(std::string ip);
    double GetLatitude(std::string ip);
    double GetLongitude(std::string ip);
    std::string GetASN(std::string ip);
};

#endif
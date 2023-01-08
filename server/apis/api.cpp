#include "api.h"

namespace api
{
    void Router::addRoute(const std::string &route, const Poco::Net::HTTPRequestHandlerFactory& factory)
    {
        routing_table[route] = &factory;
    }

    Poco::Net::HTTPRequestHandlerFactory* Router::getFactory(const std::string& route) {
        auto it = routing_table.find(route);
        if (it != routing_table.end())
            return it->second;
        return new Poco::Net::HTTPRequestHandlerFactory();
    }
} // namespace api

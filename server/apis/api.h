#include "Poco/URI.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include <string>
#include <unordered_map>

namespace api
{
    class Router
    {
    public:
        Router();
        void addRoute(const std::string &route, const Poco::Net::HTTPRequestHandlerFactory &factory);
        Poco::Net::HTTPRequestHandlerFactory* getFactory(const std::string& route);

    private:
        void init();
        std::unordered_map<std::string, Poco::Net::HTTPRequestHandlerFactory *> routing_table;
    };
}
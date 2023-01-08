
#include "Poco/Net/HTTPRequestHandlerFactory.h"

namespace api
{

    class IFactory : public Poco::Net::HTTPRequestHandlerFactory
    {
    public:
        virtual Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override = 0;
    };

} // namespace api

#include <vector>
#include <string>

namespace entity
{

    /**
     * @brief Interface for User
     *
     */
    class IUser
    {
    public:
        virtual ~IUser() = 0;
    };

    class User : public IUser
    {
    public:
        User(std::string id);
        ~User() = default;
    private:
        std::string id;
    };


}
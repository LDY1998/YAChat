#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
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
    };

    class ChatRoom
    {
    public:
        ChatRoom();
        ChatRoom(std::vector<std::string> &user_ids);

        void addUser(const std::string &id);
        void deleteUser(const std::string &id);

    private:
        std::vector<std::string> user_ids;
    };

}
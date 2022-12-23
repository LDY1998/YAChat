#include <vector>
#include <string>

namespace entity
{
    class ChatRoom
    {
    public:
        ChatRoom() {}
        ChatRoom(std::vector<std::string> &user_ids) : user_ids(user_ids) {}

        void addUser(const std::string &id);
        void deleteUser(const std::string &id);

    private:
        std::vector<std::string> user_ids;
    };

    class ChatSession
    {
    public:
        ChatSession() {}
        void addChat(const std::string &chat);

    private:
        std::vector<std::string> chats;
        std::string id;
    };
}
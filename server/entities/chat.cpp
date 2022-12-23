#include "chat.h"
#include <algorithm>

namespace entity {
    void ChatRoom::addUser(const std::string &id) {
        this->user_ids.push_back(id);
    }

    void ChatRoom::deleteUser(const std::string &id) {
        auto id_iter = std::find(user_ids.begin(), user_ids.end(), id);
        if (id_iter != user_ids.end()) {
            user_ids.erase(id_iter);
        }
    }
}
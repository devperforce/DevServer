#include "pch.h"
#include "Content/Chat/Public/ChatController.h"

#include "Content/Protocol/Public/Session.h"
#include "Content/Protocol/Public/Handler/Protobuf.h"

using namespace ws;
using namespace Protocol;

namespace Chat {

ChatController::ChatController(const User& user) : user_(user) {
}

void ChatController::Broadcast(const std::string& message) const {
    auto noti = std::make_shared<ChatBroadcastNotify>();
    noti->set_nickname(user_.nickname());
    noti->set_message(message);
    UserRepository::GetInstance().Broadcast(noti);
}

void ChatController::Unicast(int64_t to_user_uid, const std::string& message) const {
    const auto to_user = UserRepository::GetInstance().Find(to_user_uid);
    bool log_on = false;
    if (const auto to_session = to_user->session(); to_session != nullptr) {
        auto noti = std::make_shared<ChatUnicastNotify>();
        noti->set_from_nickname(user_.nickname());
        noti->set_message(message);
        to_session->Send(noti);
        log_on = true;
    }

    auto res = std::make_shared<ChatBroadcastRes>();
    res->set_to_nickname(to_user->nickname());
    res->set_message(message);
    res->set_result(ChatBroadcastRes::kSuccess);
    if (!log_on) {
        res->set_result(ChatBroadcastRes::kLogOff);
    }

    if (const auto session = user_.session(); session != nullptr) {
        session->Send(res);
    }
}

void ChatController::AdminNotice(const std::string& message, std::chrono::milliseconds duration) {

}

void ChatController::AdminNotice(const User& to, const std::string& message, std::chrono::milliseconds duration) {

}

} // namespace Chat

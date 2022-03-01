#include "pch.h"
#include "Content/Protocol/Public/Handler/LobbyHandler.h"

#include "Content/Protocol/Public/Handler/Protobuf.h"
#include "Content/Protocol/Public/Session.h"

#include "ProtobufHandler/Public/Handler.h"

using namespace ws;

namespace Protocol {

void OnLogin(std::shared_ptr<LoginReq> req, std::shared_ptr<Session> session) {
    const int64_t user_uid = req->user_uid();
    const std::string nickname = req->nickname();

    const auto old_user = UserRepository::GetInstance().Find(user_uid);
    if (old_user != nullptr) {
        UserRepository::GetInstance().Remove(user_uid);
        auto old_session = old_user->session();
        old_session->Close();
    }

    auto user = std::make_shared<User>(session, user_uid, nickname);
    session->set_user(user);
    UserRepository::GetInstance().Add(user_uid, user);

    auto res = std::make_shared<LoginRes>();
    res->set_result(LoginRes::kSuccess);
    session->Send(res);
}


void OnPing(std::shared_ptr<PingRes> req, std::shared_ptr<Session> session) {
    session->UpdatePing();
}

void LobbyHandler::Register() {
    Common::Handler<LoginReq, Session>::Register(&OnLogin);
    Common::Handler<PingRes, Session>::Register(&OnPing);
}

} // namespace Protocol

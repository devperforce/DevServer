#include "pch.h"
#include "Content/Protocol/Public/Session.h"
#include "Protobuf/Generated/world_status.pb.h"

#include "Content/Object/Public/Player.h"

using namespace ws;

namespace Protocol {

// User
User::User(std::shared_ptr<Session> session,
           int64_t user_uid,
           std::string nickname) : session_(session), user_uid_(user_uid), nickname_(nickname) {
}

int64_t User::user_uid() const {
    return user_uid_;
}

const std::string& User::nickname () const {
    return nickname_;
}

std::shared_ptr<Session> User::session() const {
    return session_.lock();
}

// Session
Session::Session(boost::asio::io_context& io_context, boost::asio::ip::tcp::socket&& socket) 
    : Common::Session(io_context, std::move(socket)) {
    std::cout << "[Session] Ctor!" << std::endl;
}

Session::~Session() {
    std::cout << "[Session] Dtor!" << std::endl;
}

/*
void Session::Dispatch(std::function<void()> msg) {
    strand_.dispatch(msg);
}
*/

void Session::OnConnected() {
    std::cout << "[Session] OnConnected!" << std::endl;
    StartPing();
}

void Session::OnDisconnected(const boost::system::error_code& ec) {
    std::cout << "[Session] OnDisconnected! " << ec.message() << std::endl;
    if (!closed_ && user_ != nullptr) {
        UserRepository::GetInstance().Remove(user_->user_uid());
    }
}

void Session::OnError(const boost::system::error_code& ec) {
    std::cout << "OnError: " << ec.message() << std::endl;
    // 접속종료 시키기

}

void Session::OnClosed () {
    closed_ = true;
}

std::shared_ptr<User> Session::user() const {
    return user_;
}

void Session::set_user(std::shared_ptr<User> user) {
    user_ = user;
}

void Session::UpdatePing() {
    last_ping_time_ = std::chrono::system_clock::now();
    LOG_ERROR("[Session] Pong last_ping_time: {0}", last_ping_time_.time_since_epoch());
}

void Session::StartPing() {
    static const auto kWaitDuration = std::chrono::seconds(1);
    ping_timer_ = std::make_shared<boost::asio::steady_timer>(strand_.context(), kWaitDuration);
    auto refresh_ping_time = std::chrono::system_clock::now();
    LOG_ERROR("[Session] Ping refresh_ping_time: {0}", last_ping_time_.time_since_epoch());
    ping_timer_->async_wait(strand_.wrap([this, self = shared_from_this(), start_time = refresh_ping_time](const boost::system::error_code& ec) {
        //LOG_ERROR("[Session] Check PingTime!");

        if (ec || boost::asio::steady_timer::clock_type::now() < ping_timer_->expires_at()) {
            std::cout << "ping timer cancel!" << std::endl;
            return;
        }

        if (last_ping_time_ <= start_time) {
            LOG_ERROR("[Session] CLOSE !! last_ping_time_{0}, start_time{1}", last_ping_time_.time_since_epoch(), start_time.time_since_epoch());
            Close();
            return;
        }
        StartPing();
    }));

    last_ping_time_ = refresh_ping_time;
    const auto req = std::make_shared<PingReq>();
    Send(req);
}

// SessionRepository
UserRepository& UserRepository::GetInstance() {
    static UserRepository repository;
    return repository;
}

void UserRepository::Add(int64_t user_uid, std::shared_ptr<User> user) {
    std::lock_guard<std::mutex> lock(mutex_);

    users_.try_emplace(user_uid, user);
}

void UserRepository::Remove(int64_t user_uid) {
    std::lock_guard<std::mutex> lock(mutex_);

    users_.erase(user_uid);
}

std::shared_ptr<User> UserRepository::Find(int64_t user_uid) {
    std::lock_guard<std::mutex> lock(mutex_);

    if (!users_.contains(user_uid)) {
        return nullptr;
    }
    return users_[user_uid];
}

void UserRepository::Broadcast(std::shared_ptr<google::protobuf::Message> msg) const {
    std::lock_guard<std::mutex> lock(mutex_);

    for (auto user : users_ | std::views::values) {
        if (auto session = user->session(); session != nullptr) {
            session->Send(msg);
        }
    }
}
    
} // namespace Server

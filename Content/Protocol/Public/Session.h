#pragma once

#include "ProtobufHandler/Public/Session.h"

#include "Content/Database/Public/Query.h"

namespace Object {
class Player;
} // namespace Object

namespace Protocol {

class Session;

class User : boost::noncopyable {
public:
    User(std::shared_ptr<Session> session,
         int64_t user_uid,
         std::string nickname);

    int64_t user_uid () const;
    const std::string& nickname () const;

    std::shared_ptr<Session> session () const;

private:
    int64_t user_uid_ = 0;
    std::string nickname_;
    std::weak_ptr<Protocol::Session> session_;
};

class Session : public Common::Session {
public:
    Session(boost::asio::io_context& io_context, boost::asio::ip::tcp::socket&& socket);
    virtual ~Session ();


    //void Dispatch(std::function<void()> msg);

    void OnConnected() override ;
    void OnDisconnected(const boost::system::error_code& ec) override;
    void OnError(const boost::system::error_code& ec) override;
    void OnClosed() override ;

    //void OnRanking(std::vector<Database::Ranking>&& rankings);
    
    std::shared_ptr<User>user() const;
    void set_user(std::shared_ptr<User> user);

    void UpdatePing();

private:
    void StartPing();

    std::shared_ptr<boost::asio::steady_timer> ping_timer_ = nullptr;
    std::chrono::system_clock::time_point last_ping_time_;

    std::shared_ptr<User> user_ = nullptr;
    bool closed_ = false;
};

class UserRepository : boost::noncopyable {
public:
    static UserRepository& GetInstance();

    void Add(int64_t user_uid, std::shared_ptr<User> session);
    void Remove(int64_t user_uid);
    std::shared_ptr<User> Find (int64_t user_uid);

    void Broadcast (std::shared_ptr<google::protobuf::Message> msg) const;

private:
    std::unordered_map<int64_t, std::shared_ptr<User>> users_;
    mutable std::mutex mutex_;
};

} // namespace Protocol
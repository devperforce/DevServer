#pragma once

namespace Protocol {
class User;
} // Session;

namespace Chat {

class ChatController {
public:
    explicit ChatController(const Protocol::User& sender);

    // 전체유저에게 메세지
    void Broadcast(const std::string& message) const;

    // 유저끼리 귓속말
    void Unicast(int64_t to_user_uid, const std::string& message) const;

    // 전체 운영 공지
    static void AdminNotice(const std::string& message, std::chrono::milliseconds duration);

    // 1명에게 운영 공지
    static void AdminNotice(const Protocol::User& to, const std::string& message, std::chrono::milliseconds duration);

private:
    const Protocol::User& user_;
};

} // namespace Chat

// 이걸 풀날이 올까...
// ScheduleNotice
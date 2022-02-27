#pragma once

namespace Protocol {
class User;
} // Session;

namespace Chat {

class ChatController {
public:
    explicit ChatController(const Protocol::User& sender);

    // ��ü�������� �޼���
    void Broadcast(const std::string& message) const;

    // �������� �ӼӸ�
    void Unicast(int64_t to_user_uid, const std::string& message) const;

    // ��ü � ����
    static void AdminNotice(const std::string& message, std::chrono::milliseconds duration);

    // 1���� � ����
    static void AdminNotice(const Protocol::User& to, const std::string& message, std::chrono::milliseconds duration);

private:
    const Protocol::User& user_;
};

} // namespace Chat

// �̰� Ǯ���� �ñ�...
// ScheduleNotice
#pragma once

#include <boost/asio.hpp>
#include <boost/core/noncopyable.hpp>

#include "Database/Public/Connection.h"

namespace Protocol {
class Session;
} // namespace Protocol


namespace nanodbc {
class connection;
}

namespace Database {

class Connection : public std::enable_shared_from_this<Connection>, boost::noncopyable {
public:
    class Pool {
    public:
        // 추후 추가 필요
    };
    static std::shared_ptr<Connection> Create(boost::asio::io_context& io_context, const Sql::SqlInfo& sql_info, const Sql::AccountInfo& account_info);

    static void TestQuery(Connection& conn);

    bool Connect();
    void Disconnect();

private:
    Connection(boost::asio::io_context& io_context,
        const Sql::SqlInfo& sql_info, 
        const Sql::AccountInfo& account_info);

    boost::asio::io_context::strand strand_;
    std::shared_ptr<nanodbc::connection> connection_;

    const Sql::SqlInfo sql_info_;
    const Sql::AccountInfo account_info_;
};

} // namespace Database
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
        static bool Initialize(boost::asio::io_context& io_context,
                               const Sql::SqlInfo& sql_info, 
                               const Sql::AccountInfo& account_info,
                               int32_t max_sharding_index = 8);
        static Connection& Get(int32_t user_uid);
        static void Clear();
    };

    Connection(boost::asio::io_context& io_context,
               const Sql::SqlInfo& sql_info, 
               const Sql::AccountInfo& account_info);

    void TestQuery();

    //void GetRanking (std::shared_ptr<Protocol::Session> session);

private:
    nanodbc::connection* GetConn ();

    bool Connect();
    void Disconnect();

    boost::asio::io_context::strand strand_;
    std::shared_ptr<nanodbc::connection> connection_;

    const Sql::SqlInfo sql_info_;
    const Sql::AccountInfo account_info_;
};

} // namespace Database
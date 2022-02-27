#include "pch.h"
#include "Content/Database/Public/Connection.h"

#include "Database/Public/Connection.h"
#include "Database/Public/nanodbc.h"

#include "Content/Protocol/Public/Session.h"

using namespace nanodbc;

namespace Database {

static std::vector<std::shared_ptr<Connection>> connections;

bool Connection::Pool::Initialize(boost::asio::io_context& io_context,
                                  const Sql::SqlInfo& sql_info, 
                                  const Sql::AccountInfo& account_info,
                                  int32_t max_sharding_index) {

    for (auto i = 0; i < max_sharding_index; ++i) {
        connections.emplace_back(std::make_shared<Connection>(io_context, sql_info, account_info));    
    }

    for (auto conn : connections) {
        if (!conn->Connect()) {
            return false;
        }
    }

    return true;
}

Connection& Connection::Pool::Get(int32_t user_uid) {
    assert(connections.size() > 0);

    const size_t index = user_uid & connections.size();
    return *connections[index];
}  

void Connection::Pool::Clear() {
    for (auto conn : connections) {
        conn->Disconnect();
    }
}

Connection::Connection(boost::asio::io_context& io_context, 
                       const Sql::SqlInfo& sql_info, 
                       const Sql::AccountInfo& account_info) 
    : strand_(io_context), sql_info_(sql_info), account_info_(account_info)  {
}

bool Connection::Connect() {

    std::wstring str = std::format(L"DSN={};SERVER={};UID={};PWD={};DRIVER=MySQL Server;", 
        sql_info_.dsn, sql_info_.address, account_info_.user_id, account_info_.pwd);


    try {
        connection_ = std::make_shared<nanodbc::connection>(str.c_str());
       //// connections_.emplace_back();
    } catch (const nanodbc::database_error& ec) {
        std::wcout << ec.what() << std::endl;
        return false;
    } catch (const nanodbc::programming_error& ec) {
        std::wcout << ec.what() << std::endl;
        return false;
    } catch (std::exception& ec) {
        std::wcout << ec.what() << std::endl;
        return false;
    } catch (...) {
        //std::wcout << L"error!"  << std::endl;
        return false;
    }


    std::wcout << std::format(L"Sql Conncted! connection size: {}", 1) << std::endl;

    return true;
}

void Connection::Disconnect() {

}

connection* Connection::GetConn() {
    if (!connection_->connected()) {
        return nullptr;
    }

    return connection_.get();
}

void Connection::TestQuery() {
    strand_.dispatch([this, self = shared_from_this()] {
        connection* conn = GetConn();
        if (conn == nullptr) {
            // LOG_ERROR
            return;
        }

        statement stmt(*conn);
        prepare(stmt, L"{call sp_get_mail(?, ?)}");

        timestamp start_time, end_time;
        start_time.year = 2021; start_time.month = 8; start_time.day = 24; start_time.hour = 0; start_time.min = 0; start_time.sec = 0; start_time.fract = 0;
        end_time.year = 2021;   end_time.month = 8;   end_time.day = 25;   end_time.hour = 0;   end_time.min = 0;   end_time.sec = 0; end_time.fract = 0;

        stmt.bind(0, &start_time, statement::PARAM_OUT);
        stmt.bind(1, &end_time, statement::PARAM_OUT);

        result results2 = execute(stmt);
        std::wcout << L"results.affected_rows: " << results2.affected_rows() << std::endl;
        while (results2.next()) {
            // 다시 unity로 보내줄때는 utf16을 utf8로 보내줘야하는건가
            const std::wstring subject = results2.get<std::wstring>(L"subject");

            std::wcout << subject.c_str() << std::endl;

            const timestamp sent_time = results2.get<timestamp>(L"sent_time");
            std::wcout << "hour: " << sent_time.hour << std::endl;

            const int64_t user_uid = results2.get<int64_t>(L"user_uid");
            std::wcout << "user_uid: " << user_uid << std::endl;
        }
    });
}

} // namespace Database
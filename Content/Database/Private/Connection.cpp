#include "pch.h"
#include "Content/Database/Public/Connection.h"

#include "Database/Public/Connection.h"
#include "Database/Public/nanodbc.h"

#include "Content/Protocol/Public/Session.h"

using namespace nanodbc;

namespace Database {

std::shared_ptr<Connection> Connection::Create(boost::asio::io_context& io_context, const Sql::SqlInfo& sql_info, const Sql::AccountInfo& account_info) {
    auto conn =  std::shared_ptr<Connection>(new Connection(io_context, sql_info, account_info));
    if (!conn->Connect()) {
        return nullptr;
    }
    return conn;
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
    } catch (const nanodbc::database_error& ec) {
        LOG_ERROR("Database Error: {}", ec.state());
        std::wcout << ec.what() << std::endl;
        return false;
    } catch (const nanodbc::programming_error& ec) {
        std::wcout << L"ProgrammingError" << ec.what() << std::endl;
        return false;
    } catch (std::exception& ec) {
        std::wcout << L"Exception" << ec.what() << std::endl;
        return false;
    } catch (...) {
        //std::wcout << L"error!"  << std::endl;
        return false;
    }

    return true;
}

void Connection::Disconnect() {

}

void Connection::TestQuery(Connection& conn) {
    statement stmt(*conn.connection_);
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
}

} // namespace Database
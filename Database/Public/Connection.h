#pragma once

namespace Database {
namespace Sql {

struct SqlInfo {
    std::wstring dsn;
    std::wstring address;
};

struct AccountInfo {
    std::wstring user_id;
    std::wstring pwd;
};

} // Sql
} // Database

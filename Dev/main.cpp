#include "pch.h"

#include "Dev/ExceptionHandler.h"
#include "Dev/Server/Public/Server.h"

#include "ProtobufHandler/Public/Handler.h"

#include "Utility/Public/Log.h"
#include "Utility/Public/Time.h"

#include "Content/Protocol/Public/Handler/LobbyHandler.h"
#include "Content/Protocol/Public/Handler/DungeonHandler.h"

#include "Content/Database/Public/Connection.h"

static auto OnStop(boost::asio::io_context& io_context) {
    return [&io_context](boost::system::error_code const& ec, int signal_number) {
        if (ec) {
            LOG_ERROR("Stop {}", ec.message());
            return;
        }
        io_context.stop();
    };
}

static constexpr size_t kThreadCount = 8;

int main() {
    try {
        setlocale(LC_ALL, "");

        GOOGLE_PROTOBUF_VERIFY_VERSION;
        ExceptionHandler::GetInstance().Initialize();
        ExceptionHandler::GetInstance().Start();

        Utility::Log::Initialize();
        Utility::Log::AddAttributes();

        boost::asio::io_context io_context;

        boost::asio::signal_set signals(io_context, SIGINT);
        signals.async_wait(OnStop(io_context));
        
        if (!Database::Connection::Pool::Initialize(
            io_context,
            { L"ctest", L"aaaa.clszgjeysodm.ap-northeast-2.rds.amazonaws.com" },
            { L"admin", L"1234" },
            kMaxScaleSize
        )) {
            return 0;
        }

        Database::Connection::Pool::Get(1).TestQuery();

        // ÇÚµé·¯ µî·Ï
        Protocol::LobbyHandler::Register();
        Protocol::DungeonHandler::Register();

        // ÄÁÅÙÃ÷ Ãß°¡
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 3100);

        std::vector<std::thread> io_threads;
        auto sever = std::make_shared<Content::Server>(io_context, endpoint);

        for (int32_t i = 0; i < kThreadCount; ++i) {
            io_threads.emplace_back([&] {
                sever->Start();
                io_context.run();
            });
        }
        io_context.run();

        for (auto& io_thread : io_threads)
        {
            io_thread.join();
        }

    } catch (const boost::property_tree::xml_parser_error& error) {
        LOG_ERROR("Unable to read xml! {}", error.what());
    } catch (...) {
        LOG_ERROR("Exception occur!");
    }
   
    getchar();
    return 0;
}

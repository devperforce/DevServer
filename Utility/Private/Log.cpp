#include "pch.h"
#include "Utility/Public/Log.h"

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

namespace Utility {

void Log::Initialize() {
    logging::add_file_log
    (
        keywords::file_name = "sample_%N.log",
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        keywords::format = "[%TimeStamp%]: %Message%",
        keywords::auto_flush = true
    );
    
    logging::add_console_log(std::clog,
        keywords::format = "%TimeStamp%: %_%",
        keywords::auto_flush = true);

    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );
}

void Log::AddAttributes () {
    logging::add_common_attributes();
    /*
    boost::log::core::get()->add_global_attribute(
        "TimeStamp",
        boost::log::attributes::local_clock());
    */
}

Log::Log() {

}

Log::~Log() {

}

auto& Log::Logger() {
    static boost::log::sources::severity_logger< boost::log::trivial::severity_level> logger;
    //static boost::log::sources::wseverity_logger_mt< boost::log::trivial::severity_level > logger;
    //static boost::log::sources::severity_logger_mt< boost::log::trivial::severity_level > logger;
    return logger;
}

void Log::Logging(boost::log::trivial::severity_level level, const std::string& msg) {
    //BOOST_LOG_SEV(Logger(), level) << msg;
    BOOST_LOG_SEV(Logger(), level) << msg;
}

} // namespace Utility


//sink->locked_backend()->scan_for_files();
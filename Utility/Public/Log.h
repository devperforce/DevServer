#pragma once

#include <boost/log/trivial.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/attributes/current_process_name.hpp>
#include <boost/log/detail/default_attribute_names.hpp>
#include <boost/log/detail/header.hpp>
#include <format>

namespace Utility {

class Log {
public:
    static void Initialize();
    static void AddAttributes();

    static auto& Logger();
    static void Logging(boost::log::trivial::severity_level level, const std::string& msg);

    Log();
    ~Log();
};

} // namespace Utility

template <typename... Args>
static void LOG_TRACE(Args&&... args) {
    //Utility::Log::Logging(boost::log::trivial::severity_level::trace, "[Trace] " + std::format(std::forward<Args>(args)...));
    Utility::Log::Logging(boost::log::trivial::severity_level::trace, std::format(std::forward<Args>(args)...));
}

template <typename... Args>
static void LOG_DEBUG(Args&&... args) {
    Utility::Log::Logging(boost::log::trivial::severity_level::debug, std::format(std::forward<Args>(args)...));
}

template <typename... Args>
static void LOG_INFO(Args&&... args) {
    Utility::Log::Logging(boost::log::trivial::severity_level::info, std::format(std::forward<Args>(args)...));
}

template <typename... Args>
static void LOG_WARNING(Args&&... args) {
    Utility::Log::Logging(boost::log::trivial::severity_level::warning, std::format(std::forward<Args>(args)...));
}

template <typename... Args>
static void LOG_ERROR(Args&&... args) {
    Utility::Log::Logging(boost::log::trivial::severity_level::error, std::format(std::forward<Args>(args)...));
}

template <typename... Args>
static void LOG_FATAL(Args&&... args) {
    Utility::Log::Logging(boost::log::trivial::severity_level::fatal, std::format(std::forward<Args>(args)...));
}

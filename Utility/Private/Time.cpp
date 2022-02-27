#include "pch.h"
#include "Utility/Public/Time.h"

namespace Utility {

constexpr uint32_t kStartYear = 1900;

DateTime DateTime::LocalNow() {
    DateTime date_time;
    const std::time_t now = std::time(nullptr);
    std::tm calendar_time;
    localtime_s(&calendar_time, std::addressof(now));

    date_time.year_ = calendar_time.tm_year + kStartYear;
    date_time.month_ = calendar_time.tm_mon + 1;
    date_time.day_ = calendar_time.tm_mday;
    date_time.hour_ = calendar_time.tm_hour;
    date_time.minute_ = calendar_time.tm_min;
    date_time.second_ = calendar_time.tm_sec;

    return date_time;
}

DateTime DateTime::UtcNow() {
    DateTime date_time;
    const std::time_t now = std::time(nullptr);
    std::tm calendar_time;
    gmtime_s(&calendar_time, std::addressof(now));

    date_time.year_ = calendar_time.tm_year + kStartYear;
    date_time.month_ = calendar_time.tm_mon + 1;
    date_time.day_ = calendar_time.tm_mday;
    date_time.hour_ = calendar_time.tm_hour;
    date_time.minute_ = calendar_time.tm_min;
    date_time.second_ = calendar_time.tm_sec;

    return date_time;
}

uint32_t DateTime::year() const {
    return year_;
}

uint32_t DateTime::month() const {
    return month_;
}

uint32_t DateTime::day() const {
    return day_;
}

uint32_t DateTime::hour() const {
    return hour_;
}

uint32_t DateTime::minute() const {
    return minute_;
}

uint32_t DateTime::second() const {
    return second_;
}

} // namespace Utility

#pragma once

namespace Utility {

class DateTime {
public:
    static DateTime LocalNow();
    static DateTime UtcNow();

     uint32_t year () const;
     uint32_t month () const;
     uint32_t day () const;
     uint32_t hour () const;
     uint32_t minute  () const;
     uint32_t second () const;

private:
    uint32_t year_ = 0;
    uint32_t month_ = 0;
    uint32_t day_ = 0;
    uint32_t hour_ = 0;
    uint32_t minute_ = 0;
    uint32_t second_ = 0;
};

} // namespace Utility

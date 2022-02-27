// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define _WIN32_WINNT 0x0A00

__pragma(warning(disable:4099))

#include <boost/property_tree/xml_parser.hpp>

#include <format>
#include <memory>
#include <optional>
#include <string>
#include <iostream>
#include <deque>
#include <variant>

// nanodbc
/*
#include <cstddef>
#include <functional>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
*/

static constexpr size_t kMaxScaleSize = 8;

#endif //PCH_H

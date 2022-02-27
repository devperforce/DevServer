// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define _WIN32_WINNT 0x0A00

// add headers that you want to pre-compile here
#include "framework.h"

#include <boost/property_tree/xml_parser.hpp>

#include <algorithm>
#include <cassert>
#include <codecvt>
#include <deque>
#include <string>
#include <format>
#include <memory>
#include <ranges>
#include <vector>
#include <functional>
#include <set>
#include <mutex>
#include <variant>
#include <iostream>
#include <filesystem>
#include <variant>
#include <unordered_map>

#include "Utility/Public/Log.h"
#include "Utility/Public/Math.h"

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };


#endif //PCH_H

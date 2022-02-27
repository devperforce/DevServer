#pragma once

#define PRAGMA_WARNING_DISABLE_PROTOBUF \
__pragma(warning(disable:4099))
__pragma(warning(disable:4100))
__pragma(warning(disable:4103))
__pragma(warning(disable:4127))
__pragma(warning(disable:4244))
__pragma(warning(disable:4996))
__pragma(warning(disable:5045))


#pragma warning(push)

PRAGMA_WARNING_DISABLE_PROTOBUF

#include "Protobuf/Generated/world_status.pb.h"

#pragma warning(pop)

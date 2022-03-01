#pragma once

//#include "Protobuf/Generated/world_status.pb.h"

namespace Protocol {

class Session;

class DungeonHandler: boost::noncopyable {
public:
    static void Register();
};

} // namespace Protocol
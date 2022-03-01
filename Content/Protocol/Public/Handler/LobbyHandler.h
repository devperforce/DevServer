#pragma once

//#include "Protobuf/Generated/world_status.pb.h"
/*
namespace ws {
class LoginReq;
} // namespace ws;
*/

namespace Protocol {

class LobbyHandler : boost::noncopyable {
public:
    static void Register();
};

} // namespace Protocol

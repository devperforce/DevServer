#pragma once

//#include "Protobuf/Generated/world_status.pb.h"

namespace Protocol {

class Session;

class DungeonHandler {
public:
    static void Register();

    //static void OnLeaveRoom(std::shared_ptr<ws::LeaveRoomReq> req, Session* session);

};

} // namespace Protocol
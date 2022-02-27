#include "pch.h"

#include "ProtobufHandler/Public/Handler.h"

namespace Common {

IHandler::Handlers& IHandler::handlers() {
    static Handlers handlers;
    return handlers;
}

} // namespace Common
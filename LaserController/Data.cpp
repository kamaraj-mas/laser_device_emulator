#include "Data.h"

CommandCode CommandData::GetCommandCode()
{
    if (command == "STR")
        return CommandCode::START;
    if (command == "STP")
        return CommandCode::STOP;
    if (command == "ST?")
        return CommandCode::STATUS;
    if (command == "KAL")
        return CommandCode::KEEP_ALIVE;
    if (command == "PW?")
        return CommandCode::GET_LASER_POWER;
    if (command == "PW=")
        return CommandCode::SET_LASER_POWER;
    if (command == "ESM")
        return CommandCode::ENABLE_SILLY_MODE;
    if (command == "DSM")
        return CommandCode::DISABLE_SILLY_MODE;
    else
        return CommandCode::UNKNOWN;
}

std::string CommandData::GetCommandAsString()
{
    return command;
};
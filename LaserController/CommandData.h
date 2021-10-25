#pragma once

#include <vector>
#include <string>

//command code in enum
enum class CommandCode
{
    START,
    STOP,
    STATUS,
    KEEP_ALIVE,
    GET_LASER_POWER,
    SET_LASER_POWER,
    ENABLE_SILLY_MODE,
    DISABLE_SILLY_MODE,
    UNKNOWN
};


//class to hold Command & parameters
struct CommandData {
    std::string command;
    //Keep the parameters as string so that we can convert them to 
    //different type if needed based on the command
    std::vector<std::string> parameters;
    CommandData() = default;
    CommandCode GetCommandCode();
    std::string GetCommandAsString();
};


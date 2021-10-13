#pragma once
#include "LaserDevice.h"
#include "Command.h"
#include <thread>

class LaserController
{
private:
    void parseCommandData(std::string CommandString, CommandData& Cmd);
    std::unique_ptr<Command> CreateCommand(CommandCode code);
    std::unique_ptr<Command> cmd = nullptr;
public:
    LaserController() = default;
    LaserDevice device;
    std::unique_ptr<std::thread> monitorThread = nullptr;
    void Run();
    ~LaserController();
};


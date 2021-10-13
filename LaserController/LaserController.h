#pragma once
#include "LaserDevice.h"
#include "Parser.h"
#include "Command.h"
#include <thread>

class LaserController
{
private:
    void parseCommandData(std::string CommandString, CommandData& Cmd);
    std::unique_ptr<Command> CreateCommand(CommandCode code);
public:
    LaserController() = default;
    LaserDevice device;
    std::thread* monitorThread = nullptr;
    void Run();
    ~LaserController();
};

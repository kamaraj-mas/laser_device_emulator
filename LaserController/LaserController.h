#pragma once
#include "LaserDevice.h"
#include "Command.h"
#include <thread>

class LaserController
{
private:
    void parseCommandDataFromString(std::string CommandString, CommandData& Cmd);
    std::unique_ptr<Command> CreateCommand(CommandCode code);
    void monitorThread();
    bool monitorThreadHasToDie = false;
public:
    LaserController() = default;
    LaserDevice device;
    void run();
    ~LaserController();
};


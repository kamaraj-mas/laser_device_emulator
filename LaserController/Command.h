#pragma once

#include "LaserDevice.h"
#include <functional>
#include <string>
#include "CommandData.h"

//Abstract class for the commands

using CallbackMethod = typename std::function<void(std::string)>;

class Command{
protected:
    const char successIndicator = '#';
    const char failureIndicator = '!';
    const char delimiter = '|';
public:
    virtual ~Command() {
    }
    //Handler method for the specific command.
    virtual std::string execute(LaserDevice& device, CommandData& cmd) const = 0;
};

class StartCommand :public Command{
public:
    std::string execute(LaserDevice& device, CommandData& cmd) const;
};

class StopCommand :public Command {
public:
    std::string execute(LaserDevice& device, CommandData& cmd) const;
};

class StatusCommand :public Command {
public:
    std::string execute(LaserDevice& device, CommandData& cmd) const;
};

class SetPowerCommand :public Command {
public:
    std::string execute(LaserDevice& device, CommandData& cmd) const;
};

class GetPowerCommand :public Command {
public:
    std::string execute(LaserDevice& device, CommandData& cmd) const;
};

class EnableSillyModeCommand:public Command {
public:
    std::string execute(LaserDevice& device, CommandData& cmd) const;
};

class DisableSillyModeCommand :public Command {
public:
    std::string execute(LaserDevice& device, CommandData& cmd) const;
};

class KeepAliveCommand :public Command {
public:
    std::string execute(LaserDevice& device, CommandData& cmd) const;
};

class UnknownCommand :public Command {
public:
    std::string execute(LaserDevice& device, CommandData& cmd) const;
};


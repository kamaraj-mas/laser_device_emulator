#pragma once

#include "LaserDevice.h"
#include <functional>
#include <string>
#include "Data.h"

//Abstract class for the commands
class Command{
public:
    virtual ~Command() {
    }
    //Handler method for the specific command.
    virtual void execute(LaserDevice& device, CommandData& cmd, std::function<void (std::string)> Callback) const = 0;
};

class StartLaser :public Command{
public:
    void execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const;
};

class StopLaser :public Command {
public:
    void execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const;
};

class LaserStatus :public Command {
public:
    void execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const;
};

class SetLaserPower :public Command {
public:
    void execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const;
};

class GetLaserPower :public Command {
public:
    void execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const;
};

class EnableSillyMode:public Command {
public:
    void execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const;
};

class DisableSillyMode :public Command {
public:
    void execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const;
};

class KeepAlive :public Command {
public:
    void execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const;
};


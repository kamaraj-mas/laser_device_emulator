#include "LaserController.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>

void LaserController::parseCommandData(std::string CommandString, CommandData& Cmd)
{
    //Parse laser command
    std::stringstream ss(CommandString);
    std::string subString;

    //run the loop until '
    while (std::getline(ss, subString, '|'))
    {
        //First string would be command
        if (Cmd.command.empty())
        {
            Cmd.command = subString;
        }
        else //Subsequent strings will consider as input values
        {
            Cmd.parameters.push_back(subString);
        }
    }
}

std::unique_ptr<Command> LaserController::CreateCommand(CommandCode code)
{
    std::unique_ptr<Command> cmd = nullptr;
    switch (code)
    {
    case CommandCode::START:
        cmd = std::make_unique<StartLaser>();
        break;
    case CommandCode::STOP:
        cmd = std::make_unique <StopLaser>();
        break;
    case CommandCode::GET_LASER_POWER:
        cmd = std::make_unique <GetLaserPower>();
        break;
    case  CommandCode::SET_LASER_POWER:
        cmd =std::make_unique <SetLaserPower>();
        break;
    case CommandCode::ENABLE_SILLY_MODE:
        cmd =std::make_unique <EnableSillyMode>();
        break;
    case  CommandCode::DISABLE_SILLY_MODE:
        cmd =std::make_unique <DisableSillyMode>();
        break;
    case  CommandCode::STATUS:
        cmd =std::make_unique <LaserStatus>();
        break;
    case CommandCode::KEEP_ALIVE:
        cmd =std::make_unique <KeepAlive>();
        break;
    case CommandCode::UNKNOWN:
        cmd = std::make_unique <Unknown>();
        break;
    default:
        break;
    }

    return cmd;
}

void LaserController::Run() {
    std::string commandString;
    
    //Thread to track of Keep Alive message
    monitorThread = std::make_unique<std::thread>(&LaserDevice::monitorLaserActivity, &device);

    //Main input reader loop to accept laser command
    while (!std::getline(std::cin, commandString).eof()) {

        //Reverse the command if the device is on silly mode
        if (device.isSillyModeOn()) {
            std::reverse(commandString.begin(), commandString.end());
        }

        //Parse command & values from the input string
        CommandData commandData;
        parseCommandData(commandString, commandData);

        //Create command object
        cmd = CreateCommand(commandData.GetCommandCode());

        if (cmd != nullptr) {
            cmd->execute(device, commandData, [](std::string response) {
                std::cout << response << "\n";
                }
            );
        }

        cmd.reset();
    }

    device.terminateThread();
    
    if (monitorThread->joinable()) {
        monitorThread->join();
    }
}

LaserController::~LaserController()
{
    if (monitorThread->joinable()) {
        monitorThread->join();
    }
}
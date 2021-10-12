// LaserController.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <algorithm>
#include "LaserDevice.h"
#include "Parser.h"
#include "Command.h"
#include <thread>

int main()
{
    std::string commandString;
    LaserDevice device;
    Parser parser;
    std::unique_ptr<Command> cmd = nullptr;
    
    //Thread to track of Keep Alive message
    std::thread* monitorThread = new std::thread(&LaserDevice::monitorLaserActivity, &device);

    //Main input reader loop to accept laser command
    while (!std::getline(std::cin, commandString).eof()){
        
        //Reverse the command if the device is on silly mode
        if (device.isSillyModeOn()) {
            std::reverse(commandString.begin(), commandString.end());
        }
        
        //Parse command & values from the input string
        CommandData commandData;
        parser.parse(commandString, commandData);

        switch (commandData.GetCommandCode())
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
            cmd = std::make_unique <SetLaserPower>();
            break;
        case CommandCode::ENABLE_SILLY_MODE:
            cmd = std::make_unique <EnableSillyMode>();
            break;
        case  CommandCode::DISABLE_SILLY_MODE:
            cmd = std::make_unique <DisableSillyMode>();
            break;
        case  CommandCode::STATUS:
            cmd = std::make_unique <LaserStatus>();
            break;
        case CommandCode::KEEP_ALIVE:
            cmd = std::make_unique <KeepAlive>();
            break;
        case  CommandCode::UNKNOWN:
            break;
        default:
            break;
        }

        if (cmd != nullptr) {
            cmd->execute(device, commandData, [](std::string response) {
                std::cout << response << "\n";
                }
            );
        }
        else{
            std::cout << "UK!" << "\n";
        }
        cmd = nullptr;
    }
    monitorThread->join();
}

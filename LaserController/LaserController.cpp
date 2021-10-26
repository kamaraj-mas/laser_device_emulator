#include "LaserController.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "IOInterface.h"

void LaserController::parseCommandDataFromString(std::string CommandString, CommandData& Cmd)
{
    //Parse laser command
    std::stringstream ss(CommandString);
    std::string subString;
    char delimiter = '|';
    //run the loop until '
    while (std::getline(ss, subString, delimiter))
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
        cmd = std::make_unique<StartCommand>();
        break;
    case CommandCode::STOP:
        cmd = std::make_unique <StopCommand>();
        break;
    case CommandCode::GET_LASER_POWER:
        cmd = std::make_unique <GetPowerCommand>();
        break;
    case  CommandCode::SET_LASER_POWER:
        cmd =std::make_unique <SetPowerCommand>();
        break;
    case CommandCode::ENABLE_SILLY_MODE:
        cmd =std::make_unique <EnableSillyModeCommand>();
        break;
    case  CommandCode::DISABLE_SILLY_MODE:
        cmd =std::make_unique <DisableSillyModeCommand>();
        break;
    case  CommandCode::STATUS:
        cmd =std::make_unique <StatusCommand>();
        break;
    case CommandCode::KEEP_ALIVE:
        cmd =std::make_unique <KeepAliveCommand>();
        break;
    case CommandCode::UNKNOWN:
        cmd = std::make_unique <UnknownCommand>();
        break;
    default:
        break;
    }

    return cmd;
}

void LaserController::run() {
    
    std::string commandString;
    //Thread to track of Keep Alive message
    auto deviceMonitorThread = std::make_unique<std::thread>(&LaserController::monitorThread, this);

    //Get input from STD IO Reader
    //Create Interface pointer using a Factory method.
    std::unique_ptr<IOInterface> ioInterface = std::make_unique<StdIOHandler>();

    try {
        //Main input reader loop to accept laser command
        while (!ioInterface->getInputCommand(commandString)) {

            //Reverse the command if the device is on silly mode
            if (device.isSillyModeOn()) {
                std::reverse(commandString.begin(), commandString.end());
            }

            //Parse command & values from the input string
            CommandData commandData;
            parseCommandDataFromString(commandString, commandData);

            //Create command object
            std::unique_ptr<Command> command = nullptr;
            command = CreateCommand(commandData.GetCommandCode());
            if (command != nullptr) {
                std::string response = command->execute(device, commandData);
                ioInterface->sendResponse(response);
                //Cleanup the command pointer before going for another action
                command.reset();
                commandString.clear();
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "LaserController::Run(): Exception occurred:" << e.what();
    }

    terminateMonitorThread();

    if (deviceMonitorThread != nullptr && deviceMonitorThread->joinable()) {
        deviceMonitorThread->join();
    }
}

void LaserController::terminateMonitorThread() {
    //Terminate the monitor thread
    std::lock_guard<std::mutex> guard(lock);
    monitorThreadHasToDie = true;
}
LaserController::~LaserController(){
}

//Monitor thread to track Keep alive command
void LaserController::monitorThread() {
    //For now, make this loop run indefinitely
    while (!monitorThreadHasToDie) {
        //wait for 1 sec
        try {
            //Check if the keep alive received within allowed 5 seconds time
            std::chrono::duration<double> elapsed_seconds = device.getTimeElapsedSinceLastKeepAliveMessage();
            if (elapsed_seconds.count() > KeepAliveTimeoutPeriodInSeconds) {
                if (device.isLaserActive()) {
                    device.stopLaser();
                }
            }
            std::this_thread::sleep_for(std::chrono::seconds(ThreadTimeoutPeriodInSeconds));
        }
        catch (const std::exception& e) {
            std::cout << "monitorLaserActivity:Exception occurred. Reason: " << e.what();
        }
    }
}
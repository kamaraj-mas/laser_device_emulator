#include "Command.h"

std::string StartCommand::execute(LaserDevice& device, CommandData& cmd) const{
    std::string returnValue = cmd.command;
    if (device.startLaser()) {
        returnValue += successIndicator;
    }
    else {
        returnValue += failureIndicator;
    }

    return returnValue;
}

std::string StopCommand::execute(LaserDevice& device, CommandData& cmd) const{
    std::string returnValue = cmd.command;
    if (device.stopLaser()){
        returnValue += successIndicator;
    }
    else{
        returnValue += failureIndicator;
    }

    return returnValue;
}

std::string StatusCommand::execute(LaserDevice& device, CommandData& cmd) const{
    std::string returnValue = cmd.command;
    //set 1 if laser is active, otherwise set 0
    returnValue +=device.isLaserActive() ? "1" : "0";
    returnValue += successIndicator;
    return returnValue;
}

std::string SetPowerCommand::execute(LaserDevice& device, CommandData& cmd) const {
    std::string returnValue = cmd.command;
    
    //input value is mandatory for SetLaserPower command
    if (cmd.parameters.size() > 0 && device.setLaserPower(atoi(cmd.parameters[0].c_str()))) {
        returnValue += successIndicator;
    }
    else{
        returnValue += failureIndicator;
    }

    return returnValue;
}

std::string GetPowerCommand::execute(LaserDevice& device, CommandData& cmd) const {
    std::string returnValue = cmd.command;
    returnValue += delimiter;
    if(!device.isLaserActive()){ //Return 0 if laser is turned OFF
        returnValue += "0";
    }
    else {
        returnValue += std::to_string(device.getLaserPower());
    }
    
    returnValue += successIndicator;
    return returnValue;
}

std::string EnableSillyModeCommand::execute(LaserDevice& device, CommandData& cmd) const {
    std::string returnValue = cmd.command;
    device.setSillyModeOn();
    returnValue += successIndicator;
    return returnValue;
}

std::string DisableSillyModeCommand::execute(LaserDevice& device, CommandData& cmd) const {
    std::string returnValue = cmd.command;
    device.setSillyModeOFF();
    returnValue += successIndicator;
    return returnValue;
}
 
std::string KeepAliveCommand::execute(LaserDevice& device, CommandData& cmd) const {
    std::string returnValue = cmd.command;
    //reset the keep alive timer 
    device.resetTimer();
    returnValue += successIndicator;
    return returnValue;
}

std::string UnknownCommand::execute(LaserDevice& device, CommandData& cmd) const{
    return "UK!";
}
#include "Command.h"

void StartLaser::execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const
{
    std::string returnValue = cmd.command;
    if (device.startLaser()) {
        returnValue += "#";
    }
    else {
        returnValue += "!";
    }

    if (Callback) {
        Callback(returnValue);
    }
}

void StopLaser::execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const
{
    std::string returnValue = cmd.command;
    if (device.stopLaser()){
        returnValue += "#";
    }
    else{
        returnValue += "!";
    }

    if (Callback) {
        Callback(returnValue);
    }

}

void LaserStatus::execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const{
    std::string returnValues = cmd.command;
    //set 1 if laser is active, otherwise set 0
    returnValues+=device.isLaserActive() ? "1" : "0";
    if (Callback) {
        Callback(returnValues);
    }
}

void SetLaserPower::execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const {
    std::string returnValues = cmd.command;
    
    //input value is mandatory for SetLaserPower command
    if (cmd.parameters.size() > 0 && device.setLaserPower(atoi(cmd.parameters[0].c_str()))) {
            returnValues += "#";
    }
    else{
        returnValues += "!";
    }

    if (Callback) {
        Callback(returnValues);
    }
}

void GetLaserPower::execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const {
    std::string returnValues = cmd.command;
    returnValues += "|";
    if(!device.isLaserActive()){ //Return 0 if laser is turned OFF
        returnValues += "0";
    }
    else {
        returnValues += std::to_string(device.getLaserPower());
    }

    if (Callback) {
        Callback(returnValues);
    }
}

void EnableSillyMode::execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const {
    std::string returnValues = cmd.command;
    device.setSillyModeOn();
    returnValues += "#";
    if (Callback)
        Callback(returnValues);
}

void DisableSillyMode::execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const {
    std::string returnValues = cmd.command;
    device.setSillyModeOFF();
    returnValues += "#";
    if (Callback)
        Callback(returnValues);
}
 
void KeepAlive::execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const {
    std::string returnValues = cmd.command;
    //reset the keep alive timer 
    device.resetTimer();
    returnValues += "#";
    if (Callback)
        Callback(returnValues);
}

void Unknown::execute(LaserDevice& device, CommandData& cmd, std::function<void(std::string)> Callback) const{
    if (Callback)
        Callback("UK!");
}
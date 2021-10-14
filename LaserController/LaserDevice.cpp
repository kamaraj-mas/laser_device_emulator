#include "LaserDevice.h"
#include <iostream>
#include <mutex>

LaserDevice::LaserDevice() :timeWhenLastKeepAliveReceived(std::chrono::system_clock::now())
{
}

bool LaserDevice::IsWithinTheBounds(short value, short low, short high) {
    return !(value < low) && (value <= high);
}

bool LaserDevice::isSillyModeOn()
{
    return sillyModeOn == true;
}

bool LaserDevice::startLaser()
{
    //Start the laser only if it is currently OFF
    if (!laserStarted)
    {
        laserStarted = true;
        timeWhenLastKeepAliveReceived = std::chrono::system_clock::now();
        return laserStarted;
    }
    return !laserStarted;
}

bool LaserDevice::stopLaser()
{
    if (laserStarted)
    {
        laserStarted = false;
        return !laserStarted;
    }
    return laserStarted;
}

bool LaserDevice::isLaserActive(){
    return laserStarted;
}

bool LaserDevice::setLaserPower(short power) {
    //set laser power only if it is ON and the value is within the permitted range 1-100
    if (isLaserActive() && IsWithinTheBounds(power, 1, 100)){
        laserPower = power;
        return true;
    }
    return false;
}

short LaserDevice::getLaserPower(){
    return laserPower;
}

void LaserDevice::setSillyModeOn(){
    sillyModeOn = true;
}
void LaserDevice::setSillyModeOFF() {
    sillyModeOn = false;
}
void LaserDevice::resetTimer(){
    timeWhenLastKeepAliveReceived = std::chrono::system_clock::now();
}

//Monitor thread to track Keep alive command
void LaserDevice::monitorLaserActivity(){
    //For now, make this loop run indefinitely
    try {
        while (!threadHasToDie) {
            //wait for 1 sec
            std::this_thread::sleep_for(std::chrono::seconds(ThreadTimeoutPeriodInSeconds));

            //Check if the keep alive received within allowed 5 seconds time
            std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - timeWhenLastKeepAliveReceived;
            if (elapsed_seconds.count() > KeepAliveTimeoutPeriodInSeconds) {
                if (laserStarted) {
                    stopLaser();
                }
            }
        }
    }
    catch (std::exception e) {
        std::cout << "monitorLaserActivity:Crash handled with Error Msg: " << e.what();
    }
}

void LaserDevice::terminateThread()
{
    std::mutex mX;
    std::lock_guard<std::mutex> guard(mX);
    //set the flag to gracefully terminate the monitor thread
    threadHasToDie = true;
}
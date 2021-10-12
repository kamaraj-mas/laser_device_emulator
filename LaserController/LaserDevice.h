#pragma once

#include <chrono>
#include <thread>

class LaserDevice
{
private:
    short laserPower = 0;
    bool laserStarted = false;
    bool sillyModeOn = false;

    std::chrono::time_point<std::chrono::system_clock> timeWhenLastKeepAliveReceived;
    bool IsWithinTheBounds(short value, short low, short high);
public:
    LaserDevice();
    bool isSillyModeOn();
    bool startLaser();
    bool stopLaser();
    bool isLaserActive();
    bool setLaserPower(short power);
    short getLaserPower();
    void setSillyModeOn();
    void setSillyModeOFF();
    void resetTimer();
    void monitorLaserActivity();
};

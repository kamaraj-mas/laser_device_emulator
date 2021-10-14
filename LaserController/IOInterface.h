#pragma once
#include <string>

//Interface for the command reader, this could be extended to  
//read command from socket/RS232 and output to the same handle
class IOInterface
{
public: 
    virtual bool getInputCommand(std::string& commandString) = 0;
    virtual void sendResponse(std::string response) = 0;
};

//Subclass to read command from Standard IO
class StdIOReader : public IOInterface
{
public:
    StdIOReader() = default;
    bool getInputCommand(std::string& commandString);
    void sendResponse(std::string response);
};

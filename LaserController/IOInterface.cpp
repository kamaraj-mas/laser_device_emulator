#include "IOInterface.h"
#include <algorithm>
#include <sstream>
#include <iostream>

bool StdIOHandler::getInputCommand(std::string& commandString)
{
    return std::getline(std::cin, commandString).eof();
}

void StdIOHandler::sendResponse(std::string response)
{
    std::cout << response <<"\n";
}
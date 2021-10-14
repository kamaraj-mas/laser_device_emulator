#include "IOInterface.h"
#include <algorithm>
#include <sstream>
#include <iostream>

bool StdIOReader::getInputCommand(std::string& commandString)
{
    return std::getline(std::cin, commandString).eof();
}

void StdIOReader::sendResponse(std::string response)
{
    std::cout << response;
}
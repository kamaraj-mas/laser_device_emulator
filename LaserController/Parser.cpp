#include "Parser.h"
#include <sstream>

void Parser::parse(std::string CommandString, CommandData& Cmd)
{
    //Parse laser command
    std::stringstream ss(CommandString);
    std::string subString;

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
#pragma once
#include "Data.h"
class Parser
{
public:
    Parser() {}
    void parse(std::string CommandString, CommandData& Command);
};


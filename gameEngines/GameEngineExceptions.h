#ifndef GAMEENGINE_EXCEPTIONS
#define GAMEENGINE_EXCEPTIONS
#pragma once

#include <iostream>
using namespace std;

namespace gameEngines
{
    class WrongGameStateSettingsException : public std::exception {
    public:

    public:
        WrongGameStateSettingsException(const char* msg) : std::exception(msg) { };
        //char* what();
    };
}

#endif

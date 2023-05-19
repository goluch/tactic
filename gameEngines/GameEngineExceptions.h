#ifndef GAMEENGINE_EXCEPTIONS
#define GAMEENGINE_EXCEPTIONS
#pragma once

#include <iostream>
using namespace std;

namespace gameEngines
{
    class WrongGameStateSettingsException : public std::exception {
    public:
        char* what();
    };
}

#endif

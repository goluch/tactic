#include "GameEngineExceptions.h"

using namespace gameEngines;

char* WrongGameStateSettingsException::what() {
    return "Wrong GameState Settings Exception Exception";
}
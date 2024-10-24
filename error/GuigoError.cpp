//
// Created by guilherme on 07/10/24.
//

#include "GuigoError.h"

#include <iostream>

void GuigoError::error(std::string message, GuigoErrorCode code, int line) {
    std::cout << "Error [" << code << "] at line: " << line << " : " << message << std::endl;
}

void GuigoError::parserError(std::string message, GuigoErrorCode code) {
    std::cout << "Error [" << code << "] " << message << std::endl;
}


void GuigoError::objectError(std::string message, GuigoErrorCode code) {
    std::cout << "Error [" << message << "]" << std::endl;
}
//
// Created by guilherme on 07/10/24.
//

#include "GuigoError.h"

#include <iostream>

void GuigoError::error(std::string message, GuigoErrorCode code, int line) {
    std::cout << "Error [" << code << "] at line: " << line << " : " << message << std::endl;
}

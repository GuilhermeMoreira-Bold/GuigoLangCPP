//
// Created by guilherme on 07/10/24.
//

#ifndef GUIGOERROR_H
#define GUIGOERROR_H
#include <string>

#include "GuigoErrorCode.h"


class GuigoError {
    public:
    static void parserError(std::string message, GuigoErrorCode code);
    static void error(std::string message, GuigoErrorCode code,int line);
    static void objectError(std::string message, GuigoErrorCode code);
    GuigoError();
};



#endif //GUIGOERROR_H

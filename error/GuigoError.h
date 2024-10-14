//
// Created by guilherme on 07/10/24.
//

#ifndef GUIGOERROR_H
#define GUIGOERROR_H
#include <string>

#include "GuigoErrorCode.h"


class GuigoError {
    public:
    static void error(std::string message, GuigoErrorCode code,int line);
    GuigoError();
};



#endif //GUIGOERROR_H

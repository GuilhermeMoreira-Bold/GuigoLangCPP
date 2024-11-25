//
// Created by guilherme on 12/11/24.
//

#ifndef GUIGOFILE_H
#define GUIGOFILE_H
#include <string>

#include "../component/IOComponent.h"


class GuigoFile : public IOComponent<GuigoFile> {
    public:
    ~GuigoFile() override;

    GuigoFile(std::ifstream path);
    std::string& getSource();
private:
    std::string source;
    std::string getFileContent(std::ifstream path);
};

#endif //GUIGOFILE_H

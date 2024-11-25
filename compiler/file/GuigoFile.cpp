//
// Created by guilherme on 12/11/24.
//

#include "GuigoFile.h"

#include <fstream>

GuigoFile::GuigoFile(std:: ifstream path) {
    source = getFileContent(std::move(path));
}

GuigoFile::~GuigoFile() {

}

std::string& GuigoFile::getSource() {
    return source;
}

std::string GuigoFile::getFileContent(std::ifstream path) {
    std::string line;
    std::string source;
    while(std::getline(path,line)) {
        source.append(line + "\n");
    }
    path.close();
    return source;
}

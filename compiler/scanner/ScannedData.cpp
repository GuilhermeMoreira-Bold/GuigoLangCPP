//
// Created by guilherme on 12/11/24.
//
#include "ScannedData.h"
#include <vector>

std::vector<Ref<Token>>& ScannedData::getTokens() {

    return tokens;
}
ScannedData::ScannedData(std::vector<Ref<Token>>& t): tokens(t) {

}

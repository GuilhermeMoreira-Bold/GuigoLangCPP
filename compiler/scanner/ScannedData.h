//
// Created by guilherme on 12/11/24.
//

#ifndef SCANNEDDATA_H
#define SCANNEDDATA_H
#include <list>
#include <memory>
#include <vector>

#include "../component/IOComponent.h"
#include "../lexer/Token.h"

template <typename  T>
using Ref = std::shared_ptr<T>;

class ScannedData : public IOComponent<ScannedData> {
    std::vector<Ref<Token>>& tokens;
    public:
    ScannedData(std::vector<Ref<Token>>& t);
    std::vector<Ref<Token>>& getTokens();
};
#endif //SCANNEDDATA_H

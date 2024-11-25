//
// Created by guilherme on 24/11/24.
//

#ifndef INTERPRETEDDATA_H
#define INTERPRETEDDATA_H
#include <memory>
#include <vector>

#include "../component/IOComponent.h"


template<typename T>
using Ref = std::shared_ptr<T>;

class InterpretedData : public IOComponent<InterpretedData> {


};
#endif //INTERPRETEDDATA_H

//
// Created by guilherme on 11/11/24.
//

#ifndef IOCOMPONENT_H
#define IOCOMPONENT_H
#include "IIOComponent.h"

template<typename Derived>
class IOComponent : public IIOComponent {
  public:
    virtual ~IOComponent() = default;
};
#endif //IOCOMPONENT_H

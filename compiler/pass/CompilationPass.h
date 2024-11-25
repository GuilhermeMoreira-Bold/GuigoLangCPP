//
// Created by guilherme on 11/11/24.
//

#ifndef COMPILATIONPASS_H
#define COMPILATIONPASS_H
#include <string>
#include <type_traits>

#include <iostream>
#include <typeinfo>
#include <memory>

#include "ICompilationPass.h"
#include "../component/IOComponent.h"
#include "../execption/UnexpectedInputType.h"

template <typename I, typename O>
class CompilationPass : public ICompilationPass {
 static_assert(std::is_base_of<IOComponent<I>, I>::value, "I must be from IOComponent<I>");
 static_assert(std::is_base_of<IOComponent<O>, O>::value, "O must be from IOComponent<O>");
public:
    CompilationPass() = default;
    virtual O* pass(I* input) = 0;
    void* run(void *arg) override {
        if(I* typedInput = dynamic_cast<I*>(static_cast<I*>(arg))) {
            return pass(typedInput);
        }
        throw UnexpectedInputType();
    }

};
#endif //COMPILATIONPASS_H

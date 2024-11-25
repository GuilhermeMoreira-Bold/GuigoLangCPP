//
// Created by guilherme on 11/11/24.
//

#ifndef ICOMPILATIONPASS_H
#define ICOMPILATIONPASS_H
#include <typeinfo>
#include <string>

class ICompilationPass {
    public:
    virtual ~ICompilationPass() = default;
    virtual void* run(void* arg) = 0;
    //virtual void* runWithInterceptor(void* arg) = 0;
    virtual const std::type_info& getInputType() = 0;
    virtual const std::type_info& getOutputType() = 0;
    virtual std::string getDebugName() = 0;


};
#endif //ICOMPILATIONPASS_H

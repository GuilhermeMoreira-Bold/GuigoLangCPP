//
// Created by guilherme on 11/11/24.
//

#ifndef COMPILATIONPIPELINE_H
#define COMPILATIONPIPELINE_H
#include <vector>
#include "../component/IOComponent.h"
#include "../pass/ICompilationPass.h"


template<typename Target, typename Source>
bool instanceof(Source* obj) {
    return dynamic_cast<Target*>(obj) != nullptr;
}


class CompilationPipeline {
public:
    std::vector<ICompilationPass*> passes;

    CompilationPipeline insertStage(ICompilationPass* pass) {
        passes.push_back(pass);
        return *this;
    }

    void execute(IIOComponent* input) {
        IIOComponent* currentInput = input;
        std::cout << "Passes size: " << passes.size() << std::endl;
        for (const auto &pass: passes) {
            std::cout << "Executing: " << pass->getDebugName() << std::endl;
            currentInput = runPass(*pass, currentInput);
        }
    }


    IIOComponent* runPass(ICompilationPass &pass, IIOComponent* input) const {
        return static_cast<IIOComponent *>(pass.run(input));
    }

};

#endif //COMPILATIONPIPELINE_H

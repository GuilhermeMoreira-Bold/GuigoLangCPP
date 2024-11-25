//
// Created by guilherme on 11/11/24.
//

#ifndef UNEXPECTEDINPUTTYPE_H
#define UNEXPECTEDINPUTTYPE_H
class UnexpectedInputType : public std::exception {
public:
    const char* what() const noexcept override {
        return "Unexpected input type.";
    }
};
#endif //UNEXPECTEDINPUTTYPE_H

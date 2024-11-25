//
// Created by guilherme on 05/11/24.
//

#ifndef PARSEDDATA_H
#define PARSEDDATA_H
#include <list>
#include <memory>
#include <vector>

#include "../component/IOComponent.h"
#include "../expressions/Expression.h"
template <typename T>
using Ref = std::shared_ptr<T>;
class ParsedData : public IOComponent<ParsedData> {
    std::vector<Ref<Expression>>& expressions;
public:
    std::vector<Ref<Expression>> getExpressions();
    ParsedData(std::vector<Ref<Expression>>& expressions);
};
#endif //PARSEDDATA_H

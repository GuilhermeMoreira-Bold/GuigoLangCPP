//
// Created by guilherme on 12/11/24.
//
#include "ParsedData.h"

#include <list>

std::vector<Ref<Expression>> ParsedData::getExpressions() {
    return expressions;
}

ParsedData::ParsedData(std::vector<Ref<Expression>>& expressions): expressions(expressions) {

}

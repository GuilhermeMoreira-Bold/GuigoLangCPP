//
// Created by guilherme on 23/10/24.
//

#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <utility>
#include "../error/GuigoError.h"
#include "../error/GuigoErrorCode.h"
#include <cmath>

class Object {
    public:
    enum Type {
        BOOLEAN, NUMBER, STRING,NONE, Null
      };
        Type type;
    Type getType() const {
        return type;
    };

    operator double() const {
        return number;
    }

    bool operator ==(const Object &other) const {
        if (type == other.type) {
            return number == other.number || boolean == other.boolean || string == other.string;
        }
        return false;
    }
    std::string toString() const {
        switch (type) {
            case BOOLEAN:
                if (boolean) {
                    return "true";
                }
                return "false";
            case NUMBER:
                if (std::floor(number) == number) {
                    static_cast<int>(number);
                }
                return std::to_string(number);
            case STRING:
                return string;
        }
    }

    void* getValue() {
        switch (type) {
            case BOOLEAN:
                return &boolean;
            case NUMBER:
                return &number;
            case STRING:
                return &string;
            case Null:
                return nullptr;
            case NONE:
                GuigoError::objectError("Unknown type", GuigoErrorCode::UnkowType);
               exit(EXIT_FAILURE);
        }
    }

    explicit Object(std::string string) : type(STRING), string(std::move(string)) {};
    explicit Object(bool boolean) : type(BOOLEAN), boolean(boolean) {};
    explicit Object(double number) : type(NUMBER), number(number) {};
    explicit Object() : type(Type::Null){};

    ~Object() {
        if (type == Type::STRING) {
            string.~basic_string();
        }
    };
    private:

        union {
            bool boolean;
            double number;
            std::string string;

        };
};
#endif //OBJECT_H

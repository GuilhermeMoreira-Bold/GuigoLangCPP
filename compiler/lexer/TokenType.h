//
// Created by guilherme on 07/10/24.
//

#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#define TOKEN_TYPE_LIST \
    X(LeftParent) X(RightParent) X \
    (LeftBrace) X(RightBrace) X \
    (Print) X (And) X (Class) X (Else) X (False) X (True) X (If) X (Null) X (Var) X (Return) X \
    (Bang) X (BangEqual) X \
    (Greater) X (GreaterEqual) X \
    (Less) X (LessEqual) X \
    (Plus) X (Minus) X (Star) X (Slash) X \
    (Mark) X (Comma) X (Dot) X (Semicolon) X \
    (EqualEqual) X (Equal) X \
    (Identifier) X (String) X (Number) X \
    (While) X (Or) X \
    (Unknow) X \
    (Eof)


enum TOKENTYPE {
#define X(name) name,
    TOKEN_TYPE_LIST
#undef X
};

inline std::string tokenTypeToString(TOKENTYPE type) {
    switch (type) {
#define X(name) case name: return #name;
        TOKEN_TYPE_LIST
#undef X
        default : return "Unknown";
    }
}

#endif //TOKENTYPE_H

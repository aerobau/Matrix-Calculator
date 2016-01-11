//
//  token.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 1/10/16.
//  Copyright © 2016 Robau inc. All rights reserved.
//

#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>

//  |ENUM|  TokenType  |ENUM|
//
//  Defines the various types of tokens that can be created when tokenizing a
//  string
enum TokenType {
    IDENTIFIER,         // Any name that links to a mapped function or variable
    OPERATION,          // Infix operations like "*" and "+"
    LITERAL_MATRIX,     // A matrix literal full of values
    LITERAL_DECIMAL,    // A single value
    OPEN_PARENTHESIS,   // Opening parenthesis token
    CLOSE_PARENTHESIS,  // Closing parenthesis token
    END_STATEMENT,      // Statement ender, like ";"
    DELIMITER,          // Delimiter, namely ","
    INVALID             // None of the above.
};

//  |STRUCT|  Token  |STRUCT|
//
//  A simple token structure that has a string that represents what the token is
//  and the type that it is.
struct Token {
    Token(std::string lexume, TokenType type) : lexume(lexume), type(type) {}
    std::string lexume;
    TokenType type;
};

#endif // TOKEN_H_

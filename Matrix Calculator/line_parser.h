//
//  parser.hpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/25/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <stack>
#include "operation.h"

enum TokenType {
    IDENTIFIER,
    OPERATION,
    LITERAL_MATRIX,
    LITERAL_DECIMAL,
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS,
    END_STATEMENT,
    DELIMITER,
    INVALID
};

struct Token {
    Token(std::string, TokenType);
    std::string lexume;
    TokenType type;
};

class LineParser {
public:
    // Constructor
    LineParser(std::string);
    
    // Main parsing function
    std::unique_ptr<SyntaxElement> Parse();
    
private:
    std::string line_;
    std::string::const_iterator line_iter_;
    std::vector<Token> tokens_;
    std::vector<Token>::const_iterator token_iter_;
    std::stack<std::unique_ptr<SyntaxElement>> values_;
    std::stack<std::unique_ptr<Operation>> operations_;
    std::unique_ptr<SyntaxElement> tree_;
    
    void Tokenize();
    void MakeTree();
    
    void ReadWord(std::string::const_iterator, std::string::const_iterator);
    MathMatrix createMatrixFromString(std::string);
    void ReadToken();
};

#endif // PARSER_H_

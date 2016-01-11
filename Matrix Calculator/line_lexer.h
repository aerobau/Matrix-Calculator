//
//  line_lexer.hpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 1/10/16.
//  Copyright © 2016 Robau inc. All rights reserved.
//

#ifndef LINE_LEXER_H_
#define LINE_LEXER_H_

#include <vector>

#include "token.h"

class LineLexer {
public:
    LineLexer(const std::string);
    std::vector<Token> Tokenize();
    
private:
    std::vector<Token> tokens_;
    const std::string line_;
    
    void LexWord(std::string::const_iterator, std::string::const_iterator);
};

#endif // LINE_LEXER_H_

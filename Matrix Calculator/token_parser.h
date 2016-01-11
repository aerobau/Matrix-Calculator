//  token_parser.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/25/15.

#ifndef TOKEN_PARSER_H_
#define TOKEN_PARSER_H_

#include <string>
#include <vector>
#include <stack>

#include "operation.h"
#include "token.h"

//  |CLASS|  TokenParser  |CLASS|
//
//  Represents an object that is constructed with a string and then is called
//  upon to tokenize the string and then build an abstract syntax tree.  This
//  abstract syntax tree is tehn returned to the caller.
class TokenParser {
public:
    // Constructs the TokenParser with the string that will be parsed.
    TokenParser(std::vector<Token>);
    
    // Parses the string and returns the tree that represents it.  Note that the
    // unique pointer that is returned is now owned by the caller, and the tree_
    // variable held by the pareser is now null.
    std::unique_ptr<SyntaxElement> Parse();
    
private:
    // The vector of tokens that are parsed from the line.
    std::vector<Token> tokens_;
    
    // The vector iterator that iterates over the Tokens as the parser builds
    // the tree
    std::vector<Token>::const_iterator token_iter_;
    
    // The stack of values that are read in, these include functions (because
    // all of their inputs follow the identifier within parenthesis), variables,
    // and literals.
    std::stack<std::unique_ptr<SyntaxElement>> values_;
    
    // The stack of operations that are read in.  These are the infix operations
    // that have values before and after them that must be read in as well.
    std::stack<std::unique_ptr<Operation>> operations_;
    
    // Given a string that represents a literal matrix, constructs the matrix
    MathMatrix createMatrixFromString(std::string);
    
    // Reads the next token
    void ReadToken();
};

#endif // PARSER_H_

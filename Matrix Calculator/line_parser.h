//  parser.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/25/15.

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <stack>
#include "operation.h"

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
    Token(std::string, TokenType);
    std::string lexume;
    TokenType type;
};

//  |CLASS|  LineParser  |CLASS|
//
//  Represents an object that is constructed with a string and then is called
//  upon to tokenize the string and then build an abstract syntax tree.  This
//  abstract syntax tree is tehn returned to the caller.
class LineParser {
public:
    // Constructs the LineParser with the string that will be parsed.
    LineParser(std::string);
    
    // Parses the string and returns the tree that represents it.  Note that the
    // unique pointer that is returned is now owned by the caller, and the tree_
    // variable held by the pareser is now null.
    std::unique_ptr<SyntaxElement> Parse();
    
private:
    // The line that is to be parsed.
    std::string line_;
    
    // The line iterator that iterates over the string as the parser tokenizes
    // the line
    std::string::const_iterator line_iter_;
    
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
    
    // The abstract syntax tree that is construted to be returned to the client.
    std::unique_ptr<SyntaxElement> tree_;
    
    // Tokenizes the tree by reading the string and separating substrings out
    // into tokens.
    std::vector<Token> Tokenize();
    
    // Constructs the abstract syntax tree from the tokens that were constructed
    std::unique_ptr<SyntaxElement> MakeTree(std::vector<Token>);
    
    // Reads a word (substring of characters) from two iterators that represent
    // the beginning and the end of the string.
    Token ReadWord(std::string::const_iterator, std::string::const_iterator);
    
    // Given a string that represents a literal matrix, constructs the matrix
    MathMatrix createMatrixFromString(std::string);
    
    // Reads the next token
    void ReadToken();
};

#endif // PARSER_H_

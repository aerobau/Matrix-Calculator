//  line_lexer.cc
//  Matrix Calculator
//
//  Created by Alexander Robau on 1/10/16.

#include "line_lexer.h"

LineLexer::LineLexer(const std::string line) : line_(line) {}

std::vector<Token> LineLexer::Tokenize() {
    std::vector<Token> tokens;
    std::string::const_iterator token_start = line_.begin();
    std::string::const_iterator line_iter = line_.begin();
    while(line_iter != line_.end()) {
        if (*line_iter == '*') {
            LexWord(token_start, line_iter);
            tokens_.push_back(Token("*", OPERATION));
            token_start = ++line_iter;
        } else if (*line_iter == '/') {
            LexWord(token_start, line_iter);
            tokens_.push_back(Token("/", OPERATION));
            token_start = ++line_iter;
        } else if (*line_iter == '+') {
            LexWord(token_start, line_iter);
            tokens_.push_back(Token("+", OPERATION));
            token_start = ++line_iter;
        } else if (*line_iter == '-') {
            LexWord(token_start, line_iter);
            tokens_.push_back(Token("-", OPERATION));
            token_start = ++line_iter;
        } else if (*line_iter == '\\') {
            LexWord(token_start, line_iter);
            tokens_.push_back(Token("\\", OPERATION));
            token_start = ++line_iter;
        } else if (*line_iter == '=') {
            LexWord(token_start, line_iter);
            tokens_.push_back(Token("=", OPERATION));
            token_start = ++line_iter;
        } else if (*line_iter == ' ') {
            LexWord(token_start, line_iter);
            token_start = ++line_iter;
        } else if (*line_iter == '(') {
            LexWord(token_start, line_iter);
            tokens_.push_back(Token("(", OPEN_PARENTHESIS));
            token_start = ++line_iter;
        } else if (*line_iter == ')') {
            LexWord(token_start, line_iter);
            tokens_.push_back(Token(")", CLOSE_PARENTHESIS));
            token_start = ++line_iter;
        } else if (*line_iter == ';') {
            LexWord(token_start, line_iter);
            tokens_.push_back(Token(";", END_STATEMENT));
            token_start = ++line_iter;
        } else if (*line_iter == ',') {
            LexWord(token_start, line_iter);
            tokens_.push_back(Token(",", DELIMITER));
            token_start = ++line_iter;
        } else if (*line_iter == '[') {
            while (*line_iter != ']' && line_iter != line_.end()) {
                ++line_iter;
            }
            
            if (line_iter == line_.end()) {
                // If the loop wasnt terminated from a matching closing bracket,
                // throw an error.
                throw std::logic_error("Missing closing bracket");
            } else {
                ++line_iter;
            }
            
            LexWord(token_start, line_iter);
            token_start = line_iter;
        } else {
            ++line_iter;
        }
    }
    LexWord(token_start, line_iter);
    return tokens_;
}

void LineLexer::LexWord(std::string::const_iterator begin, std::string::const_iterator end) {
    // Getting the substring from the iterators
    std::string word(begin, end);
    if (word.size() == 0) {
        return;  // Word is a null string, simply return
    } else if (*begin == '[') {
        if (*(end - 1) == ']') {
            // Word is a literal matrix and has matching brackets, push back as
            // a LITERAL token
            tokens_.push_back(Token(word, LITERAL_MATRIX));
        } else {
            // Word has opening brackets but not closing brackets, push back and
            // mark INVALID
            tokens_.push_back(Token(word, INVALID));
        }
    } else {
        try {
            double value;
            value = std::stod(word);
            tokens_.push_back(Token(word, LITERAL_DECIMAL));
        } catch (std::exception e) {
            tokens_.push_back(Token(word, IDENTIFIER));
        }
    }
}
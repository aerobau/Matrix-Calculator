//
//  parser.cpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/25/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#include "line_parser.h"
#include "literal.h"
#include "variable_name.h"
#include "function_syntax_element.h"

#include <stack>

Token::Token(std::string lexume, TokenType type) : lexume(lexume), type(type) {}

LineParser::LineParser(std::string line) : line_(line) {}

SyntaxElementPtr LineParser::Parse() {
    Tokenize();
    MakeTree();
    return std::move(tree_);
}

void LineParser::Tokenize() {
    std::string::const_iterator token_start = line_.begin();
    line_iter_ = line_.begin();
    while(line_iter_ != line_.end()) {
        if (*line_iter_ == '*') {
            ReadWord(token_start, line_iter_);
            tokens_.push_back(Token("*", OPERATION));
            token_start = ++line_iter_;
        } else if (*line_iter_ == '/') {
            ReadWord(token_start, line_iter_);
            tokens_.push_back(Token("/", OPERATION));
            token_start = ++line_iter_;
        } else if (*line_iter_ == '+') {
            ReadWord(token_start, line_iter_);
            tokens_.push_back(Token("+", OPERATION));
            token_start = ++line_iter_;
        } else if (*line_iter_ == '-') {
            ReadWord(token_start, line_iter_);
            tokens_.push_back(Token("-", OPERATION));
            token_start = ++line_iter_;
        } else if (*line_iter_ == '\\') {
            ReadWord(token_start, line_iter_);
            tokens_.push_back(Token("\\", OPERATION));
            token_start = ++line_iter_;
        } else if (*line_iter_ == '=') {
            ReadWord(token_start, line_iter_);
            tokens_.push_back(Token("=", OPERATION));
            token_start = ++line_iter_;
        } else if (*line_iter_ == ' ') {
            ReadWord(token_start, line_iter_);
            token_start = ++line_iter_;
        } else if (*line_iter_ == '(') {
            ReadWord(token_start, line_iter_);
            tokens_.push_back(Token("(", OPEN_PARENTHESIS));
            token_start = ++line_iter_;
        } else if (*line_iter_ == ')') {
            ReadWord(token_start, line_iter_);
            tokens_.push_back(Token(")", CLOSE_PARENTHESIS));
            token_start = ++line_iter_;
        } else if (*line_iter_ == ';') {
            ReadWord(token_start, line_iter_);
            tokens_.push_back(Token(";", END_STATEMENT));
            token_start = ++line_iter_;
        } else if (*line_iter_ == ',') {
            ReadWord(token_start, line_iter_);
            tokens_.push_back(Token(",", DELIMITER));
        } else if (*line_iter_ == '[') {
            while (*line_iter_ != ']' && line_iter_ != line_.end()) {
                ++line_iter_;
            }
            ++line_iter_;
            ReadWord(token_start, line_iter_);
            token_start = line_iter_;
        } else {
            ++line_iter_;
        }
    }
}

void LineParser::MakeTree() {
    token_iter_ = tokens_.begin();
    while (token_iter_ != tokens_.end()) {
        ReadToken();
    }
    while (!operations_.empty()) {
        OperationPtr op = std::move(operations_.top());
        operations_.pop();
        if (values_.size() < 2) {
            throw std::logic_error("Too few values");
        }
        op->set_rhs(std::move(values_.top()));
        values_.pop();
        op->set_lhs(std::move(values_.top()));
        values_.pop();
        values_.push(std::move(op));
    }
    tree_ = std::move(values_.top());
}

void LineParser::ReadWord(std::string::const_iterator begin,
                           std::string::const_iterator end) {
    // Getting the substring from the iterators
    std::string word(begin, end);
    if (word.size() == 0) {
        // Word is a null string, simply return
        return;
    } else if (*begin == '[') {
        if (*(end - 1) == ']') {
            // Word is a literal matrix and has matching brackets, push back as a LITERAL token
            tokens_.push_back(Token(word, LITERAL_MATRIX));
        } else {
            // Word has opening brackets but not closing brackets, push back and mark INVALID
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

void LineParser::ReadToken() {
    switch (token_iter_->type) {
        case LITERAL_MATRIX: {
            MathMatrix value(createMatrixFromString(token_iter_->lexume));
            values_.push(SyntaxElementPtr(new Literal(value)));
            break;
        }
            
        case LITERAL_DECIMAL: {
            double value;
            value = std::stod(token_iter_->lexume);
            MathMatrix matrix(extd::matrix<double>({{value}}));
            values_.push(SyntaxElementPtr(new Literal(matrix)));
            break;
        }
            
        case OPERATION:
            operations_.push(OperationPtr(new Operation(token_iter_->lexume)));
            break;
            
        case OPEN_PARENTHESIS: {
            auto start_iter = ++token_iter_;
            while (token_iter_ != tokens_.end() && token_iter_->type != CLOSE_PARENTHESIS) {
                ++token_iter_;
            }
            std::vector<Token> old_tokens = tokens_;
            std::vector<Token>::const_iterator old_token_iter = token_iter_;
            SyntaxElementPtr held_tree = std::move(tree_);
            tokens_ = std::vector<Token>(start_iter, old_token_iter);
            MakeTree();
            values_.push(std::move(tree_));
            tokens_ = old_tokens;
            token_iter_ = old_token_iter;
            tree_ = std::move(held_tree);
            break;
        }
            
        case IDENTIFIER: {
            std::string identifier_name = token_iter_->lexume;
            if (++token_iter_ != tokens_.end()) {
                if (token_iter_->type == OPEN_PARENTHESIS) {
                    FunctionSyntaxElement* element = new FunctionSyntaxElement(identifier_name);
                    while (token_iter_->type != CLOSE_PARENTHESIS) {
                        std::vector<Token>::const_iterator parameter_start = token_iter_;
                        while (token_iter_->type != DELIMITER && token_iter_->type != CLOSE_PARENTHESIS) {
                            ++token_iter_;
                        }
                        std::vector<Token> old_tokens = tokens_;
                        std::vector<Token>::const_iterator old_token_iter = token_iter_;
                        SyntaxElementPtr held_tree = std::move(tree_);
                        tokens_ = std::vector<Token>(parameter_start + 1, token_iter_);
                        MakeTree();
                        element->Add(std::move(tree_));
                        tokens_ = old_tokens;
                        token_iter_ = old_token_iter;
                        tree_ = std::move(held_tree);
                        ++token_iter_;
                    }
                    values_.push(SyntaxElementPtr(element));
                } else {
                    --token_iter_;
                    values_.push(SyntaxElementPtr(new VariableName(identifier_name)));
                }
            } else {
                --token_iter_;
                values_.push(SyntaxElementPtr(new VariableName(identifier_name)));
            }
            break;
        }
            
        default:
            throw std::logic_error("Token not valid");
            break;
    }
    ++token_iter_;
}

MathMatrix LineParser::createMatrixFromString(std::string rep) {
    std::vector<std::vector<double>> container;
    // removing brackets
    rep = std::string(rep.begin() + 1, rep.end() - 1);
    int columns = 0;
    int current_row = 0;
    int current_column = 0;
    std::stringstream stream(rep);
    std::string token;
    while (stream >> token) {
        if (container.size() == 0) {
            container.push_back({});
        }
        if (token == ";") {
            container.push_back(std::vector<double>(columns));
            ++current_row; current_column = 0;
        } else {
            double value;
            value = std::stod(token);
            if (container.size() == 1) {
                ++columns;
                container[current_row].push_back(value);
            } else {
                container[current_row][current_column++] = value;
            }
        }
    }
    return MathMatrix(extd::matrix<double>(container));
}
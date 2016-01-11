//  parser.cc
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/25/15.

#include "token_parser.h"
#include "literal.h"
#include "variable_name.h"
#include "function_syntax_element.h"

#include <stack>

TokenParser::TokenParser(std::vector<Token> tokens)
        : tokens_(tokens), token_iter_(tokens_.begin()) {}

std::unique_ptr<SyntaxElement> TokenParser::Parse() {
    return MakeTree();
}

std::unique_ptr<SyntaxElement> TokenParser::MakeTree() {
    token_iter_ = tokens_.begin();
    while (token_iter_ != tokens_.end()) {
        ReadToken();
    }
    while (!operations_.empty()) {
        std::unique_ptr<Operation> op = std::move(operations_.top());
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
    std::unique_ptr<SyntaxElement> tree = std::move(values_.top());
    values_.pop();
    return tree;
    
}

void TokenParser::ReadToken() {
    switch (token_iter_->type) {
        case LITERAL_MATRIX: {
            MathMatrix value(createMatrixFromString(token_iter_->lexume));
            values_.push(std::unique_ptr<SyntaxElement>(new Literal(value)));
            break;
        }
            
        case LITERAL_DECIMAL: {
            double value;
            value = std::stod(token_iter_->lexume);
            MathMatrix matrix(extd::matrix<double>({{value}}));
            values_.push(std::unique_ptr<SyntaxElement>(new Literal(matrix)));
            break;
        }
            
        case OPERATION: {
            Operation* operation = new Operation(token_iter_->lexume);
            operations_.push(std::unique_ptr<Operation>(operation));
            break;
        }
            
        case OPEN_PARENTHESIS: {
            auto start_iter = ++token_iter_;
            while (token_iter_ != tokens_.end() &&
                   token_iter_->type != CLOSE_PARENTHESIS) {
                ++token_iter_;
            }
            TokenParser sub_parser(std::vector<Token>(start_iter, token_iter_));
            values_.push(sub_parser.Parse());
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
                        TokenParser sub_parser(std::vector<Token>(parameter_start + 1, token_iter_));
                        element->Add(sub_parser.Parse());
                        ++token_iter_;
                    }
                    values_.push(std::unique_ptr<SyntaxElement>(element));
                } else {
                    --token_iter_;
                    values_.push(std::unique_ptr<SyntaxElement>(new VariableName(identifier_name)));
                }
            } else {
                --token_iter_;
                values_.push(std::unique_ptr<SyntaxElement>(new VariableName(identifier_name)));
            }
            break;
        }
            
        case END_STATEMENT:
            break;
            
        default:
            throw std::logic_error("Token not valid");
            break;
    }
    ++token_iter_;
}

MathMatrix TokenParser::createMatrixFromString(std::string rep) {
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
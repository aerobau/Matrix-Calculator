//
//  visitor.cpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/26/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#include "visitor.h"

Visitor::Visitor(VariableDelegateInterface& variable_delegate,
                 FunctionDelegateInterface& function_delegate)
        : variable_delegate_(variable_delegate),
          function_delegate_(function_delegate),
          result_(), assign_value_(), assign_(false) {}

void Visitor::VisitFunctionSyntaxElement(const FunctionSyntaxElement& element) {
    
}

void Visitor::VisitOperation(const Operation& element) {
    std::string type = element.type();
    MathMatrix lhs;
    element.rhs().Accept(*this);
    MathMatrix rhs = result_;
    if (type == "=") {
        assign_ = true;
        assign_value_ = rhs;
        element.lhs().Accept(*this);
    } else if (type == "*") {
        element.lhs().Accept(*this);
        MathMatrix lhs = result_;
        result_ = lhs.Multiply(rhs);
    } else if (type == "/") {
        result_ = MathMatrix();
    } else if (type == "+") {
        element.lhs().Accept(*this);
        MathMatrix lhs = result_;
        result_ = lhs.Add(rhs);
    } else if (type == "-") {
        element.lhs().Accept(*this);
        MathMatrix lhs = result_;
        result_ = lhs.Subtract(rhs);
    } else if (type == "\\") {
        element.lhs().Accept(*this);
        MathMatrix lhs = result_;
        result_ = lhs.LeastSquares(rhs);
    }
}

void Visitor::VisitVariableName(const VariableName& element) {
    MathMatrix var;
    if (assign_) {
        variable_delegate_.SetVariable(element.identifier(), assign_value_);
        assign_ = false;
        result_ = assign_value_;
        assign_value_ = MathMatrix();
    } else if (variable_delegate_.GetVariable(element.identifier(), var)) {
        result_ = var;
    } else {
        throw std::logic_error("Variable does not exist");
    }
}

void Visitor::VisitLiteral(const Literal& element) {
    result_ = element.value();
}
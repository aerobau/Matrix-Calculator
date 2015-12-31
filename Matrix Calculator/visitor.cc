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
          results_(), assign_(false) {}

void Visitor::VisitFunctionSyntaxElement(const FunctionSyntaxElement& element) {
    FunctionInterface* func;
    if (function_delegate_.GetFunction(element.identifier(), *func)) {
        std::vector<MathMatrix> parameters(element.children_count());
        auto iter = element.ChildrenBegin();
        for (unsigned int i = 0; i < element.children_count(); ++i, ++iter) {
            (*iter)->Accept(*this);
            if (results_.size() != 1) {
                std::string err = "Function paramter with non_singular return";
                throw std::logic_error(err);
            }
            parameters[i] = results_[0];
        }
        func->Execute(parameters);
    } else {
        throw std::logic_error("Function does not exist");
        return;
    }
}

void Visitor::VisitOperation(const Operation& element) {
    std::string type = element.type();
    element.rhs().Accept(*this);
    std::vector<MathMatrix> rhs = results_;
    
    std::string arg_err = "Too many parameters";
    if (type == "=") {
        assign_ = true;
        results_ = rhs;
        element.lhs().Accept(*this);
    } else if (type == "*") {
        element.lhs().Accept(*this);
        std::vector<MathMatrix> lhs = results_;
        if (rhs.size() != 1 || lhs.size() != 1) throw std::logic_error(arg_err);
        results_ = { lhs[0].Multiply(rhs[0]) };
    } else if (type == "/") {
        results_ = { MathMatrix() };
    } else if (type == "+") {
        element.lhs().Accept(*this);
        std::vector<MathMatrix> lhs = results_;
        if (rhs.size() != 1 || lhs.size() != 1) throw std::logic_error(arg_err);
        results_ = { lhs[0].Add(rhs[0]) };
    } else if (type == "-") {
        element.lhs().Accept(*this);
        std::vector<MathMatrix> lhs = results_;
        if (rhs.size() != 1 || lhs.size() != 1) throw std::logic_error(arg_err);
        results_ = { lhs[0].Subtract(rhs[0]) };
    } else if (type == "\\") {
        element.lhs().Accept(*this);
        std::vector<MathMatrix> lhs = results_;
        if (rhs.size() != 1 || lhs.size() != 1) throw std::logic_error(arg_err);
        results_ = { lhs[0].LeastSquares(rhs[0]) };
    }
}

void Visitor::VisitVariableName(const VariableName& element) {
    MathMatrix var;
    if (assign_) {
        if (results_.size() != 1) {
            std::string err = "Tried assigning multiple values to one variable";
            throw std::logic_error(err);
        } else {
            variable_delegate_.SetVariable(element.identifier(), results_[0]);
            assign_ = false;
        }
    } else if (variable_delegate_.GetVariable(element.identifier(), var)) {
        results_ = { var };
    } else {
        throw std::logic_error("Variable does not exist");
    }
}

void Visitor::VisitVariableList(const VariableList& element) {
    if (assign_) {
        if (results_.size() != element.VariablesCount()) {
            std::string err = "Mismatched assignment count";
            throw std::logic_error(err);
        } else {
            auto iter = element.VariablesBegin();
            for (unsigned int i = 0; i < results_.size(); ++i) {
                variable_delegate_.SetVariable((*iter)->identifier(),
                                               results_[i]);
            }
            assign_ = false;
        }
    } else {
        // Only assign of variable lists is currently supported
        std::string err = "Variable list used incorrectly";
        throw std::logic_error(err);
    }
}

void Visitor::VisitLiteral(const Literal& element) {
    results_ = { element.value() };
}
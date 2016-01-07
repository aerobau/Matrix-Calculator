//  visitor.cc
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/26/15.

#include "visitor.h"
#include "function_interface.h"
#include "printer.h"

Visitor::Visitor(VariableDelegateInterface& variable_delegate,
                 FunctionDelegateInterface& function_delegate,
                 Printer& printer)
        : variable_delegate_(variable_delegate),
          function_delegate_(function_delegate),
          printer_(printer),
          results_(), assign_(false) {}

void Visitor::VisitFunctionSyntaxElement(const FunctionSyntaxElement& element) {
    // Create FunctionInterface pointer to pass to GetFunction(...)
    FunctionInterface* func;
    if (function_delegate_.GetFunction(element.identifier(), *func)) {
        // Function was found, get the parameters by visiting all of the
        // children of the FunctionSyntaxElement
        std::vector<MathMatrix> parameters(element.ChildrenCount());
        auto iter = element.ChildrenBegin();
        for (unsigned int i = 0; i < element.ChildrenCount(); ++i, ++iter) {
            (*iter)->Accept(*this);
            if (results_.size() != 1) {
                // Parameters that are functions currently can only have one
                // return
                std::string err = "Function paramter with non_singular return";
                throw std::logic_error(err);
            }
            parameters[i] = results_[0];
        }
        results_ = func->Execute(parameters);
    } else {
        throw std::logic_error("Function does not exist");
        return;
    }
}

void Visitor::VisitOperation(const Operation& element) {
    std::string type = element.type();
    
    // Get the value of the right hand side, (the left hand side may be
    // assigning, so wait on getting that)
    element.rhs().Accept(*this);
    std::vector<MathMatrix> rhs = results_;
    
    // Definining a error string
    std::string arg_err = "Too many parameters";
    if (type == "=") {
        // Flag assignment and send to left hand side
        assign_ = true;
        results_ = rhs;
        element.lhs().Accept(*this);
    } else if (type == "*") {
        // Get the left hand side and multiply the lhs with the rhs
        element.lhs().Accept(*this);
        std::vector<MathMatrix> lhs = results_;
        if (rhs.size() != 1 || lhs.size() != 1) {
            throw std::logic_error(arg_err);  // lhs, rhs must be singular
        }
        results_ = { lhs[0].Multiply(rhs[0]) };
    } else if (type == "/") {
        // TODO(aerobau): implement division
        results_ = { MathMatrix() };
    } else if (type == "+") {
        // Get the left hand side and add the lhs with the rhs
        element.lhs().Accept(*this);
        std::vector<MathMatrix> lhs = results_;
        if (rhs.size() != 1 || lhs.size() != 1) {
            throw std::logic_error(arg_err);  // lhs, rhs must be singular
        }
        results_ = { lhs[0].Add(rhs[0]) };
    } else if (type == "-") {
        // Get the left hand side and subtract the lhs with the rhs
        element.lhs().Accept(*this);
        std::vector<MathMatrix> lhs = results_;
        if (rhs.size() != 1 || lhs.size() != 1) {
            throw std::logic_error(arg_err);  // lhs, rhs must be singular
        }
        results_ = { lhs[0].Subtract(rhs[0]) };
    } else if (type == "\\") {
        // Get the left hand side and perform least squares on lhs with rhs
        element.lhs().Accept(*this);
        std::vector<MathMatrix> lhs = results_;
        if (rhs.size() != 1 || lhs.size() != 1) {
            throw std::logic_error(arg_err);  // lhs, rhs must be singular
        }
        results_ = { lhs[0].LeastSquares(rhs[0]) };
    }
}

void Visitor::VisitVariableName(const VariableName& element) {
    MathMatrix var;  // MathMatrix variable to pass to GetVariable
    if (assign_) {
        if (results_.size() != 1) {
            // results_ must be singular for assignment to one variable name
            std::string err = "Tried assigning multiple values to one variable";
            throw std::logic_error(err);
        } else {
            variable_delegate_.SetVariable(element.identifier(), results_[0]);
            assign_ = false;  // Unflag to prevent future errors
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
            // Number of values in results must be equal to the number of names
            // being assigned to
            std::string err = "Mismatched assignment count";
            throw std::logic_error(err);
        } else {
            auto iter = element.VariablesBegin();
            for (unsigned int i = 0; i < results_.size(); ++i) {
                variable_delegate_.SetVariable((*iter),
                                               results_[i]);
            }
            assign_ = false;  // Unflag to prevent future errors
        }
    } else {
        // Only assign of variable lists is currently supported
        std::string err = "Variable list used incorrectly";
        throw std::logic_error(err);
    }
}

void Visitor::VisitLiteral(const Literal& element) {
    // Simply assign the results to the literal value
    results_ = { element.value() };
}
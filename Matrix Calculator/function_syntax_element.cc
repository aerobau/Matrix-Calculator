//  function_syntax_element.cc
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/23/15.

#include "function_syntax_element.h"
#include "visitor.h"

FunctionSyntaxElement::FunctionSyntaxElement(std::string identifier)
        : identifier_(identifier) {}

void FunctionSyntaxElement::Accept(Visitor& v) const {
    v.VisitFunctionSyntaxElement(*this);
}

std::string FunctionSyntaxElement::identifier() const {
    return identifier_;
}
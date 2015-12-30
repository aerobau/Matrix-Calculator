//
//  function_syntax_element.cpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/23/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#include "function_syntax_element.h"
#include "visitor.h"

FunctionSyntaxElement::FunctionSyntaxElement(std::string identifier) : identifier_(identifier) {}

void FunctionSyntaxElement::Add(SyntaxElementPtr element) {
    CompositeSyntaxElement::Add(std::move(element));
}

void FunctionSyntaxElement::Accept(Visitor& v) const {
    v.VisitFunctionSyntaxElement(*this);
}

std::string FunctionSyntaxElement::identifier() const {
    return identifier_;
}
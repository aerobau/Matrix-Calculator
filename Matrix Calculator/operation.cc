//
//  operation.cpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/25/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#include "operation.h"
#include "visitor.h"

Operation::Operation(std::string type) : type_(type) {}

void Operation::set_lhs(std::unique_ptr<SyntaxElement> element) {
    lhs_ = std::move(element);
}

void Operation::set_rhs(std::unique_ptr<SyntaxElement> element) {
    rhs_ = std::move(element);
}

const SyntaxElement& Operation::lhs() const {
    return *lhs_;
}

const SyntaxElement& Operation::rhs() const {
    return *rhs_;
}

void Operation::Accept(Visitor& v) const {
    v.VisitOperation(*this);
}

std::string Operation::type() const {
    return type_;
}
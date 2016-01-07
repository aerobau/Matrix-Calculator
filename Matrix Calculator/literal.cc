//  literal.cc
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/25/15.

#include "literal.h"
#include "visitor.h"

Literal::Literal(MathMatrix value) : value_(value) {}

void Literal::Accept(Visitor& v) const {
    v.VisitLiteral(*this);
}

MathMatrix Literal::value() const {
    return value_;
}
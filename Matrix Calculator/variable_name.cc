//
//  variable_name.cpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/26/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#include "variable_name.h"
#include "visitor.h"

VariableName::VariableName(std::string identifier) : identifier_(identifier) {}

std::string VariableName::identifier() const {
    return identifier_;
}

void VariableName::Accept(Visitor& v) const {
    v.VisitVariableName(*this);
}
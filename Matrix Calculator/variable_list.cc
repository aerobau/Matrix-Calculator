//  variable_list.cc
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/30/15.

#include "variable_list.h"
#include "visitor.h"

void VariableList::Accept(Visitor& v) const {
    v.VisitVariableList(*this);
}

void VariableList::Add(std::string element) {
    variables_.push_back(element);
}

std::size_t VariableList::VariablesCount() const {
    return variables_.size();
}

std::vector<std::string>::const_iterator
VariableList::VariablesBegin() const {
    return variables_.begin();
}

std::vector<std::string>::const_iterator
VariableList::VariablesEnd() const {
    return variables_.end();
}
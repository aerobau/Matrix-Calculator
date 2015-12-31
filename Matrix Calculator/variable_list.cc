//  variable_list.cc
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/30/15.

#include "variable_list.h"
#include "visitor.h"

void VariableList::Accept(Visitor& v) const {
    v.VisitVariableList(*this);
}

void VariableList::Add(std::unique_ptr<VariableName> element) {
    variables_.push_back(std::move(element));
}

std::size_t VariableList::VariablesCount() const {
    return variables_.size();
}

std::vector<std::unique_ptr<VariableName>>::const_iterator
VariableList::VariablesBegin() const {
    return variables_.begin();
}

std::vector<std::unique_ptr<VariableName>>::const_iterator
VariableList::VariablesEnd() const {
    return variables_.end();
}
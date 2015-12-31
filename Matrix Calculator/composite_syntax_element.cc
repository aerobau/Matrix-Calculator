//
//  composite_syntax_element.cpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/26/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#include "composite_syntax_element.h"

void CompositeSyntaxElement::Add(std::unique_ptr<SyntaxElement> element) {
    children_.push_back(std::move(element));
}

std::size_t CompositeSyntaxElement::children_count() const {
    return children_.size();
}

std::vector<std::unique_ptr<SyntaxElement>>::const_iterator
CompositeSyntaxElement::ChildrenBegin() const {
    return children_.begin();
}

std::vector<std::unique_ptr<SyntaxElement>>::const_iterator
CompositeSyntaxElement::ChildrenEnd() const {
    return children_.end();
}
//
//  composite_syntax_element.cpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/26/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#include "composite_syntax_element.h"

void CompositeSyntaxElement::Add(SyntaxElementPtr element) {
    elements_.push_back(std::move(element));
}
//
//  syntax_element.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/23/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#ifndef SYNTAX_ELEMENT_H_
#define SYNTAX_ELEMENT_H_

class Visitor;

#include "math_matrix.h"

class SyntaxElement {
public:
    virtual void Accept(Visitor&) const = 0;
};

typedef std::unique_ptr<SyntaxElement> SyntaxElementPtr;

#endif // SYNTAX_ELEMENT_H_

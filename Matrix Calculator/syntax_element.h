//  syntax_element.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/23/15.

#ifndef SYNTAX_ELEMENT_H_
#define SYNTAX_ELEMENT_H_

class Visitor;

#include <memory>

#include "math_matrix.h"

//  |CLASS|  SyntaxElement  |CLASS|
//
//  Interface to a syntax element that defines the shared Accept(Visitor)
//  function that is required to read the tree.
//
//  Note: all syntax element types will be a subclass of this
class SyntaxElement {
public:
    // Accepts a visitor, and, according to override, dispatches the visitor
    // to visit self
    virtual void Accept(Visitor&) const = 0;
};

#endif // SYNTAX_ELEMENT_H_

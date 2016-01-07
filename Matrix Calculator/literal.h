//  literal.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/25/15.

#ifndef LITERAL_H_
#define LITERAL_H_

#include "syntax_element.h"

//  |CLASS|  Literal  |CLASS|
//
//  A syntax element that holds a matrix literal value that was typed in
//  directly and never assigned to a variable.  Note that this may be the lhs
//  of a variable assignment, or the parameter of a function / operation.
class Literal : public SyntaxElement {
public:
    // Constructs a literal from the math matrix literal it holds
    Literal(MathMatrix);
    
    void Accept(Visitor&) const override;
    
    // Accessor for the literal value being held
    MathMatrix value() const;
    
private:
    // The MathMatrix literal value that this element holds in the syntax tree.
    MathMatrix value_;
};

#endif // LITERAL_H_

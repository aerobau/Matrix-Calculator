//
//  literal.hpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/25/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#ifndef LITERAL_H_
#define LITERAL_H_

#include "syntax_element.h"

class Literal : public SyntaxElement {
public:
    Literal(MathMatrix);
    
    void Accept(Visitor&) const override;
    MathMatrix value() const;
    
private:
    MathMatrix value_;
};

#endif // LITERAL_H_

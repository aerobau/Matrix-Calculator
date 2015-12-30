//
//  composite_syntax_element.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/23/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#ifndef COMPOSITE_SYNTAX_ELEMENT_H_
#define COMPOSITE_SYNTAX_ELEMENT_H_

#include "syntax_element.h"

class CompositeSyntaxElement : public SyntaxElement {
public:
    virtual void Add(SyntaxElementPtr);
    
private:
    std::vector<SyntaxElementPtr> elements_;
};

#endif // COMPOSITE_SYNTAX_ELEMENT_H_

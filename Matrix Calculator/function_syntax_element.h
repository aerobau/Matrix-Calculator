//
//  function_syntax_element.hpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/23/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#ifndef FUNCTION_SYNTAX_ELEMENT_H_
#define FUNCTION_SYNTAX_ELEMENT_H_

#include "composite_syntax_element.h"
#include "function_interface.h"

class FunctionSyntaxElement : public CompositeSyntaxElement {
public:
    explicit FunctionSyntaxElement(std::string);
    
    void Accept(Visitor&) const override;
    
    std::string identifier() const;
    
private:
    std::string identifier_;
};

#endif // FUNCTION_SYNTAX_ELEMENT_H_

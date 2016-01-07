//  function_syntax_element.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/23/15.

#ifndef FUNCTION_SYNTAX_ELEMENT_H_
#define FUNCTION_SYNTAX_ELEMENT_H_

#include "composite_syntax_element.h"

//  |CLASS|  FunctionSyntaxElement  |CLASS|
//
//  Contains a function identifier and overrides the CompositeSyntaxElement
//  class.  The children contained in the CompositeSyntaxElement will be its
//  parameters.
class FunctionSyntaxElement : public CompositeSyntaxElement {
public:
    // Constructs the function syntax element with its identifier.
    explicit FunctionSyntaxElement(std::string);
    
    void Accept(Visitor&) const override;
    
    // Accesses the identifier
    std::string identifier() const;
    
private:
    // Represents the name of the function.  this name will be stored in a map
    // that will hold the pointer ot the actual function begin called
    std::string identifier_;
};

#endif // FUNCTION_SYNTAX_ELEMENT_H_

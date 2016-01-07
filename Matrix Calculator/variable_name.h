//  variable_name.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/26/15.

#ifndef VARIABLE_NAME_H_
#define VARIABLE_NAME_H_

#include "syntax_element.h"

//  |CLASS|  VariableName  |CLASS|
//
//  A syntax element which holds an identifier that names a variable in the
//  specified mapping of variables.  VariableNames are named identifiers
//  that are not reserved keywords and are followed by a set of opening and
//  closing parenthesis
class VariableName : public SyntaxElement {
public:
    // Constructor that initializes the VariableName with a sting corresponding
    // to the identifier
    VariableName(std::string);
    
    // Accessor for the identifier
    std::string identifier() const;
    
    void Accept(Visitor&) const override;
    
private:
    // String that represents the name / identifier of the variable
    std::string identifier_;
};

#endif /* variable_name_hpp */

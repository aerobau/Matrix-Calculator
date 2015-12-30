//  variable_delegate_interface.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/23/15.

#ifndef VARIABLE_DELEGATE_INTERFACE_H_
#define VARIABLE_DELEGATE_INTERFACE_H_

#include <string>

class MathMatrix;

//  |CLASS|  SessionDelegateInterface  |CLASS|
//
//  An interface which describes the functions necessary to get and set
//  variables in the session and get and set the functions in the session
class VariableDelegateInterface {
public:
    // Passes a std::string that is the variable name that needs to be retrieved
    // and a MathMatrix by reference and sets that math matrix to the variable
    // if it exists and returns true.  If it does not exist, returns false and
    // does not assign the reference
    virtual bool GetVariable(std::string, MathMatrix&) const = 0;
    
    // Passes a std::string that is the variable name that needs to be set and
    // a math matrix to set it to, then sets the variable.  If the variable does
    // not yet exist, creates a new variable for the name.
    virtual void SetVariable(std::string, const MathMatrix&) = 0;
};

#endif // VARIABLE_DELEGATE_INTERFACE_H_

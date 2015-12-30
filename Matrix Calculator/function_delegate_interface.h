//  function_delegate_interface.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/29/15.

#ifndef FUNCTION_DELEGATE_INTERFACE_H_
#define FUNCTION_DELEGATE_INTERFACE_H_

class FunctionInterface;

class FunctionDelegateInterface {
    // Passes a std::string that is the function name that needs to be retrieved
    // and a MathMatrix by reference and sets that math matrix to the function
    // if it exists and returns true.  If it does not exist, returns false and
    // does not assign the reference
    virtual bool GetFunction(std::string, FunctionInterface&) const = 0;
    
    // Passes a std::string that is the function name that needs to be set and
    // a math matrix to set it to, then sets the variable.  If the function does
    // not yet exist, creates a new mapping to the function for the name.
    virtual void SetFunction(std::string, const FunctionInterface&) = 0;
};

#endif // FUNCTION_DELEGATE_INTERFACE_H_

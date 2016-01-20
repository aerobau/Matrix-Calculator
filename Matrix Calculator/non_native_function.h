//
//  non_native_function.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/29/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#ifndef NON_NATIVE_FUNCTION_H_
#define NON_NATIVE_FUNCTION_H_

#include "function_interface.h"
#include "function_delegate_interface.h"
#include "variable_delegate_interface.h"
#include "syntax_element.h"
#include <map>

//  |CLASS|  NonNativeFunction  |CLASS|
//
//  Class that represents a function that can be defined by a function
//  declaration and a function body.  This function will be able to make use of
//  primitive infix operators, NativeFunctions, and other defined
//  NonNativeFunctions
//
//  Function declaration examples
//  func example(a, b, c) -> d, e {
//      d = a + b + c;
//      e = a - b - c;
//  }
//
//  func exampleB(a, b, c) -> d, e, f {
//      d, e = example(a, b, c);
//      f = d + e;
//  }
class NonNativeFunction : public FunctionInterface, VariableDelegateInterface {
public:
    // Initializes the NonNativeFunction by adding the local variable names
    // to the map as empty math matrices and assigning the input and output
    // vectors of math matrix pointers to the corresponding matrices that
    // the map holds.
    //
    // Thus, the input and output matrices will be accessable both via the map
    // with their corresponding variable names and the input and output
    // matrices.
    //
    // Also taks a FunctionDelegateInterface reference so that it has access to
    // outside functions and takes a string that represents the function's body.
    NonNativeFunction(std::vector<std::string>, std::vector<std::string>,
                      FunctionDelegateInterface&, std::string);
    
    // Override of the execute function.  In this override, the syntax_trees_
    // vector is iterated over and each tree i interpretated by a visitor
    std::vector<MathMatrix> Execute(const std::vector<MathMatrix>) override;
    
    // Returns the size of the inputs_ and outputs_ vectors
    int inputs_count() const override;
    int outputs_count() const override;
    
    // Overriding the GetVariable and SetVariable functions from
    // VariableDelegateInterface so the Visitor can use local variables
    bool GetVariable(std::string, MathMatrix&) const override;
    void SetVariable(std::string, const MathMatrix&) override;
    
    std::string function_body() const;
    
    // Sets the function body, and parses the body and creates a syntax tree for
    // each line of the function, adding it to the syntax_trees_ vector.
    void set_function_body(std::string);
    
private:
    // A map that holds all of the local variables within the function.
    // The visitor uses these as it iterates through the syntax trees.
    std::map<std::string, MathMatrix> local_variables_;
    
    // Vectors of pointers to the inputs and outputs of the function within the
    // local_variables_ map.
    std::vector<MathMatrix*> inputs_;
    std::vector<MathMatrix*> outputs_;
    
    // The function delegate the function is using, which allows access to
    // exterior functions
    FunctionDelegateInterface& function_delegate_;
    
    // The function body as a raw string.
    std::string function_body_;
    
    // The syntax_trees_ compiled from the function body.
    std::vector<std::unique_ptr<SyntaxElement>> syntax_trees_;
    
    // Function to reset all of the variables in the local variable map to the
    // empty matrices to avoid unforseen errors
    void ResetLocalVariables();
};

#endif // NON_NATIVE_FUNCTION_H_

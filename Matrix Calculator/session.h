//
//  session.hpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/23/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#ifndef SESSION_H_
#define SESSION_H_

#include "variable_delegate_interface.h"
#include "function_delegate_interface.h"
#include "function_syntax_element.h"
#include <iostream>
#include <map>

//  |CLASS|  Session  |CLASS|
//
//  Handles user input and the storing of variables.  Utilizes the parser to
//  read user input and make SyntaxElementTrees.  Additionally, utilizes a
//  Visitor class to traverse the syntax tree and perform user operations.
class Session : public VariableDelegateInterface, FunctionDelegateInterface {
public:
    Session();
    
    // Implementation of the SessionDelegateInterface, see header of
    // SessionDelegateInterface
    bool GetVariable(std::string, MathMatrix&) const override;
    void SetVariable(std::string, const MathMatrix&) override;
    bool GetFunction(std::string, FunctionInterface&) const override;
    void SetFunction(std::string, const FunctionInterface&) override;
    
    // Starts the session.  Entry point for most aspects of the program, returns
    // Reads user input and creates, assigns, and makes use of variables and
    // functions in its map.
    //
    // NOTE: This is a long runtime function.  It is basically the main function
    // of the session and contains all logic to handle user input and pass input
    // along to the parser.
    void Run();
    
private:
    // Mappings of variables and functions to std::string names for O(n)
    // retrieval of items.
    std::map<std::string, MathMatrix> variables_;
    std::map<std::string, std::unique_ptr<FunctionInterface>> functions_;
};

#endif // SESSION_H_

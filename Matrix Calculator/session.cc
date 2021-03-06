//
//  session.cpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/23/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#include "session.h"
#include "line_lexer.h"
#include "token_parser.h"
#include "visitor.h"
#include "native_function_definitions.h"
#include "printer.h"


// CONSTRUCTORS //
Session::Session()
        : variables_(), functions_(NativeDefinitions::CreateFunctions()) {}

bool Session::GetVariable(std::string name, MathMatrix& value) const {
    auto location = variables_.find(name);
    if (location == variables_.end()) {
        // Mapping to name doesn't exist, return false
        return false;
    } else {
        // Mapping to name does exist, assign to value and return true;
        value = location->second;
        return true;
    }
}

void Session::SetVariable(std::string name, const MathMatrix& value) {
    variables_[name] = value;
}

bool Session::GetFunction(std::string name, FunctionInterface& value) const {
    auto location = functions_.find(name);
    if (location == functions_.end()) {
        // Mapping to name doesn't exist, return false
        return false;
    } else {
        // Mapping to name does exist, assign to value and return true
        value = *location->second;
        return true;
    }
}

void Session::SetFunction(std::string name, const FunctionInterface& value) {
    std::unique_ptr<FunctionInterface> added;
    *added = value;
    functions_[name] = std::move(added);
}

void Session::Run() {
    // If the variables are not empty, go ahead and print out the current
    // variables at the start of the session to inform the user of what is
    // availible
    if (!variables_.empty()) {
        std::cout << "Variables for this session: " << std::endl;
        for (auto iter = variables_.begin(); iter != variables_.end(); ++iter) {
            std::cout << iter->first << " = " << std::endl
                      << iter->second.ToString() << std::endl;
        }
    }
    
    std::string line_in;
    MathMatrix print_var;
    
    bool done = false;
    while (!done) {
        std::cout << "M << ";
        std::cin.clear();
        std::getline(std::cin, line_in);
        if (line_in == "exit") {
            done = true;  // Exit keyword submitted, flag to exit the session
        } else {
            // Parse the line into a SyntaxElement tree and visit the tree's
            // elements with a visitor to interpret.
            //
            // NOTE: The visitor holds a SessionDelegateInterface so that it can
            // edit the variables and functions in the session
            LineLexer lexer(line_in);
            TokenParser parser(lexer.Tokenize());
            std::unique_ptr<SyntaxElement> tree = parser.Parse();
            std::unique_ptr<Printer> printer(new Printer(&std::cout));
            Visitor v(*this, *this, *printer);
            tree->Accept(v);
            if (printer->valid()) printer->Print();
        }
    }
}
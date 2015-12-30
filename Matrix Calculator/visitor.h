//
//  visitor.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/23/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#ifndef VISITOR_H_
#define VISITOR_H_

#include "function_syntax_element.h"
#include "operation.h"
#include "variable_name.h"
#include "literal.h"
#include "variable_delegate_interface.h"
#include "function_delegate_interface.h"

//  |CLASS|  Visitor  |CLASS|
//
//  Simple visitor class that defines all of the functions necessary to visit
//  each of the items in the tree.  This is an implementation of the Visitor
//  design pattern.  As it visits members of the tree, the Visitor will
//  determine the result of the tree and perform its operations.
class Visitor {
public:
    Visitor(VariableDelegateInterface&, FunctionDelegateInterface&);
    
    // Visits a given FunctionSyntaxElement in the tree.  This will perform the
    // given function by passing it's children as a vector of MathMatrix to the
    // execute function.
    void VisitFunctionSyntaxElement(const FunctionSyntaxElement&);
    void VisitOperation(const Operation&);
    void VisitVariableName(const VariableName&);
    void VisitLiteral(const Literal&);
    
private:
    MathMatrix result_;
    MathMatrix assign_value_;
    bool assign_;
    VariableDelegateInterface& variable_delegate_;
    FunctionDelegateInterface& function_delegate_;
};

#endif // VISITOR_H_

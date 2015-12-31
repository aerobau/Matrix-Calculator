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
#include "variable_list.h"
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
    
    // Visits a given operation element.  This will perform the operation by
    // utilizing the rhs and lhs pointers and the infix operation represented
    // by the string the operator holds
    void VisitOperation(const Operation&);
    
    // Visits a given variable name.  This will look up the variable name and
    // get the associated value.  It will then store that value in the result
    // for use by operation and function visitations.  Is able to be assigned as
    // well.
    void VisitVariableName(const VariableName&);
    
    // Visits a given variable list.  This will look up the variable names and
    // get the associated values.  It will then store those values in the result
    // for use by operation and funcito visitations.  Is able to be assigned as
    // well.
    void VisitVariableList(const VariableList&);
    
    // Visits a given literal.  This will retireve the literal MathMatrix value
    // and store it in the result for use by operation and function visitations
    void VisitLiteral(const Literal&);
    
private:
    // Holding container for elements that the visitor must keep track of during
    // traversal.  note that when the visitor visits an object, this result will
    // be updated to reflect the result of the below tree it just visited.  This
    // is a vector because functions can have multiple return values
    std::vector<MathMatrix> results_;
    
    // Boolean that represents whether the object being visited is the lhs of an
    // assignment operator and thus needs to be assigned to the value.  When
    // true this flags the visitor to set the variable when it visits a variable
    // name.
    bool assign_;
    
    // The variable and function delegate that willb e used to look up and set
    // variables and functions from maps that are held by the session or some
    // other outside source.
    VariableDelegateInterface& variable_delegate_;
    FunctionDelegateInterface& function_delegate_;
};

#endif // VISITOR_H_

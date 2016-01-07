//  operation.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/25/15.

#ifndef OPERATION_H_
#define OPERATION_H_

#include "composite_syntax_element.h"
#include <string>

//  |CLASS|  Operation  |CLASS|
//
//  The representation of infix operations in the syntax tree.  These are
//  separate from the functions because they are binary by definition and
//  are placed in between their parameters.  This means that they must be
//  evaluated with a stack type operation and thus are separated out.
class Operation : public SyntaxElement {
public:
    // Constructs an operation from the string that is infixed between the two
    // parameters.  "*" for example would be multiplication
    Operation(std::string);
    
    // Functions to set the left hand and right hand sides of the operation.
    // Note:  The operation holds its parameters as children in the tree.
    void set_lhs(std::unique_ptr<SyntaxElement>);
    void set_rhs(std::unique_ptr<SyntaxElement>);
    
    // Accessors for the lhs and rhs of the operation, returns them as
    // references to what the operation owns as a pointer
    const SyntaxElement& lhs() const;
    const SyntaxElement& rhs() const;
    
    void Accept(Visitor&) const override;
    
    // Accessor for the type of the operation, which is the string
    // representation of the operation that is infixed between its operands in
    // the syntax.
    std::string type() const;
    
private:
    // Represents the operation ("*", "+", etc)
    std::string type_;
    
    // Owned pointers to the left hand side and right hand side of the function
    // using unique_ptr smart pointers to manage memory.
    std::unique_ptr<SyntaxElement> lhs_;
    std::unique_ptr<SyntaxElement> rhs_;
};

#endif // OPERATION_H_

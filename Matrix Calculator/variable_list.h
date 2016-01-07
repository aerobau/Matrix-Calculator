//  variable_list.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/30/15.

#ifndef VARIABLE_LIST_H_
#define VARIABLE_LIST_H_

#include "variable_name.h"

//  |CLASS|  VariableList  |CLASS|
//
//  Represents a set of variable names that can be assigned from a function with
//  multiple returns.  Is basically a composite element with a set of
//  VariableName children, but does not override CompositeSyntaxElement because
//  it knows, and needs to always know, the type of its children (VariableName)
class VariableList : public SyntaxElement {
public:
    void Accept(Visitor&) const override;
    
    // Function to be able to add a child to the vector.  No need for a removal
    // ability here because the tree will be built, then read, not deconstructed
    // or edited child by child.
    void Add(std::string);
    
    // Function that gets the number of children in the composite.
    std::size_t VariablesCount() const;
    
    // Function that creates an iterator for the vector at the beginning
    std::vector<std::string>::const_iterator
    VariablesBegin() const;
    
    // Function that creates an iterator for the vector at the end
    std::vector<std::string>::const_iterator
    VariablesEnd() const;
    
private:
    std::vector<std::string> variables_;
};

#endif // VARIABEL_LIST_H_

//  variable_list.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/30/15.

#ifndef VARIABLE_LIST_H_
#define VARIABLE_LIST_H_

#include "variable_name.h"

class VariableList : public SyntaxElement {
public:
    void Accept(Visitor&) const override;
    
    // Function to be able to add a child to the vector.  No need for a removal
    // ability here because the tree will be built, then read, not deconstructed
    // or edited child by child.
    virtual void Add(std::unique_ptr<VariableName>);
    
    // Function that gets the number of children in the composite.
    std::size_t VariablesCount() const;
    
    // Function that creates an iterator for the vector at the beginning
    std::vector<std::unique_ptr<VariableName>>::const_iterator
    VariablesBegin() const;
    
    // Function that creates an iterator for the vector at the end
    std::vector<std::unique_ptr<VariableName>>::const_iterator
    VariablesEnd() const;
    
private:
    std::vector<std::unique_ptr<VariableName>> variables_;
};

#endif // VARIABEL_LIST_H_

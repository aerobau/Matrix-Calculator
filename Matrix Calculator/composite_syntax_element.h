//
//  composite_syntax_element.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/23/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#ifndef COMPOSITE_SYNTAX_ELEMENT_H_
#define COMPOSITE_SYNTAX_ELEMENT_H_

#include "syntax_element.h"

//  |CLASS|  CompositeSyntaxElement  |CLASS|
//
//  A subclass of SyntaxElement which can hold child syntax elements in a
//  a constainer.  Has access to an iterator over it's children and the ability
//  to add children.
class CompositeSyntaxElement : public SyntaxElement {
public:
    // Function to be able to add a child to the vector.  No need for a removal
    // ability here because the tree will be built, then read, not deconstructed
    // or edited child by child.
    virtual void Add(std::unique_ptr<SyntaxElement>);
    
    // Function that gets the number of children in the composite.
    std::size_t children_count() const;
    
    // Function that creates an iterator for the vector at the beginning
    std::vector<std::unique_ptr<SyntaxElement>>::const_iterator
    ChildrenBegin() const;
    
    // Function that creates an iterator for the vector at the end
    std::vector<std::unique_ptr<SyntaxElement>>::const_iterator
    ChildrenEnd() const;


private:
    std::vector<std::unique_ptr<SyntaxElement>> children_;
};

#endif // COMPOSITE_SYNTAX_ELEMENT_H_

//
//  operation.hpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/25/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#ifndef OPERATION_H_
#define OPERATION_H_

#include "composite_syntax_element.h"
#include <string>

class Operation : public SyntaxElement {
public:
    Operation(std::string);
    void set_lhs(SyntaxElementPtr);
    void set_rhs(SyntaxElementPtr);
    const SyntaxElement& lhs() const;
    const SyntaxElement& rhs() const;
    void Accept(Visitor&) const override;
    std::string type() const;
    
private:
    std::string type_;
    SyntaxElementPtr lhs_;
    SyntaxElementPtr rhs_;
};

typedef std::unique_ptr<Operation> OperationPtr;

#endif // OPERATION_H_

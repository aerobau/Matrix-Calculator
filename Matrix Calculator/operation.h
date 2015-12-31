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
    void set_lhs(std::unique_ptr<SyntaxElement>);
    void set_rhs(std::unique_ptr<SyntaxElement>);
    const SyntaxElement& lhs() const;
    const SyntaxElement& rhs() const;
    void Accept(Visitor&) const override;
    std::string type() const;
    
private:
    std::string type_;
    std::unique_ptr<SyntaxElement> lhs_;
    std::unique_ptr<SyntaxElement> rhs_;
};

#endif // OPERATION_H_

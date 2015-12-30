//
//  variable_name.hpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/26/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#ifndef VARIABLE_NAME_H_
#define VARIABLE_NAME_H_

#include "syntax_element.h"

class VariableName : public SyntaxElement {
public:
    VariableName(std::string);
    
    std::string identifier() const;
    void Accept(Visitor&) const override;
    
private:
    std::string identifier_;
};

#endif /* variable_name_hpp */

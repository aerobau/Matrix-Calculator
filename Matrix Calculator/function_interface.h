//  function_interface.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/23/15.

#ifndef FUNCTION_INTERFACE_H_
#define FUNCTION_INTERFACE_H_

#include "math_matrix.h"

class FunctionInterface {
public:
    virtual std::vector<MathMatrix>
        Execute(const std::vector<MathMatrix>) = 0;
    virtual int inputs_count() const = 0;
    virtual int outputs_count() const = 0;
};

#endif // FUNCTION_INTERFACE_H_

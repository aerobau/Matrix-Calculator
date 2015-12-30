//
//  native_function.hpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/29/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#ifndef NATIVE_FUNCTION_H_
#define NATIVE_FUNCTION_H_

#include "function_interface.h"

class NativeFunction : public FunctionInterface {
public:
    // Constructor takes a function pointer for the native function, a vector
    // of input matrices and returns a vector of output matrices
    NativeFunction(std::vector<MathMatrix> (*)(const std::vector<MathMatrix>),
                   int, int);
    
    // Overriden function to execute the function.  Simply forwards the request
    // to the native native function pointer
    std::vector<MathMatrix>
        Execute(const std::vector<MathMatrix>) override;
    
    int inputs_count() const override;
    int outputs_count() const override;
    
private:
    std::vector<MathMatrix> (*ExecuteNative)(const std::vector<MathMatrix>);
    int inputs_count_;
    int outputs_count_;
};

#endif // NATIVE_FUNCTION_H_

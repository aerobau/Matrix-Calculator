//  native_functions_definitions.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/29/15.

#ifndef NATIVE_FUNCTION_DEFINITIONS_H_
#define NATIVE_FUNCTION_DEFINITIONS_H_

#include "math_matrix.h"

namespace native_function_definitions {
    std::vector<MathMatrix> eigenvalues(std::vector<MathMatrix> inputs) {
        return {inputs[0].eigenvalues()};
    }
    
    std::vector<MathMatrix> qr(std::vector<MathMatrix> inputs) {
        return
    }
    
}

#endif // NATIVE_FUNCTION_DEFINITIONS_H_

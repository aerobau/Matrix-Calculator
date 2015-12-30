//  native_function.cc
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/29/15.

#include "native_function.h"

NativeFunction::
NativeFunction(std::vector<MathMatrix>
               (*ExecuteNative)(const std::vector<MathMatrix>),
               int inputs_count, int outputs_count)
        : ExecuteNative(ExecuteNative),
          inputs_count_(inputs_count), outputs_count_(outputs_count) {}

int NativeFunction::inputs_count() const {
    return inputs_count_;
}

int NativeFunction::outputs_count() const {
    return outputs_count_;
}

std::vector<MathMatrix> NativeFunction::
Execute(const std::vector<MathMatrix> inputs) {
    return ExecuteNative(inputs);  // Forwards request to function pointer
}
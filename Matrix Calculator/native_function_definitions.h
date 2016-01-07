//  native_functions_definitions.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/29/15.

#ifndef NATIVE_FUNCTION_DEFINITIONS_H_
#define NATIVE_FUNCTION_DEFINITIONS_H_

#include "math_matrix.h"
#include "native_function.h"
#include <string>
#include <map>

namespace NativeDefinitions {
    std::vector<MathMatrix> Eigenvalues(const std::vector<MathMatrix> inputs) {
        return { inputs[0].Eigenvalues() };
    }
    
    std::vector<MathMatrix>
    QRDecomposition(const std::vector<MathMatrix> inputs) {
        return inputs[0].QRDecomposition();
    }
    
    std::vector<MathMatrix> Diagonal(const std::vector<MathMatrix> inputs) {
        return { inputs[0].Diagonal() };
    }
    
    std::vector<MathMatrix> Determinant(const std::vector<MathMatrix> inputs) {
        double det = inputs[0].Determinant();
        std::vector<std::vector<double>> container = {{ det }};
        return { MathMatrix(extd::matrix<double>(container)) };
    }
    
    std::vector<MathMatrix>
    SVDDecomposition(const std::vector<MathMatrix> inputs) {
        return inputs[0].SVDDecomposition();
    }
    
    std::map<std::string, std::unique_ptr<FunctionInterface>>
    CreateFunctions() {
        std::map<std::string, std::unique_ptr<FunctionInterface>> functions;
        
        functions["Eigenvalues"] =
        std::unique_ptr<FunctionInterface>(new NativeFunction(Eigenvalues,
                                                              1, 1));
        
        functions["QRDecomposition"] =
        std::unique_ptr<FunctionInterface>(new NativeFunction(QRDecomposition,
                                                              1, 2));
        
        functions["Diagonal"] =
        std::unique_ptr<FunctionInterface>(new NativeFunction(Diagonal,
                                                              1, 1));
        
        functions["Determinant"] =
        std::unique_ptr<FunctionInterface>(new NativeFunction(Determinant,
                                                              1, 1));
        
        functions["SVDDecomposition"] =
        std::unique_ptr<FunctionInterface>(new NativeFunction(SVDDecomposition,
                                                              1, 3));
        
        return functions;
    }
}

#endif // NATIVE_FUNCTION_DEFINITIONS_H_

//  math_matrix.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/19/15.

#ifndef DOUBLE_MATRIX_H_
#define DOUBLE_MATRIX_H_

#include <sstream>

#include "matrix.h"

//  |CLASS|  MathMatrix  |CLASS|
//
//  A class that adapts the extd::matrix<T> object to be a matrix organized set
//  of double precision floating point values.  This matrix is able to do major
//  operations related to matrix and vector multiplication.
class MathMatrix {
public:
    MathMatrix();
    explicit MathMatrix(extd::matrix<double>);
    MathMatrix(std::size_t, std::size_t);
    MathMatrix(const MathMatrix&) = default;
    
    ~MathMatrix() = default;
    
    MathMatrix& operator=(const MathMatrix&) = default;
    
    // Returns a reference to the double element at the given (column, row)
    // index.  Has a const counterpart allows use in const environments.
    double& operator()(int, int);
    const double& operator()(int, int) const;
    
    // Multiplies two math matrices by passing in the right hand side of the
    // operation as a parameter
    //
    // Note that this is const, and has a const MathMatrix parameter it creates
    // a new MathMatrix to represent the result of the function to maintain
    // constant parameters
    MathMatrix Multiply(const MathMatrix) const;
    
    // Adds two math matrices by passing in the right hand side of the operation
    // as a paramter.  Has the same const operation as multiply function above
    MathMatrix Add(const MathMatrix) const;
    
    // Subtracts two math matrices by passing in the right hand side of the
    // operation as a paramter.  Has the same const operation as multiply
    // function above
    MathMatrix Subtract(const MathMatrix) const;
    
    // Finds least squares solution between a MathMatrix and a given column
    // vector to get the solution uses the QR decomposition method.
    //
    // Note that once again the result is created as a new MathMatrix with const
    // parameters
    MathMatrix LeastSquares(const MathMatrix) const;
    
    // Gets the diagonal of the matrix as a row vector.
    //
    // Note: math vectors are not their own class, and instead are represented
    // as math matrices
    MathMatrix Diagonal() const;
    
    // Calculates the determinant of the matrix and returns it as a double
    // precision decimal value
    double Determinant() const;
    
    // Returns the eigenvalues of the matrix as a column vector within the math
    // matrix.  This utilizes a repeated qr method to converge the eigenvalues.
    MathMatrix Eigenvalues() const;
    
    // Calculates the SVD decomposition of the matrix. This will have three
    // values, a MathMatrix holding the U matrix, a MathMatrix holding the S
    // singular values, and V holding the V matrix.  These will be returned as a
    // vector of MathMatrix.
    std::vector<MathMatrix> SVDDecomposition() const;
    
    // Calculates the QRDecomposition of the matrix.  This will have two values,
    // a MathMatrix holding the Q matrix and a MathMatrix holding the R matrix.
    // These once again will be returned as aa vector of the MathMatrix
    std::vector<MathMatrix> QRDecomposition() const;
    
    // Converts the matrix to the reverse row echelon form of the matrix.
    // Note: mutates the matrix.
    void RREF();
    
    // Submethod of RREF, mutates the matrix into a upper triangular form.
    // Note: mutates the matrix.
    void Gauss();
    
    // Submethod of RREF, converts a upper-triangular form of a matrix into the
    // reduced row echelon form by back substituting the values for the
    // variables.
    // Note: mutates the matrix.
    void Backsub();
    
    extd::matrix_size Size() const;
    std::size_t ColumnSize() const;
    std::size_t RowSize() const;
    
    // Returns true if the matrix has only one column
    bool IsColumnVector() const;
    
    // Returns true if the matrix has only one row
    bool IsRowVector() const;
    
    // Returns true if the matrix is either a row or a column vector
    bool IsVector() const;
    
    // Returns true if the matrix has an equal number of rows and columns
    bool IsSquare() const;
    
    // Returns true if the matrix contains a single value
    bool IsSingleValue() const;
    
    std::string ToString() const;
    
private:
    // The matrix representation that holds the double precision values that
    // make up the matrix.  This object is a wrapping of a two dimmensional
    // vector with additional operations and iterators
    extd::matrix<double> matrix_;
};

#endif // DOUBLE_MATRIX_H_

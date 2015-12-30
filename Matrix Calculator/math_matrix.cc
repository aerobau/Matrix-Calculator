//  math_matrix.cc
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/19/15.

#include "math_matrix.h"

MathMatrix::MathMatrix() : matrix_() {};

MathMatrix::MathMatrix(extd::matrix<double> matrix) : matrix_(matrix) {}

MathMatrix::MathMatrix(std::size_t rows, std::size_t columns)
: matrix_(extd::matrix<double>(rows, columns)) {}

double& MathMatrix::operator()(int row, int column) {
    return matrix_(row, column);
}

const double& MathMatrix::operator()(int row, int column) const {
    return matrix_(row, column);
}

double MathMatrix::Determinant() const {
    return 0.0; // TODO: implement determinant
}

MathMatrix MathMatrix::Eigenvalues() const {
    if (!IsSquare()) {
        std::string err = "Tried gettin eigenvalues for a non square matrix";
        throw std::logic_error(err);
        return MathMatrix();  // Return empty matrix, error thrown
    }
    
    // Create a copy, then perform [Q, R] = qr(copy); copy = R * Q; 20 times
    // This will converge down to eigenvalues across the diagonal.
    MathMatrix copy = *this;
    for (int i = 0; i < 20; ++i) {
        std::vector<MathMatrix> qr = copy.QRDecomposition();
        copy = qr[1].Multiply(qr[0]);
    }
    return copy.Diagonal();
}

MathMatrix MathMatrix::Multiply(const MathMatrix rhs) const {
    // Matrix multiplication requires that the number of columns in the right is
    // equal to the number of rows in the left.
    if (rhs.ColumnSize() == RowSize()) {
        MathMatrix result = MathMatrix(RowSize(), rhs.ColumnSize());
        for (unsigned int i = 0; i < RowSize(); ++i) {
            // Iterating through each row of the lhs
            for (unsigned int j = 0; j < rhs.ColumnSize(); ++j) {
                // Iterating through each column of the rhs
                result(i, j) = 0;
                for (unsigned int k = 0; k < rhs.RowSize(); ++k) {
                    // Iterating through each row of the rhs
                    result(i, j) += this->operator()(i, k) * rhs(k, j);
                }
            }
        }
        return result;
    } else {
        std::string err = "Tried to multiply matrices with mismatched sizes";
        throw std::invalid_argument(err);
        return MathMatrix();  // Return empty matrix, error thrown.
    }
    
}

MathMatrix MathMatrix::Add(const MathMatrix rhs) const {
    MathMatrix result = MathMatrix(RowSize(), ColumnSize());
    if (rhs.Size() == Size()) {
        for (unsigned int i = 0; i < RowSize(); ++i) {
            for (unsigned int j = 0; j < ColumnSize(); ++j) {
                result(i,j) = this->operator()(i, j) + rhs(i, j);
            }
        }
        return result;
    } else {
        std::string err = "Tried to add matrices with different sizes";
        throw std::invalid_argument(err);
        return MathMatrix();  // Return empty matrix, error thrown.
    }
}

MathMatrix MathMatrix::Subtract(const MathMatrix rhs) const {
    MathMatrix result = *this;
    if (rhs.Size() == Size()) {
        for (unsigned int i = 0; i < RowSize(); ++i) {
            for (unsigned int j = 0; j < ColumnSize(); ++j) {
                result(i,j) = this->operator()(i, j) - rhs(i, j);
            }
        }
        return result;
    } else {
        std::string err = "Tried to subtract matrices with different sizes";
        throw std::invalid_argument(err);
        return MathMatrix();  // Return empty matrix, error thrown.
    }
}

MathMatrix MathMatrix::LeastSquares(const MathMatrix rhs) const {
    // TODO(aerobau) implement
    return MathMatrix();
}

MathMatrix MathMatrix::Diagonal() const {
    std::vector<std::vector<double>> diagonal(1);
    std::size_t size = std::min(matrix_.num_col(), matrix_.num_row());
    diagonal[0] = std::vector<double>(size);
    auto iter = matrix_.begin_diagonal();
    for (int i = 0; i < size; ++i, ++iter) {
        diagonal[0][i] = *iter;
    }
    return MathMatrix(extd::matrix<double>(diagonal));
}


std::vector<MathMatrix> MathMatrix::SVDDecomposition() const {
    // TODO(aerobau): implement
    return { MathMatrix(), MathMatrix(), MathMatrix() };
}

std::vector<MathMatrix> MathMatrix::QRDecomposition() const {
    // TODO(aerobau): implement
    return { MathMatrix(), MathMatrix() };
}


void MathMatrix::RREF() {
    // TODO(aerobau): implement
}

void MathMatrix::Gauss() {
    // TODO(aerobau): implement
}

void MathMatrix::Backsub() {
    // TODO(aerobau): implement
}


extd::matrix_size MathMatrix::Size() const {
    return matrix_.size();
}

std::size_t MathMatrix::ColumnSize() const {
    return matrix_.num_col();
}

std::size_t MathMatrix::RowSize() const {
    return matrix_.num_row();
}



bool MathMatrix::IsColumnVector() const {
    return matrix_.num_row() == 1;
}

bool MathMatrix::IsRowVector() const {
    return matrix_.num_col() == 1;
}

bool MathMatrix::IsVector() const {
    return matrix_.num_col() == 1 || matrix_.num_row() == 1;
}

bool MathMatrix::IsSquare() const {
    return matrix_.num_col() == matrix_.num_row();
}

bool MathMatrix::IsSingleValue() const {
    return matrix_.num_row() == 1 && matrix_.num_col() == 1;
}

std::string MathMatrix::ToString() const {
    std::stringstream stream;
    // For every row, add to the stream the following: [ val val val ... val ]
    // End the line after each row as well
    for (unsigned int i = 0; i < RowSize(); ++i) {
        stream << "[ ";
        for (unsigned int j = 0; j < ColumnSize(); ++j) {
            stream << this->operator()(i, j) << " ";
        }
        stream << "]" << std::endl;
    }
    return stream.str();
}





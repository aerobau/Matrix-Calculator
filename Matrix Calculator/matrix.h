//  matrix.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/18/15.

#include <vector>
#include <sstream>

#ifndef MATRIX_H_
#define MATRIX_H_

// namespace extd, due to the matrix class's design and similarity to std but
// its extending nature
namespace extd {

//  |STRUCT|  matrix_size  |STRUCT|
//
//  A simple structure that holds the columns and rows that represent the size
//  of a matrix
struct matrix_size {
    matrix_size(std::size_t rows, std::size_t columns)
            : rows(rows), columns(columns) {}
    
    bool operator==(const matrix_size rhs) const {
        return columns == rhs.columns && rows == rhs.rows;
    }
    bool operator !=(const matrix_size rhs) const {
        return !(*this == rhs);
    }
    
    // Number of columns and rows in a given matrix
    std::size_t columns, rows;
};
  
//  |CLASS|  matrix  |CLASS|
//
//  Matrix data structure.  Encapsulates and allows operations to a two
//  dimmensional vector set such that the Matrix has many methods similar to the
//  standard library vector notation.  There is also iterator support with
//  multiple different iteration types (Column, Row, Diagonal)
template<typename T>
class matrix {
public:
    // Enum for the supported iteration types through the vector
    enum iterator_type {COLUMN, ROW, DIAGONAL};
    
    //  |NESTED CLASS|  iterator  |NESTED CLASS|
    //
    //  iterator class that allows for the iteration of the vector in a
    //  multitude of methods
    class iterator : public std::iterator<std::forward_iterator_tag, T> {
    private:
        // Holds a reference to the matrix so that the value can be accessed
        // from held row and column indexes
        matrix<T>& matrix_;
        
        // Holds the row and column index
        int column_, row_;
        
        // The type of iteration that is being performed (see enum above)
        iterator_type type_;
        
        // Increments based on the type of iteration that is being performed.
        void increment() {
            switch(type_) {
                case COLUMN: ++row_;
                case ROW: ++column_;
                case DIAGONAL: ++row_, ++column_;
            }
        }
        
        // Decrements based on the type of iteration that is being performed.
        void decrement() {
            switch(type_) {
                case COLUMN: --row_;
                case ROW: --column_;
                case DIAGONAL: --row_, --column_;
            }
        }
        
    public:
        iterator(iterator_type type, matrix<T>& matrix, int row, int column)
            : type_(type), matrix_(matrix), row_(row), column_(column) {}
        iterator(const iterator&) = default;
        
        ~iterator() = default;
        
        iterator& operator=(const iterator&) = default;
        
        iterator& operator++() {
            increment();
            return *this;
        }
        
        iterator operator++(int) {
            iterator iter = *this;
            increment();
            return iter;
        }
        
        iterator& operator--() {
            iterator iter = *this;
            decrement();
            return iter;
        }
        
        iterator& operator--(int) {
            decrement();
            return *this;
        }
        
        T& operator*() const {
            return matrix_.container_[row_][column_];
        }
        
        T* operator->() const {
            return &matrix_.container_[row_][column_];
        }
    };
    
    //  |NESTED CLASS|  const_iterator  |NESTED CLASS|
    //
    //  const_iterator complement to iterator
    class const_iterator : public std::iterator<std::forward_iterator_tag, T> {
    private:
        // Holds a const reference to the matrix so that the value can be
        // accessed from held row and column indexes.
        const matrix<T>& matrix_;
        
        // Holds the row and column index.
        int column_, row_;
        
        // The type of iteration that is being performed (see enum above).
        iterator_type type_;
        
        // Increments based on the type of iteration that is being performed.
        void increment() {
            switch(type_) {
                case COLUMN: ++row_;
                case ROW: ++column_;
                case DIAGONAL: ++row_, ++column_;
            }
        }
        
        // Decrements based on the type of iteration that is being performed.
        void decrement() {
            switch(type_) {
                case COLUMN: --row_;
                case ROW: --column_;
                case DIAGONAL: --row_, --column_;
            }
        }
        
    public:
        const_iterator(iterator_type type, const matrix<T>& matrix,
                       int row, int column)
                : type_(type), matrix_(matrix), row_(row), column_(column) {}
        const_iterator(const const_iterator& iter) = default;
        
        ~const_iterator() = default;
        
        const_iterator& operator=(const const_iterator&) = default;
        
        const_iterator& operator++() {
            increment();
            return *this;
        }
        
        const_iterator operator++(int) {
            const_iterator iter = *this;
            increment();
            return iter;
        }
        
        const_iterator& operator--() {
            decrement();
            return *this;
        }
        
        const_iterator operator--(int) {
            const_iterator iter = *this;
            decrement();
            return iter;
        }
        
        const T& operator*() const {
            return matrix_.container_[row_][column_];
        }
        
        T* operator->() const {
            return &matrix_.container_[row_][column_];
        }
    };

    
    matrix() : container_() {}
    explicit matrix(std::vector<std::vector<T>> container)
            : container_(container) {}
    
    // Allocation style constructor that initializes the matrix with a given
    // number of rows and columns, filling with default values
    matrix(std::size_t rows, std::size_t columns) {
        std::vector<T> row(columns);
        container_ = std::vector<std::vector<T>>(rows);
        for (unsigned int i = 0; i < rows; ++i) {
            container_[i] = row;
        }
    }
    
    matrix(const matrix&) = default;
    
    matrix& operator=(const matrix&) = default;
    
    // Accessses a reference to the value at a given row and column indexing
    T& operator()(int row, int column) {
        return container_[row][column];
    }
    
    // Const counterpart of above
    const T& operator()(int row, int column) const {
        return container_[row][column];
    }
    
    std::size_t num_col() const {
        // Avoids index access of empty container
        return container_.size() > 0 ? container_[0].size() : 0;
    }
    
    std::size_t num_row() const {
        return container_.size();
    }
    
    matrix_size size() const {
        return matrix_size(num_col(), num_row());
    }
    
    // Adds a row to the end
    void push_back_row(std::vector<T> row) {
        if (container_.size() > 0) {
            // Container not empty, check for size match on existing rows
            if (num_col() == row.size()) {
                container_.push_back(row);
            } else {
                std::string err =
                    "Row being added is not the correct size vector";
                throw std::invalid_argument(err);
            }
        } else {
            container_.push_back(row);
        }
    }
    
    // Adds a column to the end
    void push_back_column(std::vector<T> column) {
        if (container_.size() > 0) {
            // Container not empty, check for size match on existing columns
            if (num_row() == column.size()) {
                // Adds the correct index of the column on the end of each
                // corresponding row
                for (unsigned int i = 0; i < container_.size(); ++i) {
                    container_[i].push_back(column[i]);
                }
            } else {
                std::string err =
                    "Column being added is not the correct size vector";
                throw std::invalid_argument(err);
            }
        } else {
            for (unsigned int i = 0; i < container_.size(); ++i) {
                container_[i].push_back(column[i]);
            }
        }
    }
    
    // Inserts a row at a given index using iterator semantics
    void insert_row(iterator position, std::vector<T> row) {
        if (container_.size() > 0) {
            // Check for size match on existing rows
            if (num_col() != row.size()) {
                std::string err =
                    "Inserting row is not the correct size vector";
                throw std::invalid_argument(err);
                return;
            }
        }
        container_.insert(container_.begin() + position.row_, row);
    }
    
    // Inserts a column at a given index using iterator semantics
    void insert_column(iterator position, std::vector<T> column) {
        // Check for size match on existing columns
        if (container_.size() != column.size()) {
            std::string err =
                "Inserting column is not the correct size vector";
            throw std::invalid_argument(err);
        } else {
            for (int i = 0; i < container_.size(); ++i) {
                container_[i].insert(container_[i].begin() + position.column_,
                                     column);
            }
        }
    }
    
    // Takes an iterator and deletes the column that the iterator is in
    void erase_column(iterator position) {
        for (int i = 0; i < container_.size(); ++i) {
            container_[i].erase(container_[i].begin() + position.column_);
        }
    }
    
    // Takes in an iterator and deletes the row that the iterator is in
    void erase_row(iterator position) {
        container_.erase(container_.begin() + position.row_);
    }
    
    // Makes an iterator over a column that starts at the beginning of a column
    // at a given index
    iterator begin_column(int index) {
        return custom_iterator(COLUMN, 0, index);
    }
    
    // Making an iterator over a column that starts at the end of a column at a
    // given index
    iterator end_column(int index) {
        return custom_iterator(COLUMN, num_row(), index);
    }
    
    // Making an iterator over a row that starts at the beginning of a row at a
    // given index
    iterator begin_rows(int index) {
        return custom_iterator(ROW, index, 0);
    }
    
    // Making an iterator over a row that starts at the end of a row at a given
    // index
    iterator end_rows(int index) {
        return custom_iterator(ROW, index, num_col());
    }
    
    // Making an iterator over the core digaonal that starts at 0,0
    iterator begin_diagonal() {
        return custom_iterator(DIAGONAL, 0, 0);
    }
    
    // Making an iterator over the core diagonal that starts at the index
    // min(col_size, row_size)
    iterator end_diagonal() {
        // Use the minimum dimension to end the diagonal
        int end_index = (int) (num_row() > num_col() ? num_col() : num_row());
        return custom_iterator(DIAGONAL, end_index, end_index);
    }
    
    // Makes a custom iterator for use in special applications
    iterator custom_iterator(iterator_type type, int row, int column) {
        if (row >= num_row() || row < 0 || column >= num_col() || column < 0) {
            throw std::out_of_range("Row or column index out of range");
        } else {
            return iterator(type, *this, row, column);
        }
    }
    
    // Makes a const_iterator over a column that starts at the begin of a column
    // at a given index
    const_iterator begin_column(int index) const {
        return custom_const_iterator(COLUMN, 0, index);
    }
    
    // Makes a const_iterator over a column that starts at the end of a column
    // at a given index
    const_iterator end_column(int index) const {
        return custom_const_iterator(COLUMN, num_row(), index);
    }
    
    // Makes a const_iterator over a row that starts at the begin of a row at a
    // given index
    const_iterator begin_row(int index) const {
        return custom_const_iterator(ROW, index, 0);
    }
    
    // Makes a const_iterator over a row that starts at the end of a row at a
    // given index
    const_iterator end_row(int index) const {
        return custom_const_iterator(ROW, index, num_col());
    }
    
    // Making an const_iterator over the core digaonal that starts at 0,0
    const_iterator begin_diagonal() const {
        return custom_const_iterator(DIAGONAL, 0, 0);
    }
    
    // Makes a const_iterator over the core diagonal that starts at the index
    // min(num_col, num_row)
    const_iterator end_diagonal() const {
        // Use the minimum dimmension to end the diagonal
        int end_index = num_row() > num_col() ? num_col() : num_row();
        return custom_const_iterator(DIAGONAL, end_index, end_index);
    }
    
    // Makes a custom const_iterator for use in special applications
    const_iterator custom_const_iterator(iterator_type type,
                                         int row, int column) const {
        if (row >= num_row() || row < 0 || column >= num_col() || column < 0) {
            throw std::out_of_range("Row or column index out of range");
        } else {
            return const_iterator(type, *this, row, column);
        }
    }
    
private:
    // The container that holds the values needed in a two dimmensional vector,
    // oriented in row, column order, can be accessed in the following way:
    // - container_[row][column]
    std::vector<std::vector<T>> container_;
};
    
}

#endif // MATRIX_H_

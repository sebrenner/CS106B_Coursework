/*
 * File: gridimpl.cpp
 * ------------------
 * This file contains the implementation of the grid.h interface.
 * Because of the way C++ compiles templates, this code must be
 * available to the compiler when it reads the header file.
 */

#ifdef _grid_h

template <typename ValueType>
Grid<ValueType>::Grid() {
   elements = NULL;
   nRows = 0;
   nCols = 0;
}

template <typename ValueType>
Grid<ValueType>::Grid(int nRows, int nCols) {
   elements = NULL;
   resize(nRows, nCols);
}

template <typename ValueType>
Grid<ValueType>::~Grid() {
   if (elements != NULL) delete[] elements;
}

template <typename ValueType>
int Grid<ValueType>::numRows() const {
   return nRows;
}

template <typename ValueType>
int Grid<ValueType>::numCols() const {
   return nCols;
}

template <typename ValueType>
void Grid<ValueType>::resize(int nRows, int nCols) {
   if (nRows < 0 || nCols < 0) {
      error("Attempt to resize grid to invalid size ("
            + integerToString(nRows) + ", "
            + integerToString(nCols) + ")");
   }
   if (elements != NULL) delete[] elements;
   this->nRows = nRows;
   this->nCols = nCols;
   elements = new ValueType[nRows * nCols];
   ValueType value = ValueType();
   for (int i = 0; i < nRows * nCols; i++) {
      elements[i] = value;
   }
}

template <typename ValueType>
bool Grid<ValueType>::inBounds(int row, int col) const {
   return row >= 0 && col >= 0 && row < nRows && col < nCols;
}

template <typename ValueType>
typename Grid<ValueType>::GridRow Grid<ValueType>::operator[](int row) {
   return GridRow(this, row);
}

template <typename ValueType>
void Grid<ValueType>::mapAll(void (*fn)(ValueType)) {
   for (int i = 0; i < nRows * nCols; i++) {
      fn(elements[i]);
   }
}

template <typename ValueType>
template <typename ClientDataType>
void Grid<ValueType>::mapAll(void (*fn)(ValueType, ClientDataType&),
                             ClientDataType & data) {
   for (int i = 0; i < nRows * nCols; i++) {
      fn(elements[i], data);
   }
}

#endif

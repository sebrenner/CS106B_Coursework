/*
 * File: gridpriv.h
 * ----------------
 * This file contains the private section of the grid.h interface.
 */

/*
 * Implementation notes: Grid data structure
 * -----------------------------------------
 * The Grid is internally managed as a dynamic array of elements.
 * The array itself is one-dimensional, the logical separation into
 * rows and columns is done by arithmetic computation.  The layout
 * is in row-major order, which is to say that the entire first row
 * is laid out contiguously, followed by the entire second row,
 * and so on.
 */

/* Instance variables */

   ValueType *elements;  /* A dynamic array of the elements   */
   int nRows;            /* The number of rows in the grid    */
   int nCols;            /* The number of columns in the grid */

/* Private method prototypes */

   void checkRange(int row, int col);

/*
 * Hidden features
 * ---------------
 * The remainder of this file consists of the code required to
 * support deep copying and iteration.  Including these methods
 * in the public interface would make that interface more
 * difficult to understand for the average client.
 */

/*
 * Deep copying support
 * --------------------
 * This copy constructor and operator= are defined to make a
 * deep copy, making it possible to pass/return grids by value
 * and assign from one grid to another. The entire contents of
 * the grid, including all elements, are copied. Each grid
 * element is copied from the original grid to the copy using
 * assignment (operator=). Making copies is generally avoided
 * because of the expense and thus, grids are typically passed
 * by reference, however, when a copy is needed, these operations
 * are supported.
 */

   void copyInternalData(const Grid & grid) {
      int n = grid.nRows * grid.nCols;
      elements = new ValueType[n];
      for (int i = 0; i < n; i++) {
         elements[i] = grid.elements[i];
      }
      nRows = grid.nRows;
      nCols = grid.nCols;
   }

public:

   Grid & operator=(const Grid & rhs) {
      if (this != &rhs) {
         delete[] elements;
         copyInternalData(rhs);
      }
      return *this;
   }

   Grid(const Grid & rhs) {
      copyInternalData(rhs);
   }

/*
 * Iterator support
 * ----------------
 * The classes in the StanfordCPPLib collection implement input
 * iterators so that they work symmetrically with respect to the
 * corresponding STL classes.
 */

   class iterator : public std::iterator<std::input_iterator_tag, ValueType> {
   public:

      iterator(const Grid *gp, int index) {
         this->gp = gp;
         this->index = index;
      }

      iterator(const iterator & it) {
         this->gp = it.gp;
         this->index = it.index;
      }

      iterator & operator++() {
         index++;
         return *this;
      }

      iterator operator++(int) {
         iterator copy(*this);
         operator++();
         return copy;
      }

      bool operator==(const iterator & rhs) {
         return gp == rhs.gp && index == rhs.index;
      }

      bool operator!=(const iterator & rhs) {
         return !(*this == rhs);
      }

      ValueType & operator*() {
         return gp->elements[index];
      }

   private:
      const Grid *gp;
      int index;
   };

   iterator begin() const {
      return iterator(this, 0);
   }

   iterator end() const {
      return iterator(this, nRows * nCols);
   }

/*
 * Class: Grid<ValType>::GridRow
 * -----------------------------
 * This section of the code defines a nested class within the Grid template
 * that makes it possible to use traditional subscripting on Grid values.
 */

   class GridRow {
   public:
      GridRow() {
         /* Empty */
      }

      ValueType & operator[](int col) {
              if (!gp->inBounds(row, col)) {
                 error("Grid index values out of range");
              }
         return gp->elements[(row * gp->nCols) + col];
      }

   private:
      GridRow(Grid *gridRef, int index) {
         gp = gridRef;
         row = index;
      }

      Grid *gp;
      int row;
      friend class Grid;
   };
   friend class GridRow;

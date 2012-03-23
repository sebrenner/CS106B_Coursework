/*
 * File: grid.h
 * ------------
 * This interface exports the <code>Grid</code> template class, which
 * provides a convenient abstraction for representing two-dimensional
 * arrays.
 */

#ifndef _grid_h
#define _grid_h

#include "error.h"
#include "foreach.h"
#include "strlib.h"

/*
 * Class: Grid<ValueType>
 * ----------------------
 * The <code>Grid</code> class stores an indexed, two-dimensional
 * array.  The following function, for example, creates an identity
 * matrix of size <code>n</code>, in which the elements are 1.0
 * along the main diagonal and 0.0 everywhere else:
 *
 *<pre>
 *    Grid<double> createIdentityMatrix(int n) {
 *       Grid<double> matrix(n, n);
 *       for (int i = 0; i < n; i++) {
 *          matrix[i][i] = 1.0;
 *       }
 *       return matrix;
 *    }
 *</pre>
 */

template <typename ValueType>
class Grid {

public:

/* Forward reference */
   class GridRow;

/*
 * Constructor: Grid
 * Usage: Grid<ValueType> grid;
 *        Grid<ValueType> grid(nRows, nCols);
 * ------------------------------------------
 * Initializes a new grid.  The second form of the constructor is
 * more common and creates a grid with the specified number of rows
 * and columns.  Each element of the grid is initialized to the
 * default value for the type.  The default constructor creates an
 * empty grid for which the client must call <code>resize</code> to
 * set the dimensions.
 */

   Grid();
   Grid(int nRows, int nCols);

/*
 * Destructor: ~Grid
 * Usage: (usually implicit)
 * -------------------------
 * Frees any heap storage associated with this grid.
 */

   ~Grid();

/*
 * Method: numRows
 * Usage: int nRows = grid.numRows();
 * ----------------------------------
 * Returns the number of rows in the grid.
 */

   int numRows() const;

/*
 * Method: numCols
 * Usage: int nCols = grid.numCols();
 * ----------------------------------
 * Returns the number of columns in the grid.
 */

   int numCols() const;

/*
 * Method: resize
 * Usage: grid.resize(nRows, nCols);
 * ---------------------------------
 * Reinitializes the grid to have the specified number of rows
 * and columns.  Any previous grid contents are discarded.
 */

   void resize(int nRows, int nCols);

/*
 * Method: inBounds
 * Usage: if (grid.inBounds(row, col)) . . .
 * -----------------------------------------
 * Returns <code>true</code> if the specified row and column position
 * is inside the bounds of the grid.
 */

   bool inBounds(int row, int col) const;

/*
 * Operator: []
 * Usage:  grid[row][col]
 * ----------------------
 * Overloads <code>[]</code> to select elements from this grid.
 * This extension enables the use of traditional array notation to
 * get or set individual elements.  This method signals an error if
 * the <code>row</code> and <code>col</code> arguments are outside
 * the grid boundaries.
 */

   GridRow operator[](int row);

/*
 * Macro: foreach
 * Usage: foreach (ValueType value in grid) . . .
 * ----------------------------------------------
 * Iterates over the elements of the grid in <i>row-major order,</i>
 * in which all the elements of row 0 are processed, followed by
 * the elements in row 1, and so on.
 */

   /* The foreach macro is defined in foreach.h */

/*
 * Method: mapAll
 * Usage: grid.mapAll(fn);
 *        grid.mapAll(fn, data);
 * -----------------------------
 * Calls the specified function on each element of the grid.  The
 * elements are processed in <i>row-major order,</i> in which all
 * the elements of row 0 are processed, followed by the elements
 * in row 1, and so on.  The second form of the call allows the
 * client to pass a data value of any type to the callback function.
 */

   void mapAll(void (*fn)(ValueType value));

   template <typename ClientDataType>
   void mapAll(void (*fn)(ValueType value, ClientDataType & data),
               ClientDataType & data);

#include "private/gridpriv.h"

};

#include "private/gridimpl.cpp"

#endif

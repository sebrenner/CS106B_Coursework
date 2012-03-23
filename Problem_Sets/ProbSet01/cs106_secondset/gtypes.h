/*
 * File: gtypes.h
 * --------------
 * This file defines three classes that are used in the graphics
 * library to encapsulate basic geometrical concepts:
 *
 *<pre>
 *   GPoint     - A point containing an x and y value
 *   GRectangle - A rectangle with x, y, width, height
 *   GPolygon   - A vector of GPoints marking the vertices of a polygon
 *</pre>
 */

#ifndef _gtypes_h
#define _gtypes_h

#include <string>
#include "vector.h"

/*
 * Class: GPoint
 * -------------
 * This class represents a point on the real-valued graphics plane.
 */

class GPoint {

public:

/*
 * Constructor: GPoint
 * Usage: GPoint origin;
 *        GPoint pt(x, y);
 * -----------------------
 * Creates a <code>GPoint</code> object with the specified <code>x</code>
 * and <code>y</code> coordinates.  If the coordinates are not supplied,
 * the default constructor sets these fields to 0.
 */

   GPoint();
   GPoint(double x, double y);

/*
 * Method: getX
 * Usage: double x = pt.getX();
 * ----------------------------
 * Returns the <i>x</i> component of the point.
 */

   double getX() const;

/*
 * Method: getY
 * Usage: double y = pt.getY();
 * ----------------------------
 * Returns the <i>y</i> component of the point.
 */

   double getY() const;

/*
 * Method: toString
 * Usage: string str = pt.toString();
 * ----------------------------------
 * Converts the <code>GPoint</code> to a string in the form
 * <code>"(</code><i>x</i><code>,</code>&nbsp;<i>y</i><code>)"</code>.
 */

   std::string toString() const;

#include "private/gpointpriv.h"

};

/*
 * Class: GRectangle
 * -----------------
 * This class represents a rectangle on the graphics plane and is
 * conventionally used to denote the bounding box for an object.
 */

class GRectangle {

public:

/*
 * Constructor: GRectangle
 * Usage: GRectangle empty;
 *        GRectangle r(x, y, width, height);
 * -----------------------------------------
 * Creates a <code>GRectangle</code> object with the specified components.
 * If these parameters are not supplied, the default constructor sets
 * these fields to 0.
 */

   GRectangle();
   GRectangle(double x, double y, double width, double height);

/*
 * Method: getX
 * Usage: double x = r.getX();
 * ---------------------------
 * Returns the <i>x</i> component of the rectangle.
 */

   double getX() const;

/*
 * Method: getY
 * Usage: double y = pt.getY();
 * ----------------------------
 * Returns the <i>y</i> component of the rectangle.
 */

   double getY() const;

/*
 * Method: getWidth
 * Usage: double width = r.getWidth();
 * -----------------------------------
 * Returns the <i>width</i> component of the rectangle.
 */

   double getWidth() const;

/*
 * Method: getHeight
 * Usage: double height = pt.getHeight();
 * --------------------------------------
 * Returns the <i>height</i> component of the rectangle.
 */

   double getHeight() const;

/*
 * Method: isEmpty
 * Usage: if (r.isEmpty()) . . .
 * -----------------------------
 * Returns <code>true</code> if the rectangle is empty.
 */

   bool isEmpty() const;

/*
 * Method: contains
 * Usage: if (r.contains(pt)) . . .
 *        if (r.contains(x, y)) . . .
 * ----------------------------------
 * Returns <code>true</code> if the rectangle contains the given point,
 * which may be specified either as a point or as distinct coordinates.
 */

   bool contains(GPoint pt) const;
   bool contains(double x, double y) const;

/*
 * Method: toString
 * Usage: string str = r.toString();
 * ---------------------------------
 * Converts the <code>GRectangle</code> to a string in the form
 * <code>"(</code><i>x</i><code>,</code>&nbsp;<i>y</i><code>,</code>
 * <i>width</i><code>,</code>&nbsp;<i>height</i><code>)"</code>.
 */

   std::string toString() const;

#include "private/grectanglepriv.h"

};

/*
 * Class: GPolygon
 * ---------------
 * This class represents a polygon and consists of a vector of
 * the vertices.
 */

class GPolygon : public Vector<GPoint> {

public:

/*
 * Constructor: GPolygon
 * Usage: GPolygon poly;
 * ---------------------
 * Creates a <code>GPolygon</code> object with no internal vertices.
 * The vertices must be added using vector operations or the methods
 * <code>addVertex</code>, <code>addEdge</code>, or
 * <code>addPolarEdge</code>.
 */

   GPolygon();

/*
 * Method: addVertex
 * Usage: poly.addVertex(pt);
 *        poly.addVertex(x, y);
 * ----------------------------
 * Adds a new vertex to the polygon.
 */

   void addVertex(GPoint pt);
   void addVertex(double x, double y);

/*
 * Method: addEdge
 * Usage: poly.addEdge(dx, dy);
 * ----------------------------
 * Adds a new vertex to the polygon whose coordinates are displaced
 * by <code>dx</code> and <code>dy</code> from the last vertex.
 */

   void addEdge(double dx, double dy);

/*
 * Method: addPolarEdge
 * Usage: poly.addPolarEdge(r, theta);
 * -----------------------------------
 * Adds a new vertex to the polygon whose coordinates are <code>r</code>
 * pixels away from the last point in the direction specified by
 * <code>theta</code>.
 */

   void addPolarEdge(double r, double theta);

/*
 * Method: contains
 * Usage: if (poly.contains(pt)) . . .
 *        if (poly.contains(x, y)) . . .
 * -------------------------------------
 * Returns <code>true</code> if the polygon contains the given point,
 * which may be specified either as a point or as distinct coordinates.
 */

   bool contains(GPoint pt) const;
   bool contains(double x, double y) const;

/*
 * Method: toString
 * Usage: string str = poly.toString();
 * ------------------------------------
 * Converts the <code>GPolygon</code> to a string.
 */

   std::string toString() const;

};

#include "private/gtypescompare.h"

#endif

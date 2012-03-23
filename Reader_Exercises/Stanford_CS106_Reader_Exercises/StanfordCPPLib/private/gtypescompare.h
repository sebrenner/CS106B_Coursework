/*
 * File: gtypescompare.h
 * ---------------------
 * This file defines the comparison functions for GPoint, GRectangle,
 * and GPolygon.
 */

/*
 * Operators: ==, !=
 * Usage: if (p1 == p2) . . .
 *        if (p1 != p2) . . .
 *        if (r1 == r2) . . .
 *        if (r1 != r2) . . .
 *        if (poly1 == poly2) . . .
 *        if (poly1 != poly2) . . .
 * --------------------------------
 * Define the comparison operators for points, rectangles, and
 * polygons.
 */

bool operator==(const GPoint & p1, const GPoint & p2);
bool operator!=(const GPoint & p1, const GPoint & p2);
bool operator==(const GRectangle & r1, const GRectangle & r2);
bool operator!=(const GRectangle & r1, const GRectangle & r2);
bool operator==(const GPolygon & poly1, const GPolygon & poly2);
bool operator!=(const GPolygon & poly1, const GPolygon & poly2);

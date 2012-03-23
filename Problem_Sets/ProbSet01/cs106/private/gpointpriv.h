/*
 * File: gpointpriv.h
 * ------------------
 * This file contains the private section of the GPoint class.  This
 * information is stored in a separate file to ensure that the client
 * doesn't see this information when reading the interface.
 */

private:

/* Instance variables */

   double x;                       /* The x-coordinate of the point */
   double y;                       /* The y-coordinate of the point */

/* Friend declarations */

friend bool operator==(const GPoint & p1, const GPoint & p2);
friend bool operator!=(const GPoint & p1, const GPoint & p2);

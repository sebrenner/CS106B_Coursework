/*
 * File: grectanglepriv.h
 * ----------------------
 * This file contains the private section of the GRectangle class.  This
 * information is stored in a separate file to ensure that the client
 * doesn't see this information when reading the interface.
 */

private:

/* Instance variables */

   double x;                       /* The x-coordinate of the rectangle */
   double y;                       /* The y-coordinate of the rectangle */
   double width;                   /* The width of the rectangle        */
   double height;                  /* The height of the rectangle       */

/* Friend declarations */

friend bool operator==(const GRectangle & r1, const GRectangle & r2);
friend bool operator!=(const GRectangle & r1, const GRectangle & r2);

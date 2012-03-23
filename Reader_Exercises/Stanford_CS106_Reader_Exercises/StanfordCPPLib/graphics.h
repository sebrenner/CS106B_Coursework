/*
 * File: graphics.h
 * ----------------
 * This interface provides access to a simple graphics library
 * that makes it possible to draw lines, rectangles, ovals, arcs,
 * polygons, images, and strings on a graphical window.
 */

#ifndef _graphics_h
#define _graphics_h

#include <string>
#include "gtypes.h"
#include "vector.h"

/*
 * Function: initGraphics
 * Usage: initGraphics();
 *        initGraphics(width, height);
 * -----------------------------------
 * Creates the graphics window on the screen.  The first form
 * creates a window with a default size of 500x300; the second
 * allows the client to specify the size of the window.  The call
 * to <code>initGraphics</code> must precede any console output
 * or calls to other functions in this interface.
 */

void initGraphics();
void initGraphics(int width, int height);

/*
 * Function: drawArc
 * Usage: drawArc(bounds, start, sweep);
 *        drawArc(x, y, width, height, start, sweep);
 * --------------------------------------------------
 * Draws an elliptical arc inscribed in a rectangle.   The parameters
 * <code>x</code>, <code>y</code>, <code>width</code>, and <code>height</code>
 * (or, equivalently, the <code>GRectangle</code> <code>bounds</code>)
 * specify the coordinates and dimensions of the bounding rectangle.
 * The <code>start</code> parameter indicates the angle at which the
 * arc begins and is measured in degrees counterclockwise from the
 * +<i>x</i> axis.  Thus, a <code>start</code> angle of 0 indicates
 * an arc that begins along the line running eastward from the center,
 * a <code>start</code> angle of 135 begins along the line running
 * northwest, and a <code>start</code> angle of -90 begins along
 * the line running south.  The <code>sweep</code> parameter indicates
 * the extent of the arc and is also measured in degrees counterclockwise.
 * A <code>sweep</code> angle of 90 defines a quarter circle extending
 * counterclockwise from the <code>start</code> angle, and a
 * <code>sweep</code> angle of -180 defines a semicircle extending
 * clockwise.
 */

void drawArc(const GRectangle & bounds, double start, double sweep);
void drawArc(double x, double y, double width, double height,
                                 double start, double sweep);

/*
 * Function: fillArc
 * Usage: fillArc(bounds, start, sweep);
 *        fillArc(x, y, width, height, start, sweep);
 * --------------------------------------------------
 * Fills a wedge-shaped area of an elliptical arc.  The parameters are
 * interpreted in the same way as those for <code>drawArc</code>.
 */

void fillArc(const GRectangle & bounds, double start, double sweep);
void fillArc(double x, double y, double width, double height,
                                 double start, double sweep);

/*
 * Function: drawImage
 * Usage: drawImage(filename, pt);
 *        drawImage(filename, x, y);
 *        drawImage(filename, bounds);
 *        drawImage(filename, x, y, width, height);
 * ------------------------------------------------
 * Draws the image from the specified file with its upper left corner
 * at the specified point.  The forms of the call that include the
 * bounds scale the image so that it fits inside the specified rectangle.
 */

void drawImage(std::string filename, const GPoint & pt);
void drawImage(std::string filename, double x, double y);
void drawImage(std::string filename, const GRectangle & bounds);
void drawImage(std::string filename, double x, double y,
                                     double width, double height);

/*
 * Function: getImageBounds
 * Usage: GRectangle bounds = getImageBounds(filename);
 * ----------------------------------------------------
 * Returns the bounds of the image contained in the specified file.
 * Only the width and height components of the rectangle are of
 * interest; the x and y components are always 0.
 */

GRectangle getImageBounds(std::string filename);

/*
 * Function: drawLine
 * Usage: drawLine(p0, p1);
 *        drawLine(x0, y0, x1, y1);
 * --------------------------------
 * Draws a line connecting the specified points.
 */

void drawLine(const GPoint & p0, const GPoint & p1);
void drawLine(double x0, double y0, double x1, double y1);

/*
 * Function: drawPolarLine
 * Usage: GPoint p1 = drawPolarLine(p0, r, theta);
 *        GPoint p1 = drawPolarLine(x0, y0, r, theta);
 * ---------------------------------------------------
 * Draws a line of length <code>r</code> in the direction <code>theta</code>
 * from the initial point.  The angle <code>theta</code> is measured in
 * degrees counterclockwise from the +<i>x</i> axis.  The function returns
 * the end point of the line.
 */

GPoint drawPolarLine(const GPoint & p0, double r, double theta);
GPoint drawPolarLine(double x0, double y0, double r, double theta);

/*
 * Function: drawOval
 * Usage: drawOval(bounds);
 *        drawOval(x, y, width, height);
 * -------------------------------------
 * Draws the frame of a oval with the specified bounds.
 */

void drawOval(const GRectangle & bounds);
void drawOval(double x, double y, double width, double height);

/*
 * Function: fillOval
 * Usage: fillOval(bounds);
 *        fillOval(x, y, width, height);
 * -------------------------------------
 * Fills the frame of a oval with the specified bounds.
 */

void fillOval(const GRectangle & bounds);
void fillOval(double x, double y, double width, double height);

/*
 * Function: drawRect
 * Usage: drawRect(bounds);
 *        drawRect(x, y, width, height);
 * -------------------------------------
 * Draws the frame of a rectangle with the specified bounds.
 */

void drawRect(const GRectangle & bounds);
void drawRect(double x, double y, double width, double height);

/*
 * Function: fillRect
 * Usage: fillRect(bounds);
 *        fillRect(x, y, width, height);
 * -------------------------------------
 * Fills the frame of a rectangle with the specified bounds.
 */

void fillRect(const GRectangle & bounds);
void fillRect(double x, double y, double width, double height);

/*
 * Function: drawPolygon
 * Usage: drawPolygon(polygon);
 *        drawPolygon(polygon, pt);
 *        drawPolygon(polygon, x, y);
 * ----------------------------------
 * Draws the outline of the specified polygon.  The optional <code>pt</code>
 * or <code>x</code> and <code>y</code> parameters shift the origin
 * of the polygon to the specified point.
 */

void drawPolygon(const Vector<GPoint> & polygon);
void drawPolygon(const Vector<GPoint> & polygon, const GPoint & pt);
void drawPolygon(const Vector<GPoint> & polygon, double x, double y);

/*
 * Function: fillPolygon
 * Usage: fillPolygon(polygon);
 *        fillPolygon(polygon, pt);
 *        fillPolygon(polygon, x, y);
 * ----------------------------------
 * Fills the frame of the specified polygon.  The optional <code>pt</code>
 * or <code>x</code> and <code>y</code> parameters shift the origin
 * of the polygon to the specified point.
 */

void fillPolygon(const Vector<GPoint> & polygon);
void fillPolygon(const Vector<GPoint> & polygon, const GPoint & pt);
void fillPolygon(const Vector<GPoint> & polygon, double x, double y);

/*
 * Function: drawString
 * Usage: drawString(str, pt);
 *        drawString(str, x, y);
 * -----------------------------
 * Draws the string <code>str</code> so that its baseline origin appears at
 * the specified point.  The text appears in the current font and color.
 */

void drawString(std::string str, const GPoint & pt);
void drawString(std::string str, double x, double y);

/*
 * Function: getStringWidth
 * Usage: double width = getStringWidth(str);
 * ------------------------------------------
 * Returns the width of the string <code>str</code> when displayed in
 * the current font.
 */

double getStringWidth(std::string str);

/*
 * Function: setFont
 * Usage: setFont(font);
 * ---------------------
 * Sets a new font.  The <code>font</code> parameter is a string in the
 * form <i>family</i><code>-</code><i>style</i><code>-</code><i>size</i>.
 * In this string, <i>family</i> is the name of the font family;
 * <i>style</i> is either missing (indicating a plain font) or one
 * of the strings <code>Bold</code>, <code>Italic</code>, or
 * <code>BoldItalic</code>; and <i>size</i> is an integer
 * indicating the point size.  If any of these components is
 * specified as an asterisk, the existing value is retained.
 * The <code>font</code> parameter can also be a sequence of
 * such specifications separated by semicolons, in which the
 * first available font on the system is used.
 */

void setFont(std::string font);

/*
 * Function: getFont
 * Usage: string font = getFont();
 * -------------------------------
 * Returns the current font.
 */

std::string getFont();

/*
 * Function: setColor
 * Usage: setColor(color);
 * -----------------------
 * Sets the color used for drawing.  The <code>color</code> parameter
 * is usually one of the predefined color names from Java:
 *
 *    <code>BLACK</code>,
 *    <code>BLUE</code>,
 *    <code>CYAN</code>,
 *    <code>DARK_GRAY</code>,
 *    <code>GRAY</code>,
 *    <code>GREEN</code>,
 *    <code>LIGHT_GRAY</code>,
 *    <code>MAGENTA</code>,
 *    <code>ORANGE</code>,
 *    <code>PINK</code>,
 *    <code>RED</code>,
 *    <code>WHITE</code>, or
 *    <code>YELLOW</code>.
 *
 * <p>The case of the individual letters in the color name is ignored,
 * as are spaces and underscores, so that the Java color
 * <code>DARK_GRAY</code> could be written as <code>"Dark&nbsp;Gray"</code>.
 *
 * <p>The color can also be specified as a string in the form
 * <code>"#rrggbb"</code> where <code>rr</code>, <code>gg</code>, and
 * <code>bb</code> are pairs of hexadecimal digits indicating the
 * red, green, and blue components of the color.
 */

void setColor(std::string color);

/*
 * Function: getColor
 * Usage: string color = getColor();
 * ---------------------------------
 * Returns the current color as a string in the form <code>"#rrggbb"</code>.
 * In this string, the values <code>rr</code>, <code>gg</code>,
 * and <code>bb</code> are two-digit hexadecimal values representing
 * the red, green, and blue components of the color, respectively.
 */

std::string getColor();

/*
 * Function: saveGraphicsState
 * Usage: saveGraphicsState();
 * ---------------------------
 * Saves the state of the graphics context.  This function is used
 * in conjunction with <code>restoreGraphicsState()</code> to avoid
 * changing the state set up by the client.
 */

void saveGraphicsState();

/*
 * Function: restoreGraphicsState
 * Usage: restoreGraphicsState();
 * ------------------------------
 * Restores the graphics state from the most recent call to
 * <code>saveGraphicsState()</code>.
 */

void restoreGraphicsState();

/*
 * Function: getWindowWidth
 * Usage: double width = getWindowWidth();
 * ---------------------------------------
 * Returns the width of the graphics window in pixels.
 */

double getWindowWidth();

/*
 * Function: getWindowHeight
 * Usage: double height = getWindowHeight();
 * -----------------------------------------
 * Returns the height of the graphics window in pixels.
 */

double getWindowHeight();

/*
 * Function: repaint
 * Usage: repaint();
 * -----------------
 * Issues a request to update the graphics window.  This function
 * is called automatically when the program pauses, waits for an
 * event, waits for user input on the console, or terminates.  As
 * a result, most clients will never need to call repaint explicitly.
 */

void repaint();

/*
 * Function: pause
 * Usage: pause(milliseconds);
 * ---------------------------
 * Pauses for the indicated number of milliseconds.  This function is
 * useful for animation where the motion would otherwise be too fast.
 */

void pause(double milliseconds);

/*
 * Function: waitForClick
 * Usage: waitForClick();
 * ----------------------
 * Waits for a mouse click to occur anywhere in the window.
 */

void waitForClick();

/*
 * Function: setWindowTitle
 * Usage: setWindowTitle(title);
 * -----------------------------
 * Sets the title of the primary graphics window.
 */

void setWindowTitle(std::string title);

/*
 * Function: getWindowTitle
 * Usage: string title = getWindowTitle();
 * ---------------------------------------
 * Returns the title of the primary graphics window.
 */

std::string getWindowTitle();

/*
 * Function: exitGraphics
 * Usage: exitGraphics();
 * ----------------------
 * Closes the graphics window and exits from the application without
 * waiting for any additional user interaction.
 */

void exitGraphics();

#include "console.h"
#include "private/main.h"

#endif

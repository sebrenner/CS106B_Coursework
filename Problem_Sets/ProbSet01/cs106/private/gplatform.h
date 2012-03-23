/*
 * File: gplatform.h
 * -----------------
 * This interface defines the GPlatform class, which encapsulates the
 * platform-specific parts of the graphics package.  It is implemented
 * separately on each platform.  The class is used to create a singleton
 * object that is used to invoke all of the platform-specific code.
 */

#ifndef _gplatform_h
#define _gplatform_h

#include "gtypes.h"
#include "vector.h"

class GWindow;
class GPainter;

class GPlatform {
public:
   int createGraphicsWindow(double width, double height);
   void closeGraphicsWindow(int id);
   void clear(int id);
   void repaint(int id);
   void setVisible(int id, bool flag);
   bool isVisible(int id);
   void drawArc(int id, double x, double y, double width, double height,
                                            double start, double sweep);
   void fillArc(int id, double x, double y, double width, double height,
                                            double start, double sweep);
   void drawImage(int id, std::string filename, double x, double y);
   void drawImage(int id, std::string filename, double x, double y,
                                                double width, double height);
   void drawLine(int id, double x0, double y0, double x1, double y1);
   void drawOval(int id, double x, double y, double width, double height);
   void fillOval(int id, double x, double y, double width, double height);
   void drawRect(int id, double x, double y, double width, double height);
   void fillRect(int id, double x, double y, double width, double height);
   void drawPolygon(int id, const Vector<GPoint> & polygon,
                    double x, double y);
   void fillPolygon(int id, const Vector<GPoint> & polygon,
                    double x, double y);
   void drawString(int id, std::string str, double x, double y);
   double getStringWidth(int id, std::string str);
   void setFont(int id, std::string font);
   std::string getFont(int id);
   void setColor(int id, int color);  // Consider going back to strings
   int getColor(int id);
   void saveGraphicsState(int id);
   void restoreGraphicsState(int id);
   double getWindowWidth(int id);
   double getWindowHeight(int id);
   void pause(int id, double milliseconds);
   void setWindowTitle(int id, std::string title);
   std::string getWindowTitle(int id);
   void setPainter(GPainter *pptr);

   int openImage(std::string filename);
   void closeImage(int id);
   int getImageWidth(int id);
   int getImageHeight(int id);
};

class GPainter {
public:
   GPainter() {
      /* Empty */
   }

   GPainter(void (*callback)(GWindow & gw)) {
      fn = callback;
   }

   virtual void repaint(GWindow & gw) {
      fn(gw);
   }

private:
   void (*fn)(GWindow & gw);

};

template <typename Type>
class GObjectPainter : public GPainter {
public:
   GObjectPainter(Type & painter) {
      objptr = &painter;
   }

   virtual void repaint(GWindow & gw) {
      objptr->paint(gw);
   }

private:
   Type *objptr;
};

#endif

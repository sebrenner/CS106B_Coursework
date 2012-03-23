/*
 * File: gwindowpriv.h
 * -------------------
 * This file contains the private section of the GWindow class.
 */

public:
   GWindow() {
      id = 0;
   }

   GWindow(int id) {
      this->id = id;
      color = "BLACK";
   }

   GRectangle getImageBounds(std::string filename);

   void pause(double milliseconds);

private:
   int id;
   std::string color;

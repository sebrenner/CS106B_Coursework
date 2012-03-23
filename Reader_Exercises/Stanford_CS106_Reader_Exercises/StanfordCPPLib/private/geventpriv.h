/*
 * File: geventpriv.h
 * ------------------
 * This file contains the parts of the GEvent class definition
 * that are of no interest to clients.
 */

public:

/*
 * Method: setEventTime
 * Usage: e.setEventTime(time);
 * ----------------------------
 * Sets the event time field for this event.  The event system needs
 * access to this method, but conventional clients don't.
 */

   void setEventTime(int time);

/*
 * Method: setModifiers
 * Usage: e.setModifiers(modifiers);
 * ---------------------------------
 * Sets the modifiers field for this event.  The event system needs
 * access to this method, but conventional clients don't.
 */

   void setModifiers(int modifiers);

private:

/*
 * Instance variables
 * ------------------
 * Implementation note: All the variables from the subclasses are included
 * in the outer class to make it possible to convert between general events
 * and the various subclasses.  By keeping all event classes the same size,
 * this design avoids any issues of slicing off parts of the data during
 * such conversions.
 */

/* General events */

   EventClassType eventClass;
   int eventType;
   int modifiers;
   double eventTime;
   bool isValid;
   std::string sourceKey;

/* Window events */

   GWindow gw;

/* Action events */

   std::string actionCommand;

/* Mouse events */

   double x;
   double y;

/* Key events */

   int key;

/* Friend specifications */

friend class GWindowEvent;
friend class GActionEvent;
friend class GTimerEvent;
friend class GMouseEvent;
friend class GKeyEvent;

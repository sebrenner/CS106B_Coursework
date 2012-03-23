/*
 * File: synchonized.h
 * -------------------
 * This file defines the synchronized macro.
 */

void lockForPlatform(int id);
void unlockForPlatform(int id);

class Lock_State {
public:

   Lock_State(Lock & lock) {
      lp = &lock;
      finished = false;
   }

   bool advance() {
      if (finished) {
         unlockForPlatform(lp->id);
         return false;
      } else {
         finished = true;
         lockForPlatform(lp->id);
         return true;
      }
   }

private:
   Lock *lp;
   bool finished;

};

#define synchronized(lock) for (Lock_State ls(lock) ; ls.advance(); )

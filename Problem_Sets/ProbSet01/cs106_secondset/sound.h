/*
 * File: sound.h
 * -------------
 * This interface defines a class that represents a sound.
 */

#ifndef _sound_h
#define _sound_h

/*
 * Class: Sound
 * ------------
 * This class encapsulates a sound file, which is typically
 * specified in the constructor.
 */

class Sound {

public:

/*
 * Constructor: Sound
 * Usage: Sound sound;
 *        Sound sound(filename);
 * -----------------------------
 * Creates a <code>Sound</code> object.  The default constructor
 * creates an empty sound that cannot be played.  The second form
 * initializes the sound by reading in the contents of the specified
 * file.
 */

   Sound();
   Sound(std::string filename);

/*
 * Destructor: ~Sound
 * Usage: (usually implicit)
 * -------------------------
 * Frees the memory associated with the sound.
 */

   ~Sound();

/*
 * Method: play
 * Usage: sound.play();
 * --------------------
 * Plays the sound synchronously and waits for the sound to finish before
 * returning.
 */

   void play();

/*
 * Method: start
 * Usage: sound.start();
 * ---------------------
 * Starts playing the sound asynchronously.
 */

   void start();

/*
 * Method: stop
 * Usage: sound.stop();
 * --------------------
 * Stops playing the sound.
 */

   void stop();

#include "private/soundpriv.h"

};

#endif

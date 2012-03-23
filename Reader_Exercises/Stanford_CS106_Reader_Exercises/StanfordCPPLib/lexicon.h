/*
 * File: lexicon.h
 * ---------------
 * This interface exports the <code>Lexicon</code> class, which is a
 * compact structure for storing a list of words.
 */

#ifndef _lexicon_h
#define _lexicon_h

#include <string>
#include "foreach.h"
#include "set.h"
#include "stack.h"

/*
 * Class: Lexicon
 * --------------
 * This class is used to represent a <i>lexicon,</i> or word list.
 * The main difference between a lexicon and a dictionary is that
 * a lexicon does not provide any mechanism for storing definitions;
 * the lexicon contains only words, with no associated information.
 * It is therefore similar to a set of strings, but with a more
 * space-efficient internal representation.  The <code>Lexicon</code>
 * class supports efficient lookup operations for words and prefixes.
 */

#include <cctype>

class Lexicon {

public:

/*
 * Constructor: Lexicon
 * Usage: Lexicon lex;
 *        Lexicon lex(filename);
 * -----------------------------
 * Initializes a new lexicon.  The default constructor creates an empty
 * lexicon.  The second form reads in the contents of the lexicon from
 * the specified data file.  The data file must be in one of two formats:
 * (1) a space-efficient precompiled binary format or (2) a text file
 * containing one word per line.  The Stanford library distribution
 * includes a binary lexicon file named <code>English.dat</code>
 * containing a list of words in English.  The standard code pattern
 * to initialize that lexicon looks like this:
 *
 *<pre>
 *    Lexicon english("English.dat");
 *</pre>
 */

   Lexicon();
   Lexicon(std::string filename);

/*
 * Destructor: ~Lexicon
 * Usage: (usually implicit)
 * -------------------------
 * The destructor deallocates any storage associated with the lexicon.
 */

   ~Lexicon();

/*
 * Method: size
 * Usage: int n = lex.size();
 * --------------------------
 * Returns the number of words contained in the lexicon.
 */

   int size() const;

/*
 * Method: isEmpty
 * Usage: if (lex.isEmpty()) . . .
 * -------------------------------
 * Returns <code>true</code> if the lexicon contains no words.
 */

   bool isEmpty() const;

/*
 * Method: clear
 * Usage: lex.clear();
 * -------------------
 * Removes all words from the lexicon.
 */

   void clear();

/*
 * Method: add
 * Usage: lex.add(word);
 * ---------------------
 * Adds the specified word to the lexicon.
 */

   void add(std::string word);

/*
 * Method: addWordsFromFile
 * Usage: lex.addWordsFromFile(filename);
 * --------------------------------------
 * Reads the file and adds all of its words to the lexicon.
 */

   void addWordsFromFile(std::string filename);

/*
 * Method: contains
 * Usage: if (lex.contains(word)) . . .
 * ------------------------------------
 * Returns <code>true</code> if <code>word</code> is contained in the
 * lexicon.  In the <code>Lexicon</code> class, the case of letters is
 * ignored, so "Zoo" is the same as "ZOO" or "zoo".
 */

   bool contains(std::string word) const;

/*
 * Method: containsPrefix
 * Usage: if (lex.containsPrefix(prefix)) . . .
 * --------------------------------------------
 * Returns true if any words in the lexicon begin with <code>prefix</code>.
 * Like <code>containsWord</code>, this method ignores the case of letters
 * so that "MO" is a prefix of "monkey" or "Monday".
 */

   bool containsPrefix(std::string prefix) const;

/*
 * Macro: foreach
 * Usage: foreach (string word in lexicon) . . .
 * ---------------------------------------------
 * Iterates over the words in the lexicon in alphabetical order.
 */

   /* The foreach macro is defined in foreach.h */

/*
 * Method: mapAll
 * Usage: lexicon.mapAll(fn);
 *        lexicon.mapAll(fn, data);
 * --------------------------------
 * Calls the specified function on each word in the lexicon.  The second
 * form of the call allows the client to pass a data value of any type
 * to the callback function.
 */

   void mapAll(void (*fn)(std::string value));

   template <typename ClientDataType>
   void mapAll(void (*fn)(std::string value, ClientDataType & data),
               ClientDataType & data);

#include "private/lexiconpriv.h"

};

#include "private/lexiconimpl.cpp"

#endif

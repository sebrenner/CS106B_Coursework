/*
 * File: lexiconpriv.h
 * -------------------
 * This file contains the private section of the lexicon.h interface.
 * This portion of the class definition is taken out of the lexicon.h
 * header so that the client need not have to see all of these
 * details.
 */

private:

#ifdef _MSC_VER
#define LITTLE_ENDIAN 1
#define BYTE_ORDER LITTLE_ENDIAN
#endif

   struct Edge {
#if defined(BYTE_ORDER) && BYTE_ORDER == LITTLE_ENDIAN
      unsigned long letter:5;
      unsigned long lastEdge:1;
      unsigned long accept:1;
      unsigned long unused:1;
      unsigned long children:24;
#else
      unsigned long children:24;
      unsigned long unused:1;
      unsigned long accept:1;
      unsigned long lastEdge:1;
      unsigned long letter:5;
#endif
   };

   Edge *edges, *start;
   int numEdges, numDawgWords;
   Set<std::string> otherWords;

public:

/*
 * Deep copying support
 * --------------------
 * This copy constructor and operator= are defined to make a
 * deep copy, making it possible to pass/return lexicons by value
 * and assign from one lexicon to another.  The entire contents of
 * the lexicon, including all words, are copied.  Making copies is
 * generally avoided because of the expense and thus, lexicons are
 * typically passed by reference.  When a copy is needed, these
 * operations are supported.
 */

   Lexicon(const Lexicon & rhs);
   Lexicon & operator=(const Lexicon & rhs);

/*
 * Iterator support
 * ----------------
 * The classes in the StanfordCPPLib collection implement input
 * iterators so that they work symmetrically with respect to the
 * corresponding STL classes.
 */

   class iterator : public std::iterator<std::input_iterator_tag,std::string> {
   private:
      const Lexicon *lp;
      int index;
      std::string currentDawgPrefix;
      std::string currentSetWord;
      Edge *edgePtr;
      Stack<Edge *> stack;
      Set<std::string>::iterator setIterator;
      Set<std::string>::iterator setEnd;

      void advanceToNextWordInDawg();
      void advanceToNextWordInSet();
      void advanceToNextEdge();

   public:
      iterator() {
         this->lp = NULL;
      }

      iterator(const Lexicon *lp, bool endFlag) {
         this->lp = lp;
         if (endFlag) {
            index = lp->size();
         } else {
            index = 0;
            edgePtr = NULL;
            setIterator = lp->otherWords.begin();
            setEnd = lp->otherWords.end();
            currentDawgPrefix = "";
            currentSetWord = "";
            advanceToNextWordInDawg();
            advanceToNextWordInSet();
         }
      }

      iterator(const iterator & it) {
         lp = it.lp;
         index = it.index;
         currentDawgPrefix = it.currentDawgPrefix;
         currentSetWord = it.currentSetWord;
         edgePtr = it.edgePtr;
         stack = it.stack;
         setIterator = it.setIterator;
      }

      iterator & operator++() {
         if (edgePtr == NULL) {
            advanceToNextWordInSet();
         } else {
            if (currentSetWord == "" || currentDawgPrefix < currentSetWord) {
               advanceToNextWordInDawg();
            } else {
               advanceToNextWordInSet();
            }
         }
         index++;
         return *this;
      }

      iterator operator++(int) {
         iterator copy(*this);
         operator++();
         return copy;
      }

      bool operator==(const iterator & rhs) {
         return lp == rhs.lp && index == rhs.index;
      }

      bool operator!=(const iterator & rhs) {
         return !(*this == rhs);
      }

      std::string operator*() {
         if (edgePtr == NULL) return currentSetWord;
         if (currentSetWord == "" || currentDawgPrefix < currentSetWord) {
            return currentDawgPrefix + lp->ordToChar(edgePtr->letter);
         } else {
            return currentSetWord;
         }
      }
   };

   iterator begin() const {
      return iterator(this, false);
   }

   iterator end() const {
      return iterator(this, true);
   }

private:

   Edge *findEdgeForChar(Edge *children, char ch) const;
   Edge *traceToLastEdge(const std::string & s) const;
   void readBinaryFile(std::string filename);
   void copyInternalData(const Lexicon & rhs);
   int countDawgWords(Edge *start) const;

   unsigned int charToOrd(char ch) const {
      return ((unsigned int)(tolower(ch) - 'a' + 1));
   }

   char ordToChar(unsigned int ord) const {
      return ((char)(ord - 1 + 'a'));
   }

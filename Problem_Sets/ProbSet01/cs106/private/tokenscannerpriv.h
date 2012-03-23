/*
 * File: scannerpriv.h
 * -------------------
 * This file contains the private section of the scanner.h interface.
 * This portion of the class definition is taken out of the scanner.h
 * header so that the client need not have to see all of these details.
 */

private:

   enum NumberScannerState {
      INITIAL_STATE,
      BEFORE_DECIMAL_POINT,
      AFTER_DECIMAL_POINT,
      STARTING_EXPONENT,
      FOUND_EXPONENT_SIGN,
      SCANNING_EXPONENT,
      FINAL_STATE
   };

   std::string buffer;              /* The original argument string */
   std::istream *isp;               /* The input stream for tokens  */
   bool stringInputFlag;            /* Flag indicating string input */
   bool ignoreWhitespaceFlag;       /* Scanner ignores whitespace   */
   bool ignoreCommentsFlag;         /* Scanner ignores comments     */
   bool scanNumbersFlag;            /* Scanner parses numbers       */
   bool scanStringsFlag;            /* Scanner parses strings       */
   std::string wordChars;           /* Characters legal in a word   */
   Stack<int> savedCharacters;      /* Buffer for saved characters  */
   Stack<std::string> savedTokens;  /* Buffer for saved tokens      */
   Lexicon operators;               /* Set of multichar operators   */

/* Private method prototypes */

   int getChar();
   void saveChar(int ch);
   void skipSpaces();
   std::string scanWord();
   std::string scanNumber();
   std::string scanString();
   char scanEscapeCharacter();

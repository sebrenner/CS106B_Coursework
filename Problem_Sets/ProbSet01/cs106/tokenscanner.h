/*
 * File: tokenscanner.h
 * --------------------
 * This file exports a <code>TokenScanner</code> class that divides
 * a string into individual logical units called <i>tokens</i>.
 */

#ifndef _scanner_h
#define _scanner_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "stack.h"

/*
 * Type: TokenType
 * ---------------
 * This enumerated type defines the values of the
 * <code>getTokenType</code> method.
 */

enum TokenType { SEPARATOR, WORD, NUMBER, STRING, OPERATOR };

/*
 * Class: TokenScanner
 * -------------------
 * This class divides a string into individual tokens.  The typical
 * use of the <code>TokenScanner</code> class is illustrated by the
 * following pattern, which reads the tokens in the string variable
 * <code>input</code>:
 *
 *<pre>
 *    TokenScanner scanner;
 *    scanner.setInput(input);
 *    while (scanner.hasMoreTokens()) {
 *       string token = scanner.nextToken();
 *       . . . process the token . . .
 *    }
 *</pre>
 *
 * The <code>TokenScanner</code> class exports several additional methods
 * that give clients more control over its behavior.  Those methods are
 * described individually in the documentation.
 */

class TokenScanner {

public:

/*
 * Constructor: TokenScanner
 * Usage: TokenScanner scanner;
 *        TokenScanner scanner(str);
 *        TokenScanner scanner(infile);
 * ------------------------------------
 * Initializes a scanner object.  The initial token stream comes from
 * the specified string or input stream, if supplied.  The default
 * constructor creates a scanner with an empty token stream.
 */

   TokenScanner();
   TokenScanner(std::string str);
   TokenScanner(std::istream & infile);

/*
 * Destructor: ~TokenScanner
 * Usage: (usually implicit)
 * -------------------------
 * Deallocates the storage associated with this scanner.
 */

   ~TokenScanner();

/*
 * Method: setInput
 * Usage: scanner.setInput(str);
 *        scanner.setInput(infile);
 * --------------------------------
 * Sets the token stream for this scanner to the specified string or
 * input stream.  Any previous token stream is discarded.
 */

   void setInput(std::string str);
   void setInput(std::istream & infile);

/*
 * Method: hasMoreTokens
 * Usage: if (scanner.hasMoreTokens()) . . .
 * -----------------------------------------
 * Returns <code>true</code> if there are additional tokens for this
 * scanner to read.
 */

   bool hasMoreTokens();

/*
 * Method: nextToken
 * Usage: token = scanner.nextToken();
 * -----------------------------------
 * Returns the next token from this scanner.  If <code>nextToken</code>
 * is called when no tokens are available, it returns the empty string.
 */

   std::string nextToken();

/*
 * Method: saveToken
 * Usage: scanner.saveToken(token);
 * --------------------------------
 * Pushes the specified token back into this scanner's input stream.
 * On the next call to <code>nextToken</code>, the scanner will return
 * the saved token without reading any additional characters from the
 * token stream.
 */

   void saveToken(std::string token);

/*
 * Method: ignoreWhitespace()
 * Usage: scanner.ignoreWhitespace();
 * ----------------------------------
 * Tells the scanner to ignore whitespace characters.  By default,
 * the <code>nextToken</code> method treats whitespace characters
 * (typically spaces and tabs) just like any other punctuation mark
 * and returns them as single-character tokens.
 * Calling
 *
 *<pre>
 *    scanner.ignoreWhitespace();
 *</pre>
 *
 * changes this behavior so that the scanner ignore whitespace characters.
 */

   void ignoreWhitespace();

/*
 * Method: ignoreComments
 * Usage: scanner.ignoreComments();
 * --------------------------------
 * Tells the scanner to ignore comments.  The scanner package recognizes
 * both the slash-star and slash-slash comment format from the C-based
 * family of languages.  Calling
 *
 *<pre>
 *    scanner.ignoreComments();
 *</pre>
 *
 * sets the parser to ignore comments.
 */

   void ignoreComments();

/*
 * Method: scanNumbers
 * Usage: scanner.scanNumbers();
 * -----------------------------
 * Controls how the scanner treats tokens that begin with a digit.  By
 * default, the <code>nextToken</code> method treats numbers and letters
 * identically and therefore does not provide any special processing for
 * numbers.  Calling
 *
 *<pre>
 *    scanner.scanNumbers();
 *</pre>
 *
 * changes this behavior so that <code>nextToken</code> returns the
 * longest substring that can be interpreted as a real number.
 */

   void scanNumbers();

/*
 * Method: scanStrings
 * Usage: scanner.scanStrings();
 * -----------------------------
 * Controls how the scanner treats tokens enclosed in quotation marks.  By
 * default, quotation marks (either single or double) are treated just like
 * any other punctuation character.  Calling
 *
 *<pre>
 *    scanner.scanStrings();
 *</pre>
 *
 * changes this assumption so that <code>nextToken</code> returns a single
 * token consisting of all characters through the matching quotation mark.
 * The quotation marks are returned as part of the scanned token so that
 * clients can differentiate strings from other token types.
 */

   void scanStrings();

/*
 * Method: addWordCharacters
 * Usage: scanner.addWordCharacters(str);
 * --------------------------------------
 * Adds the characters in <code>str</code> to the set of characters legal
 * in a word.  For example, calling <code>addWordCharacters("_")</code>
 * adds the underscore to the set of word characters.
 */

   void addWordCharacters(std::string str);

/*
 * Method: addOperator
 * Usage: scanner.addOperator(op);
 * -------------------------------
 * Defines a new multicharacter operator.  Whenever you call
 * <code>nextToken</code> when the input stream contains operator
 * characters, the scanner returns the longest possible operator
 * string that can be read at that point.
 */

   void addOperator(std::string op);

/*
 * Method: getPosition
 * Usage: int pos = scanner.getPosition();
 * ---------------------------------------
 * Returns the current position of the scanner in the input stream.
 * If <code>saveToken</code> has been called, this position corresponds
 * to the beginning of the saved token.  If <code>saveToken</code> is
 * called more than once, the position is unavailable.
 */

   int getPosition() const;

/*
 * Method: isWordCharacter
 * Usage: if (scanner.isWordCharacter(ch)) . . .
 * ---------------------------------------------
 * Returns <code>true</code> if the character is valid in a word.
 */

   bool isWordCharacter(char ch) const;

/*
 * Method: verifyToken
 * Usage: scanner.verifyToken(expected);
 * -------------------------------------
 * Reads the next token and makes sure it matches the string
 * <code>expected</code>.  If it does not, <code>verifyToken</code>
 * throws an error.
 */

   void verifyToken(std::string expected);

/*
 * Method: getTokenType
 * Usage: TokenType type = scanner.getTokenType(token);
 * ----------------------------------------------------
 * Returns the type of this token.  This type will match one of the
 * following enumerated type constants:
 *
 *    <code>EOF</code>,
 *    <code>SEPARATOR</code>,
 *    <code>WORD</code>,
 *    <code>NUMBER</code>,
 *    <code>STRING</code>, or
 *    <code>OPERATOR</code>.
 */

TokenType getTokenType(std::string token) const;

#include "private/tokenscannerpriv.h"

};

#endif

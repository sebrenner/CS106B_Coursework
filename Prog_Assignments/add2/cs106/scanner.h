/*
 * File: scanner.h
 * ---------------
 * This file is the interface for a class that facilitates dividing
 * a string into logical units  called "tokens", which are either
 *
 * 1. Strings of consecutive letters and digits representing words
 * 2. One-character strings representing punctuation or separators
 *
 * To use this class, you must first create an instance of a
 * Scanner object by declaring
 *
 *      Scanner scanner;
 *
 * You initialize the scanner's input a particular string by calling
 *
 *      scanner.setInput(str);
 *
 * where str is the string from which tokens should be read.  To
 * retrieve each individual token, you make the following call:
 *
 *      token = scanner.nextToken();
 *
 * To determine whether any tokens remain to be read, you can call
 * the predicate member function scanner.hasMoreTokens().  The 
 * nextToken member function returns the empty string after the last 
 * token is read.
 *
 * The following code fragment serves as an idiom for processing
 * each token in the string inputString:
 *
 *      Scanner scanner; 
 *      scanner.setInput(inputString);
 *      while (scanner.hasMoreTokens()) {
 *          string token = scanner.nextToken();
 *          . . . process the token . . .
 *      }
 * 
 * Note that it is possible for clients to have more than one scanner
 * active at the same time.  For instance
 *
 *      Scanner scannerX, scannerY;
 *
 * creates two independent scanner objects.  The client specifies a
 * particular object name before the "." in a member function call to 
 * identify which particular instance of the scanner is to be used.
 *
 * The Scanner class also supports the following advanced features,
 * which are documented later in the interface:
 *
 *   saveToken
 *   setSpaceOption
 *   setStringOption
 *   setNumberOption
 *   setBracketOption
 */

#ifndef _scanner_h
#define _scanner_h

#include <string>
#include "genlib.h"




/*
 * Class: Scanner
 * --------------
 * This class is used to represent a single instance
 * of a scanner.  
 */

class Scanner {
  public:

	/*
	 * Constructor: Scanner
	 * Usage: Scanner scanner;
	 *        Scanner *sp = new Scanner;
	 * ---------------------------------
	 * The constructor initializes a new scanner object. The scanner
	 * starts empty, with no input to scan.
	 */
	Scanner();


	/*
	 * Destructor: ~Scanner
	 * Usage: delete sp;
	 * -----------------
	 * The destructor deallocates the storage associated with this scanner.
	 */
	~Scanner();


	/*
	 * Member function: setInput
	 * Usage: scanner.setInput(str);
	 * -----------------------------
	 * This member function configures this scanner to start extracting 
	 * tokens from the input string str. Any previous input string is
	 * discarded.
	 */
	void setInput(string str);


	/*
	 * Member function: nextToken
	 * Usage: token = scanner.nextToken();
	 * -----------------------------------
	 * This member function returns the next token from this scanner.  If
	 * nextToken is called when no tokens are available, it returns the
	 * empty string.  
	 */
	string nextToken();

	/*
	 * Member function: hasMoreTokens
	 * Usage: if (scanner.hasMoreTokens()) . . .
	 * ------------------------------------------
	 * This member function returns true as long as there are additional
	 * tokens for this scanner to read.
	 */
	bool hasMoreTokens();

	/*
	 * Member function: saveToken
	 * Usage: scanner.saveToken(token);
	 * --------------------------------
	 * This member function restores token into this scanner's input
	 * in such a way that the next time nextToken is called, the scanner
	 * will return this token without reading any additional characters
	 * from the input. 
	 */
	void saveToken(string token);

	/*
	 * Member functions: setSpaceOption, getSpaceOption
	 * Usage: scanner.setSpaceOption(option);
	 *        option = scanner.getSpaceOption();
	 * ------------------------------------------
	 * This member function controls whether this scanner
	 * ignores whitespace characters or treats them as valid tokens.
	 * By default, the nextToken function treats whitespace characters,
	 * such as spaces and tabs, just like any other punctuation mark.
	 * If, however, you call
	 *
	 *    scanner.setSpaceOption(Scanner::IgnoreSpaces);
	 *
	 * the scanner will skip over any white space before reading a
	 * token. You can restore the original behavior by calling
	 *
	 *    scanner.setSpaceOption(Scanner::PreserveSpaces);
	 *
	 * The getSpaceOption function returns the current setting
	 * of this option.
	 */

	enum spaceOptionT { PreserveSpaces, IgnoreSpaces };

	void setSpaceOption(spaceOptionT option);
	spaceOptionT getSpaceOption();

    /*
     * Member functions: setNumberOption, getNumberOption
     * Usage: scanner.setNumberOption(option);
     *        option = scanner.getNumberOption();
     * --------------------------------------------------
     * This member function controls whether this scanner treats numeric
     * values specially.  The default behavior for a scanner is to treat
     * digits as equivalent to letters.  If you call
     *
     *    scanner.setNumberOption(Scanner::ScanNumbersAsIntegers);
     *
     * a token beginning with a digit will end at the first nondigit.
     * (Note that digits can still be scanned as part of a token as in
     * the token "x1".)  If you call
     *
     *    scanner.setNumberOption(Scanner::ScanNumbersAsReals);
     *
     * the scanner will return the longest token string that represents
     * a real number, if the next character to be scanned is a digit.
     * The format for a real number is a sequence of digit characters
     * that may include at most one decimal point, optionally followed
     * by the letter 'E' in either upper- or lowercase, an optional sign,
     * and an exponent.  You can restore the default behavior by calling
     *
     *    scanner.setNumberOption(Scanner::ScanNumbersAsLetters);
     *
     * Even if the number options are enabled, nextToken always returns
     * its result as a string, which means that you need to call
     * StringToInteger or StringToReal to convert the token to a number.
     */
    enum numberOptionT {
        ScanNumbersAsLetters,
        ScanNumbersAsIntegers,
        ScanNumbersAsReals
    };
    
    void setNumberOption(numberOptionT option);
    numberOptionT getNumberOption();

    /*
     * Member functions: setStringOption, getStringOption
     * Usage: scanner.setStringOption(option);
     *        option = scanner.getStringOption();
     * --------------------------------------------------
     * This member function controls how this scanner treats double
     * quotation marks in the input.  The default behavior for a scanner
     * is to treat quotes just like any other punctuation character.
     * If, however, you call
     *
     *    scanner.setStringOption(Scanner::ScanQuotesAsStrings);
     *
     * a token beginning with a quotation mark will be scanned up to
     * the closing quotation mark.  The quotation marks are returned
     * as part of the scanned token so that clients can differentiate
     * strings from other token types.  The original behavior can be
     * restored by calling
     *
     *    scanner.setStringOption(Scanner::ScanQuotesAsPunctuation);
     *
     * When scanning a string, the scanner recognizes the standard
     * escape sequences from ANSI C, such as \n and \t.
     */
    enum stringOptionT { ScanQuotesAsPunctuation, ScanQuotesAsStrings };
    
    void setStringOption(stringOptionT option);
    stringOptionT getStringOption();

    /*
     * Member functions: setBracketOption, getBracketOption
     * Usage: scanner.setBracketOption(option);
     *        option = scanner.getBracketOption();
     * --------------------------------------------
     * This member function controls how this scanner treats angle 
     * brackets in the input.  The default behavior for a scanner is
     * to treat brackets just like any other punctuation character.
     * If, however, you call
     *
     *    scanner.setBracketOption(Scanner::ScanBracketsAsTag);
     *
     * a token beginning with a open < bracket will be scanned up to
     * the closing > bracket.  The brackets are returned
     * as part of the scanned token so that clients can differentiate
     * tags from other token types.  The original behavior can be
     * restored by calling
     *
     *    scanner.setBracketOption(Scanner::ScanBracketsAsPunctuation);
     *
     */
    enum bracketOptionT { ScanBracketsAsPunctuation, ScanBracketsAsTag };
    
    void setBracketOption(bracketOptionT option);
    bracketOptionT getBracketOption();
    
    
  private:

    /*
     * Private attributes -- direct access to these attributes from
     *                       outside the class is not possible
     */

    enum realNumScanStateT {
        InitialState,
        BeforeDecimalPoint,
        AfterDecimalPoint,
        StartingExponent,
        FoundExponentSign,
        ScanningExponent,
        FinalState
    };

    string str;
    int len;
    int cp;
    string savedToken;
    spaceOptionT spaceOption;
    numberOptionT numberOption; 
    stringOptionT stringOption;  
    bracketOptionT bracketOption;
    
    void skipSpaces();
    int scanToEndOfIdentifier();
    int scanToEndOfInteger();
    int scanToEndOfReal();
    string scanQuotedString();
    char scanEscapeCharacter();
    string scanTag();

};

#endif

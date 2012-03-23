/*
 * File: lexiconimpl.cpp
 * ---------------------
 * This file contains the implementation of the lexicon.h interface.
 * Because of the way C++ compiles templates, this code must be
 * available to the compiler when it reads the header file.
 */

#ifdef _lexicon_h

template <typename ClientDataType>
void Lexicon::mapAll(void (*fn)(string word, ClientDataType &),
                     ClientDataType & clientData) {
   foreach (string word in *this) {
      fn(word, clientData);
   }
}

#endif

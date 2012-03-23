This repository contains my coursework for the Stanford's CS 106B: introduction to computer science | programming abstractions class.  http://see.stanford.edu/see/courseinfo.aspx?coll=11f4f422-5670-4b4c-889c-008262e09e4e.  Stanford provides almost all of the course materials for free as a zip download.  

The lectures are available in iTunes, iTunesU, and on YouTube. The course reader is not included in the zip file. But I was able to download a draft pdf of the reader from the class webpage for the current (Spring 2012) CS 106 class: http://www.stanford.edu/class/cs106b/

In starting this class I have had a lot of trouble get my projects to compile. I think quite a few of the problems are related to the age of the CS106B course and course materials. The course is from 2010 and the Xcode project and code were created for Xcode 2.x and 3.x. I was unable to get the projects to work with Xcode 4 so I am using Xcode 3.2.6. All of my coursework is done on a Mac using Xcode 3.2.6. The code files should compile and work on windows or other platforms, but I have only tested them on the Mac. I also spent a lot of time discovering that there are at least two Stanford C++ Libraries. See a full discussion in the dependencies section. 

I am posting my course work to help others interested in complete CS 106B. I will update the repository as I complete problem sets and assignments. Hopefully the code and project files will help others complete the course. If you are interested in discussing the class or specific problem please post an issue or post something in the wiki.

Dependencies

The code included in the repository requires the Stanford libraries. 

THERE ARE MULTIPLE STANFORD C++ LIBRARIES 

Note that there are at least two sets of Stanford Libraries. One set is included in with the course materials. It includes the libraries that are discussed in the class. They are the libraries needed to complete the programming assignments and problems sets.

To complete the exercises in the Reader you will need a different set of libraries. They appear to be newer. They are available at the current (Spring 2012) CS 106B class webpage: http://www.stanford.edu/class/cs106b/. That same page also provides Xcode projects that already include the libraries referred to in the Reader. BE CAREFUL: The libraries include confusingly similar classes and functions. Many have the same name but the capitalization is different. Or they take different arguments. Keeping the two libraries straight in your head is hard.

Install

You can either download the zip or clone the repository to your Mac.

License

My Code is license under The MIT License (MIT): 

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. 

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 

************************************************************** 

The Stanford Course materials are licensed under a Creative Commons Attribution 3.0 United States License.

You can also clone the project with Git by running:

$ git clone git://github.com/sebrenner/Stanford_CS106B_Coursework
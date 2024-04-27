#1. How to run the code

Clone the repository and open in CLion (or any other IDE).

Make sure a C++ compiler is on your device.

Go into the main.cpp code (where all the code for this assignment is located).

Compile and run main.cpp.

Here is documentation on how to clone projects from GitHub using CLion if needed:

https://www.jetbrains.com/help/clion/manage-projects-hosted-on-github.html

This documentation also includes directions on compiling and running applications if needed.

***Some Things to NOTE:***

As the instructions didn't mention requiring user input or menu system, the tests
have been hard coded in the main function.

The tests for the In Memory DB are as displayed in the instruction document with additional tests
created by myself to ensure comprehensive testing of all features and potential error conditions.

For the get method, in the case that NULL is returned because the key doesn't exist
in the DB, it will show as 0 being returned, due to C++ limitations. In the actual code for get(),
NULL is returned, but when it is outputted to the console, C++ writes it as 0.


#2. How this assignment should be modified to become an "official" assignment in the future

To become an official assignment in the future, the instructions should be clearer so that
students have an easier time understanding exactly what is required. For example, for the get()
method, it can be clarified that either NULL or 0 can be returned depending on the programming 
language used (as when the function is declared to return int in C++, it returns 0 instead of NULL).
Additionally, it should be clarified whether or not user input or menu system is required. In the
current instructions, it didn't mention anything about that, so I hard coded the tests, but in the
future it should be made clear if graders want a menu or if they are fine with hardcoded tests.
Other than improving the clarification in the instructions, this is a fun assignment to do.

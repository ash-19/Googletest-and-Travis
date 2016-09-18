Development Roadmap:

1. _Stub_ all possible test cases.
2. Implement _all the stubs_ while periodically running the tests.
    + use something like `g++ -o StudentsTests -std=c++11 Students.o StudentsTests.cpp -L../googletest/googletest -I../googletest/googletest/include -lgtest -lgtest_main -lpthread` to compile and run. Change the directories as needed.
    + Commit after implementation of **each test category** (like after all `AddUser` tests, `RemoveUser` tests, etc.)
3. Create a makefile to run compile and run the tests _locally_ **(and not on travis)**. This will not only help lower the 100 builds limit of travis but also reduce debug time. 
4. Make a `.travis.yml` file and update the `Makefile` to reflect `travis` build changes.
5. Build and test on `travis`.
6. Make sure everything from the assignment specification is completed and done!

Notes:
- Make sure to _code on_ **linux virtual machines**. The `Students.o` file was built on a linux 32-bit system, therefore to use it on our macs would require re-compililation which is not possible (missing Students.cpp).

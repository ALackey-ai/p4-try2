# Working in the Kount Lab

If you are working in the Kount Lab you will need to follow these instructions
to get setup. If you are working on your own machine or in github codespaces
follow the instructions in the [README.md](README.md) file.

## Configuring your project

Run the `debug.sh` script from the terminal to generate the build files for your
project. Note that your output will be slightly different than what is shown
below because cmake configures the build system specific to the system that it
is running on.

```bash
$ ./debug.sh
-- The CXX compiler identification is AppleClang 15.0.0.15000040
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Performing Test COMPILER_HAS_HIDDEN_VISIBILITY
-- Performing Test COMPILER_HAS_HIDDEN_VISIBILITY - Success
-- Performing Test COMPILER_HAS_HIDDEN_INLINE_VISIBILITY
-- Performing Test COMPILER_HAS_HIDDEN_INLINE_VISIBILITY - Success
-- Performing Test COMPILER_HAS_DEPRECATED_ATTR
-- Performing Test COMPILER_HAS_DEPRECATED_ATTR - Success
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Found Readline:
-- Found local install of gtest
-- Configuring done
-- Generating done
-- Build files have been written to: /Users/shane/repos/cpp-project-template/build
```

## Compiling the program

After you have run `debug.sh` you can `cd` into the build directory and compile
the program and then run the example tests.

```bash
[shanepanter@onyx os-starter]$ cd build/
[shanepanter@onyx build]$ make
Scanning dependencies of target lab
[  7%] Building CXX object src/CMakeFiles/lab.dir/lab.cpp.o
...
[100%] Built target gmock_main
```

## Running the tests

You can run the test program by running `make test` from the build directory.

```bash
[shanepanter@onyx build]$ make test
Running tests...
Test project /home/ShanePanter/starter-code-test/os-starter/build
    Start 1: AddTest.Positive
1/1 Test #1: AddTest.Positive .................   Passed    0.11 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.38 sec
[shanepanter@onyx build]$ ./myprogram
Function go called by main version: 0.1
```

## Running the program

```bash
$ ./myprogram
What is your name?shane
Hello shane! This is the starter template version: 0.1
```

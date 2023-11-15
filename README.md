# Overview

This project is divided into several tasks. Each task will be explained in
detail and you are expected to complete each task in order. This project has
been tested on Linux, Windows, and MacOS using github actions. In _theory_ you
could use any operating system you wish to develop and test your solution.
However, the reality of writing native cross platform code is a quagmire of
sadness and despair. Additionally, supporting 3 operating systems and their
respective development environments is beyond the capacity of your instructor
and GA/TA. This project is configured for [VSCode](https://code.visualstudio.com/)
and should work out of the box with [Github Codespaces](https://github.com/features/codespaces).

Students get a free [Github Pro](https://education.github.com/pack) account as
long as you sign up with your Boise State email address. This will allow you to
use Github Codespaces for free in this class. If you run out of free hours on
codespaces you can use the CS department lab machines to complete the project.
You are NOT required to pay for a Github Pro account to complete this project.

You code will be graded using the same setup as github codespaces, office hours
with your instructor or TA/GA will be conducted in the github codespaces, and
all questions about the project will be answered in the context of the github
codespaces.  **ALL** instructions below assume you are working in github
codespaces.

**NOTE:** While students are encouraged to setup their own machine to work on
the project, the instructor and TA/GA will not be able to provide any support
for personal machines. The only supported environment is github codespaces or
the CS department lab machines.

## Task 0 - Pre-reading

- [Grading Rubric](https://shanepanter.com/cs452/grading-rubric.html)
- [Google Test Framework](http://google.github.io/googletest/primer.html#simple-tests)
- (optional)[Developing Cross Platform](https://shanepanter.com/cs452/cross-platform.html)

## Task 1 - Understand Starter Code

This project is setup with a sample `src/lab.h`, `src/lab.cpp`, and
`tests/test-lab.cpp` file to demonstrate how to structure your code and tests.
This project template includes intentional errors in the code and tests to
demonstrate how address sanitizer can help you find bugs in your code. Run the
following commands to see everything in action!

```bash
cmake --preset x64-ASan
cmake --build --preset x64-ASan
```

You should see a bunch of warnings in the output (which is bad), your code
should have no warnings.

```bash
/home/shanep/repos/cpp-project-template/src/lab.cpp:14:16: warning: unused parameter ‘argc’ [-Wunused-parameter]
   14 | int myMain(int argc, char **argv)
      |            ~~~~^~~~
/home/shanep/repos/cpp-project-template/src/lab.cpp:14:29: warning: unused parameter ‘argv’ [-Wunused-parameter]
   14 | int myMain(int argc, char **argv)
```

You can run the executable like this:

```bash
$ ./out/build/x64-ASan/myprogram
What is your name?shane
Hello shane! This is the starter template version: 0.1
```

You can see the tests in action like this:

```bash
$ ctest --preset x64-ASan
Test project /home/shanep/repos/cpp-project-template/out/build/x64-ASan
    Start 1: VersionTest.PositiveNos
1/5 Test #1: VersionTest.PositiveNos ..........   Passed    0.01 sec
    Start 2: AddTest.PositiveNos
2/5 Test #2: AddTest.PositiveNos ..............   Passed    0.01 sec
    Start 3: SegFaultTest.asan
3/5 Test #3: SegFaultTest.asan ................   Passed    0.04 sec
    Start 4: OutOfBoundsTest.fail
4/5 Test #4: OutOfBoundsTest.fail .............***Not Run (Disabled)   0.00 sec
    Start 5: LeakTest.fail
5/5 Test #5: LeakTest.fail ....................***Not Run (Disabled)   0.00 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =   0.06 sec

The following tests did not run:
          4 - OutOfBoundsTest.fail (Disabled)
          5 - LeakTest.fail (Disabled)
```

You can see there are two disabled tests. They are disabled because they fail,
lets run them anyway!

```bash
$ ./out/build/x64-ASan/test-lab --gtest_filter=DISABLED_OutOfBoundsTest.fail --gtest_also_run_disabled_tests
Running main() from /builddir/build/BUILD/googletest-1.13.0/googletest/src/gtest_main.cc
Note: Google Test filter = DISABLED_OutOfBoundsTest.fail
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from DISABLED_OutOfBoundsTest
[ RUN      ] DISABLED_OutOfBoundsTest.fail
=================================================================
==171560==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7f4241500034 at pc 0x7f424425955a bp 0x7ffd10d43490 sp 0x7ffd10d43488
WRITE of size 4 at 0x7f4241500034 thread T0
...
...
Address 0x7f4241500034 is located in stack of thread T0 at offset 52 in frame
    #0 0x7f4244259359 in outOfBounds /home/shanep/repos/cpp-project-template/src/lab.cpp:61

  This frame has 1 object(s):
    [32, 52) 'arr' (line 62) <== Memory access at offset 52 overflows this variable
HINT: this may be a false positive if your program uses some custom stack unwind mechanism, swapcontext or vfork
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow /home/shanep/repos/cpp-project-template/src/lab.cpp:66 in outOfBounds
Shadow bytes around the buggy address:
  0x7f42414ffd80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7f42414ffe00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7f42414ffe80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7f42414fff00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7f42414fff80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x7f4241500000: f1 f1 f1 f1 00 00[04]f3 f3 f3 f3 f3 00 00 00 00
  0x7f4241500080: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7f4241500100: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7f4241500180: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7f4241500200: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7f4241500280: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==171560==ABORTING
```

Play around with the project, see if you can get both of the disabled tests to
pass before you move on to the next task. NOTE: Fixing the failing tests is not
part of you grade, it is just for fun. If you are against having fun you can
skip ahead to Task 2, but be warned skipping fun may make you sad 😢.

## Task 2 - Prepare project

Locate the project you are working on from the [class website](https://shanepanter.com/cs452/projects/),
and download all the necessary starter code. You can find additional
details listed in the assignment on [canvas](https://boisestatecanvas.instructure.com).

Each file provided in the started code is intended to replace the file in this
project with the same name. For example, if the starter code has a file named
`src/lab.h` . Replace the entire contents of `src/lab.h` in your project. Once
you have all the starter code in place you will need to stub out minimal
implementations so everything will compile. Once you have your project compiling
make a commit and push it to github to mark your progress.

This project has a preset file to help build the project. You can list all the
presets with `cmake --list-presets`. You can get started right away with the
Address Sanitizer build as shown below. The executable will be located in the
out/build/x64-ASan directory.

```bash
cmake --preset x64-ASan
cmake --build --preset x64-ASan
```

## Task 3 - Write Unit tests

The starter code included a base set of tests to help guide you to the correct
solution. Using the existing tests as a guide you need to think of some cases
that are not covered by the existing tests and write some additional tests. At
this point the tests should fail, thats ok because you have not written any code
yet, in the next task you will write the code to make the tests pass. This
approach is called [Test Driven
Development](https://en.wikipedia.org/wiki/Test-driven_development) and it is a
very powerful tool for writing high quality code.

At a minimum try to add at least 1 test for each function defined in
`src/lab.h`. You may come back and add more tests later when you start working
on the next task. Writing tests first helps you think about what the functions
should do before you jump into writing the code.

You can run your tests like this:

```bash
cmake --preset x64-ASan
cmake --build --preset x64-ASan
ctest --preset x64-ASan
```

## Task 4 - Write the code

The `src/lab.h` file that you downloaded is well documented, your job is to
implement all the functions defined in that file in `src/lab.cpp`. You are free
to create additional **private** functions in `src/lab.cpp` if you wish but you
are not allowed to add any additional data or modify `src/lab.h`. You are also
not allowed to modify the `app/main.cpp` file in any way. You do not need to
have any unit test for private functions you create in `src/lab.cpp`.

## Task 5 - Complete the Retrospective

Once you have completed everything open the file **Retrospective.md** and
complete each section that has a TODO label. You will need to add your name and
email address to the top of the file or your project will not be graded.

## Task 6 - student.toml

The last thing you need to do is update the `student.toml` file with your name
and Boise State email address.

## Task 7 - Add, Commit, Push your code

Once you are finished you need to make sure that you have pushed all your code
to GitHub for grading! You can do this by running the following commands in the
root of your project directory. You can run `git status` to see what files have
changed since the last commit.

```bash
git add .
git commit -m "My project is finished"
git push
```

## Task 8 - Bonus

As a bonus for those of you who do the work to get everything working on a OS
other than Linux you can claim a bonus of up to 5% of your final project grade.
Your code must configure, build, and run (without errors) on either Windows or
MacOS.

## Task 9 - Extra super bonus

You did the lab in rust! You can claim a bonus of up to 10% of your final
project grade. You can claim both the bonus tasks if you wish.

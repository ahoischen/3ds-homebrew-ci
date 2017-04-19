[![CircleCI](https://circleci.com/gh/ahoischen/3ds-homebrew-ci.svg?style=svg)](https://circleci.com/gh/ahoischen/3ds-homebrew-ci)
[![TravisCI](https://travis-ci.org/ahoischen/3ds-homebrew-ci.svg?branch=master)](https://travis-ci.org/ahoischen/3ds-homebrew-ci)
# 3DS homebrew CI
This repository contains the necessarry configuration files to set up Continuous
Integration for Nintendo 3DS homebrew applications. It also includes an example
project which is also used for testing provider compatibility.

## Compatibility
This project supports .3dsx natively and attempts to support .cia by testing
the corresponding .cci, though differences in functionality are not clear.

Because testing is done in citra all tests are limited by citra's emulation
accuracy. Tests should therefore occasionally be run on actual hardware and
disabled for citra tests. This would be done via tagging the tests.

There is no unit testing framework for the 3ds that is known to work yet. This
*may* change in the future.

This projects aims to support both TravisCI and CircleCI, but TravisCI is still
a work in progress.

An average build takes about 5 minutes right now, which might be a limiting
factor for large projects.

## Creating your own project
Your project must supply a test_runner.3dsx executable, which creates a
`Test Log.txt` and a `Test Finished.bin` file. The `Test Log.txt` contains
all output that would usually be produced by command line tools and
`Test Finished.bin` contains the runner's exit code. For a minimum example
please look at `tests/main.cpp`. 

If you are using CMake to build your projects all you need to do is copy
`circle.yml` or `.travis.yml` to the root of your project and enable CI for
your project. Should there be any dependencies, add them either to your 
`CMakeLists.txt` or to the `.yml` files. The project will be built in the
build directory and assumes you are using
[3ds-cmake](https://github.com/Lectem/3ds-cmake).
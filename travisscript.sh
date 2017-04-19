#!/bin/bash
# This script assumes that the citra emulator is accessible via `citra`, that
# the current directory is the root of the project, that devkitARM is properly
# installed and configured and that cmake and make available.
# The first argument is the filename of the rom containing the test runner.

CITRA_SDMC="${HOME}/.local/share/citra-emu/sdmc"
TEST_EXIT_FILE="${CITRA_SDMC}/Test Finished.bin"
TEST_LOG_FILE="${CITRA_SDMC}/Test Log.txt"

set -e

mkdir -p build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=DevkitArm3DS.cmake ..
make
cd ..
citra $1 &> /dev/null || true 

# Make the log file visible to TravisCI
cat "$TEST_LOG_FILE"

# Return the exit code of the test script.
TEST_EXIT_CODE=`cat "$TEST_EXIT_FILE" || echo 1`
exit $TEST_EXIT_CODE
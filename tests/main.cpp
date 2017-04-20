#include <cstdio>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

#include <3ds.h>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(int argc, char **argv) {

	// Minimum boilerplate to make citra not hang.
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);
	gspWaitForVBlank();
	gfxExit();

	// Redirect all output into the log file.
	int catch_argc = 5;
	char *catch_argv[5] = {"catch", "--reporter", "junit", "--out", "Test Log.txt"};
	int result = Catch::Session().run(catch_argc, catch_argv);

	fclose(stdout);
	int exit_code = 0;
	std::ofstream test_exit_file;
	test_exit_file.open("Test Finished.bin");
	test_exit_file << std::to_string(exit_code);
	test_exit_file.close();

	return exit_code;
}
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

#include <3ds.h>

int main(int argc, char **argv) {

	// Minimum boilerplate to make citra not hang.
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);
	gspWaitForVBlank();
	gfxExit();

	// Redirect all output into the log file.
	stdout = fopen("Test Log.txt", "w");
	printf("Hello Continually Integrated 3DS World!\n");

	fclose(stdout);
	int exit_code = 0;
	std::ofstream test_exit_file;
	test_exit_file.open("Test Finished.bin");
	test_exit_file << std::to_string(exit_code);
	test_exit_file.close();

	return exit_code;
}
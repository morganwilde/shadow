#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include "lib.h"

int main() {
	// Create a drawing grid
	struct winsize terminal;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal);
	int		w = terminal.ws_col,
			h = terminal.ws_row - 1;

	Grid grid = gridInit(w, h);

	Vector v1 = vectorMake(20, 0, 0);
	Vector v2 = vectorMake(0, 10, 0);
	Vector center = vectorMake((int)w/2, (int)h, 0);
	Vector zero = vectorMake(0, 0, 0);

	Vector v3 = vectorSubtract(v1, v2);

	// A mechanism for delay between draws
	struct timespec t;
	t.tv_sec = 0; //1;
	t.tv_nsec = 1000 * 1000 * 100;

	// Rotation
	int		degrees = 0,
			x = 0,
			y = 0,
			z = 0;
	double	radians;
	Vector	v4;

	int test = 1;
	while (test) {
		// Calculations
		v4 = vectorRotate(v1, degrees);
		degrees += 6;
		// Erase the grid
		//grid = gridInit(w, h);

		// Draw a vector
		drawVectorAtOrigin(v4, center, grid);

		// Flush grid to the terminal
		gridDraw(grid);

		//v1.y++;

		nanosleep(&t, NULL);
	}

	return 0;
}

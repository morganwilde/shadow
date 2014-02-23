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
		radians = (degrees * M_PI)/180;
		degrees += 6;
		// Erase the grid
		//grid = gridInit(w, h);

		// Draw a vector
		x = (int)roundf(cos(radians)*v1.x - sin(radians)*v1.y);
		y = (int)roundf(sin(radians)*v1.x + cos(radians)*v1.y);

		v4 = vectorMake(x, y, z);
		drawVectorAtOrigin(v4, center, grid);

		Vector v5 = vectorMake(0, -10, 0);
		drawVectorAtOrigin(v5, center, grid);

		// Draw a rectangle
		Vector r1 = vectorMake(10, 0, 0);
		Vector r2 = vectorMake(0, 10, 0);
		Vector r3 = vectorMake(10, 6, 0);
		Vector r4 = vectorMake(0, 16, 0);
		Vector r5 = vectorMake(10, -6, 0);
		Vector r6 = vectorMake(0, -16, 0);
		Vector r7 = vectorMake(-10, 6, 0);

		/*
		drawVectorAtOrigin(r1, zero, grid);
		drawVectorAtOrigin(r2, zero, grid);
		drawVectorAtOrigin(r2, r1, grid);
		drawVectorAtOrigin(r1, r2, grid);
		*/
		drawVectorAtOrigin(r3, zero, grid);
		drawVectorAtOrigin(r4, zero, grid);
		drawVectorAtOrigin(r3, r4, grid);
		drawVectorAtOrigin(r4, r3, grid);
		drawVectorAtOrigin(r5, vectorAdd(r4, r3), grid);
		drawVectorAtOrigin(r6, vectorAdd(r5, vectorAdd(r4, r3)), grid);
		drawVectorAtOrigin(r7, vectorAdd(r6, vectorAdd(r5, vectorAdd(r4, r3))), grid);

		// Flush grid to the terminal
		gridDraw(grid);

		//v1.y++;

		nanosleep(&t, NULL);
	}

	return 0;
}

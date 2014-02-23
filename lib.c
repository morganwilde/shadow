#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib.h"

//
// Utilities
//
int min(int a, int b) {
	return (a > b) ? b : a;
}
int max(int a, int b) {
	return (a > b) ? a : b;
}

Vector vectorMake(int x, int y, int z) {
	Vector v;
	v.x = x;
	v.y = y;
	v.z = z;

	return v;
}

Vector vectorSubtract(Vector v1, Vector v2) {
	Vector v;
	v.x = v2.x - v1.x;
	v.y = v2.y - v1.y;
	v.z = v2.z - v1.z;

	return v;
}

Vector vectorAdd(Vector v1, Vector v2) {
	Vector v;
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;

	return v;
}

float vectorMagnitude(Vector v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

// Initialize the grid
Grid gridInit(int w, int h) {
	Grid grid;
	grid.w = w; // + 1; // Accomodate the extra \n at every line end
	grid.h = h;
	grid.g = (char *)malloc(grid.w * grid.h * sizeof(char));

	// Initialize the grid to blank spaces and \n
	int 	i, j,
			index;
	for (i = 0; i < grid.h; i++) {
		for (j = 0; j < grid.w; j++) {
			index = i * (grid.w - 1) + j;
			if ((j+1) == grid.w)
				grid.g[index] = '\n';
			else
				grid.g[index] = ' ';
		}
	}

	return grid;
}

// Draw it
void gridDraw(Grid grid) {
	printf("%s", grid.g);
}


void drawVector(Vector v, Grid grid) {
	// Draw just the projection of this vector on the x axis
	int x, y, index;
	
	int 	deltaX = v.x,
			deltaY = v.y;
	float	slopeY = (float)deltaY/(float)deltaX,
			slopeX = (float)deltaX/(float)deltaY;
	// Find the axis with the biggest delta
	//printf("deltaX: %d, deltaY: %d\n", deltaX, deltaY);
	if (deltaX >= deltaY && deltaY > 0) {
		for (x = 0; x < deltaX; x++) {
			y = (int)roundf(x * slopeY);
			grid.g[y * grid.w + x] = '*';
		}
	} else if (deltaX > 0 && deltaY == 0) {
		for (x = 0; x < deltaX; x++) {
			grid.g[x] = '*';
		}
	} else if (deltaX == 0 && deltaY > 0) {
		// What to do when delta-x is zero ?
		for (y = 0; y < deltaY; y++) {
			grid.g[y * grid.w] = '*';
		}
	} else if (deltaX == 0 && deltaY == 0) {
		// Point at the origin
		x = deltaX;
		y = deltaY;
		grid.g[y * grid.w + x] = '*';
	} else {
		// Line with switched iteration between x and y
		for (y = 0; y < deltaY; y++) {
			x = (int)roundf(y * slopeX);
			grid.g[y * grid.w + x] = '*';
		}
	}
}

void drawVectorAtOrigin(Vector v, Vector origin, Grid grid) {
	// Draw just the projection of this vector on the x axis
	int x, y, index;
	
	int 	deltaX = abs(v.x),
			deltaY = abs(v.y),
			fromX = min(0, (v.x+1)),
			fromY = min(0, (v.y+1)),
			toX = max(1, v.x),
			toY = max(1, v.y);

	float	slopeY = (float)v.y/(float)v.x,
			slopeX = (float)v.x/(float)v.y;
	// Find the axis with the biggest delta
	if (deltaX >= deltaY && deltaY > 0) {
		for (x = fromX; x < toX; x++) {
			y = (int)roundf(x * slopeY / 2) + origin.y;
			grid.g[y * grid.w + x + origin.x] = '*';
		}
	} else if (deltaX > 0 && deltaY == 0) {
		for (x = fromX; x < toX; x++) {
			y = origin.y;
			grid.g[y * grid.w + x + origin.x] = '*';
		}
	} else if (deltaX == 0 && deltaY > 0) {
		// What to do when delta-x is zero ?
		for (y = fromY; y < toY; y++) {
			x = origin.x;
			grid.g[((int)roundf(y/2)+origin.y) * grid.w + x] = '*';
		}
	} else if (deltaX == 0 && deltaY == 0) {
		// Point at the origin
		x = fromX + origin.x;
		y = toY + origin.y;
		grid.g[y * grid.w + x] = '*';
	} else {
		// Line with switched iteration between x and y
		for (y = fromY; y < toY; y++) {
			x = (int)roundf(y * slopeX) + origin.x;
			grid.g[((int)roundf(y/2)+origin.y) * grid.w + x] = '*';
		}
	}
}

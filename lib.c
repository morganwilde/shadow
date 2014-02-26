#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib.h"

//
// Utilities
//
int min(int a, int b) 
{
	return (a > b) ? b : a;
}
int max(int a, int b) 
{
	return (a > b) ? a : b;
}
float radians(int degrees) 
{
	return (degrees * M_PI)/180;
}

Vector vectorMake(float x, float y, float z) 
{
	Vector v;
	v.x = x;
	v.y = y;
	v.z = z;

	return v;
}

Vector vectorSubtract(Vector v1, Vector v2) 
{
	Vector v;
	v.x = v2.x - v1.x;
	v.y = v2.y - v1.y;
	v.z = v2.z - v1.z;

	return v;
}

Vector vectorAdd(Vector v1, Vector v2) 
{
	Vector v;
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;

	return v;
}

Vector vectorRotate(Vector v, int degrees) 
{
	float rads = radians(degrees);
	Vector rotated;
	rotated.x = (int)roundf(cos(rads)*v.x - sin(rads)*v.y);
	rotated.y = (int)roundf(sin(rads)*v.x + cos(rads)*v.y);
	rotated.z = v.z;

	return rotated;
}

float vectorMagnitude(Vector v) 
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

// Initialize the grid
Grid gridInit(int w, int h) 
{
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
void gridDraw(Grid grid) 
{
	printf("%s", grid.g);
}

// Update it
void gridUpdate(float x, float y, Vector o, Grid grid) 
{
	printf("c: %d [%f, %f]\n", 0, x, y);
	int 	xc = (int)roundf(x + o.x),		// X component
			yc = (int)roundf((y + o.y))/2, // Y component (half because of symbol heigh/width ratio
			coordinate = (grid.w * yc) + xc;
	printf("c: %d [%d, %d]\n", 0, xc, yc);
	grid.g[coordinate] = '*';
}

void drawVectorAtOrigin(Vector v, Vector origin, Grid grid) 
{
	int 	deltaX 		= abs(v.x),
			deltaY 		= abs(v.y),
			fromX 		= min(0, (v.x+1)),
			fromY 		= min(0, (v.y+1)),
			toX 		= max(1, v.x),
			toY 		= max(1, v.y),
			originY 	= origin.y,
			originX 	= origin.x;

	float	slopeY = (float)v.y/(float)v.x,
			slopeX = (float)v.x/(float)v.y;

	// Find the axis with the biggest delta
	if (deltaX >= deltaY) {
		// Iterate over X
		int x;
		for (x = fromX; x < toX; x++) {
			gridUpdate(x, deltaY > 0 ? (x * slopeY) : 0, origin, grid);
		}
	} else {
		// Iterate over Y
		int y;
		for (y = fromY; y < toY; y++) {
			gridUpdate(deltaX > 0 ? (y * slopeX) : 0, y, origin, grid);
		}
	}
}

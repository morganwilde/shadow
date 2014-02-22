#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//
// Custom types
//

// The grid
typedef struct {
	int 	w,
			h;
	char 	*g; // Holds the data to be drawn
} Grid;

// 3D vector
typedef struct {
	int x;
	int y;
	int z;
} Vector;

//
// Functions
//

// Grid
Grid gridInit(int w, int h);

// Vector
Vector vectorMake(int x, int y, int z);
Vector vectorSubtract(Vector v1, Vector v2);
Vector vectorAdd(Vector v1, Vector v2);
float vectorMagnitude(Vector v);

// Drawing
void drawVector(Vector v, Grid grid);
void drawVectorAtOrigin(Vector v, Vector origin, Grid grid);

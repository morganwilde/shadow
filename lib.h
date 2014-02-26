#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//
// Utilities
//

int		 min(int a, int b);
int		 max(int a, int b);
float	 radians(int degrees);

//
// Custom types
//

// The grid
typedef struct {
	int 	w,
			h;
	char 	*g; // Holds the current frame to be drawn
} Grid;

// 3D vector
typedef struct {
	// Due to the limited amount of characters float is good enough
	float 	x,
			y,
			z;
} Vector;

//
// Functions
//

// Grid
Grid	 gridInit(int w, int h);

// Vector
Vector	 vectorMake(float x, float y, float z);
Vector	 vectorSubtract(Vector v1, Vector v2);
Vector	 vectorAdd(Vector v1, Vector v2);
Vector	 vectorRotate(Vector v, int degrees);
float	 vectorMagnitude(Vector v);

// Drawing
void	 drawVector(Vector v, Grid grid);
void	 drawVectorAtOrigin(Vector v, Vector origin, Grid grid);

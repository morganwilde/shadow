#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define CNRM "\x1B[0m"
#define CWHT "\x1B[37m"
#define CMAG "\x1B[36m"
#define CRED "\x1B[31m"

int max(int a, int b) {
	return (a > b) ? a : b;
}
int min(int a, int b) {
	return (a > b) ? b : a;
}

typedef struct {
	int w,		// width
		h,		// height
		**grid; // points to a grid of size = height * width
} Matrix;

typedef struct {
	int x,
		y;
} Point;

Point point(int x, int y) {
	Point p;
	p.x = x;
	p.y = y;

	return p;
}

Matrix matrixInit(int w, int h) {
	Matrix canvas;
	canvas.w = w;
	canvas.h = h;
	// allocate the height of the grid
	canvas.grid = (int **)calloc(h, sizeof(int *));
	// allocate the width's of each line
	int i;
	for (i = 0; i < h; i++) {
		canvas.grid[i] = (int *)calloc(w, sizeof(int));
	}

	return canvas;
}

void matrixDisplay(Matrix canvas) {
	int i, j;
	for (i = 0; i < canvas.h; i++) {
		for (j = 0; j < canvas.w; j++) {
			if (canvas.grid[i][j] > 0)
				printf("%s*%s", CRED, CWHT);
			else
				printf("%s*%s", CWHT, CNRM);
		}
		printf("\n");
	}
}

//
// Drawing
//
void drawLine(Point from, Point to, Matrix canvas) {
	int 	xDelta = to.x - from.x, // horizontal distance
			yDelta = to.y - from.y,	// vertical distance
			x, y,						
			i, j;
	float 	ySlope = (float)yDelta/(float)xDelta,
			xSlope = (float)xDelta/(float)yDelta,
			distance = sqrt(pow(xDelta, 2) + pow(yDelta, 2));

	if (xDelta >= yDelta) {
		for (i = from.x; i < to.x; i++) {
			y = (int)roundf(ySlope * i);
			canvas.grid[y][i] = 1;
		}
	} else {
		for (j = from.y; j < to.y; j++) {
			x = (int)roundf(xSlope * j);
			canvas.grid[j][x] = 1;
		}
	}
}

void drawL(Point from, Point to, Matrix canvas) {
	int 	xDelta = to.x - from.x, // horizontal distance
			yDelta = to.y - from.y,	// vertical distance
			x, y,						
			i, j, k;
	float 	ySlope = (float)yDelta/(float)xDelta,
			xSlope = (float)xDelta/(float)yDelta,
			distance = sqrt(pow(xDelta, 2) + pow(yDelta, 2));

	for (k = 0; k < (int)roundf(distance); k++) {
		x = ySlope * k + from.x;
		y = xSlope * k + from.y;
		canvas.grid[y][x] = 1;
	}
}

int main() {
	struct winsize terminal;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal);

	// Leave room for one command row
	Matrix canvas = matrixInit(terminal.ws_col, terminal.ws_row - 1);
	int x, y;
	//canvas.grid[20][20] = 1;
	Point p1 = point(0, 0);
	Point p2 = point(20, 0);
	Point p3 = point(20, 20);
	drawL(p1, p3, canvas);
	drawL(p1, p3, canvas);
	//drawLine(p1, p2, canvas);
	//drawLine(p2, p3, canvas);

	while (1) {
		matrixDisplay(canvas);
		scanf("%d %d", &x, &y);
		p2 = point(x, y);
		drawLine(p1, p2, canvas);
	}

	return 0;
}

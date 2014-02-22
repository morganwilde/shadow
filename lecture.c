#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	// Storage
	int upTo;
	unsigned long long factorial;

	printf("%lu\n", sizeof(unsigned long long));
	
	// Input
	if (argc == 2) {
		upTo = atoi(argv[1]);
	} else {
		printf("----------\n");
		printf("Calculate the factorial of a number\n");
		printf("----------\n");
		printf("Enter a number: ");
		scanf("%d", &upTo);
	}

	// Calculates the factorial
	int i;
	for (
		i = 1, factorial = 1;
		((i <= upTo) && (i <= 21));
		factorial *= i++, printf("%llu\n", factorial)
		)
		;

	return 0;
}

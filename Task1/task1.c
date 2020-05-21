#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int steps;
	
	if (argc != 3) {
		printf ("Enter 2 arguments\n");
		exit(EXIT_FAILURE);
	} else {
		if ((atoi(argv[1]) > 0) && (atoi(argv[2]) >= 0)) {
			for (int i = 0; i < atoi(argv[1]); i++) {
				if (i % (atoi(argv[2]) + 1) == 0) {
					steps++;
				}
			}
			printf("%d\n", steps);
		} else {
			printf("Enter valid arguments\n");
		}
	}
}


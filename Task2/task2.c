#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int length = 0;
	
	if (argc != 3) {
		printf ("Enter 2 arguments\n");
		exit(EXIT_FAILURE);
	} else {
		if ((atoi(argv[1]) >= 0) && (atoi(argv[2]) > 0)) {
			for (int i = 0; i <= atoi(argv[1]); i++) {
				length += i * atoi(argv[2]);
			}
			printf("%d meters\n", length);
		} else {
			printf("Enter valid arguments\n");
		}
	}
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
	int n = 0;
	int k = 0;
	float steps = 0;
	
	n = atoi(argv[1]);
	k = atoi(argv[2]);
	
	if ((n > 0) && (k >= 0)) {
		if (n % (k + 1) == 0) {
			steps = ceil(n / (k + 1));
		} else {
			steps = ceil(n / (k + 1)) + 1;
		}
			printf("%.0f\n", steps);
	} else {
			printf("Enter valid arguments\n");
	}
}

#include <stdio.h>

int main() {
	int size, cars, i, j, k, x[10000], y[10000], distances[100][100], swap, sort[10000];
	int grid[100][100];
	printf("Size: ");
	scanf("%d", &size);
	while (size > 100) {
		printf("Please enter a size less than 100: ");
		scanf("%d", &size);
	}
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			grid[i][j] = 0;
			distances[i][j] = 0;
		}
	}
	printf("Cars: ");
	for (i = 0;; i++) {
		scanf("%d", &cars);
		if (cars <= size*size)break;
		printf("Please do not enter number of cars more than parking grids: ");
	}
	if (cars < size*size) {
		for (i = 0; i < cars; i++) {
			printf("Location: ");
			scanf("%d %d", &x[i], &y[i]);
		}
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				for (k = 0; k < cars; k++) {
					if (i + 1 >= x[k] && j + 1 >= y[k])distances[i][j] = distances[i][j] + i + 1 - x[k] + j + 1 - y[k];
					else if (i + 1 >= x[k] && j + 1 < y[k])distances[i][j] = distances[i][j] + i + 1 - x[k] - j - 1 + y[k];
					else if (i + 1 < x[k] && j + 1 >= y[k])distances[i][j] = distances[i][j] - i - 1 + x[k] + j + 1 - y[k];
					else if (i + 1 < x[k] && j + 1 < y[k])distances[i][j] = distances[i][j] - i - 1 + x[k] - j - 1 + y[k];
				}
			}
		}
		k = 0;
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				sort[k] = distances[i][j];
				k++;
			}
		}
		for (i = 0; i < size*size - 1; i++)
		{
			for (j = 0; j < size*size - 1 - i; j++)
			{
				if (sort[j] < sort[j + 1])
				{
					swap = sort[j];
					sort[j] = sort[j + 1];
					sort[j + 1] = swap;
				}
			}
		}
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				if (distances[i][j] == sort[0]) {
					printf("Best Slot Found In: %d %d\n", i + 1, j + 1);
				}
			}
		}
	}
	else if (cars == size*size)
		printf("0 0\n");
	return 0;
}

#include <stdio.h>
int pointvalue(int points) {
	char ring, emptychar;
	int segment;
	printf("Throw: ");
	scanf("%d", &segment);
	scanf("%c", &emptychar);
	scanf("%c", &ring);
	if (ring == 'O' || ring == 'o')return points = 25;
	else if (ring == 'I' || ring == 'i')return points = 50;
	else if (ring == 'D' || ring == 'd')return points = segment * 2;
	else if (ring == 'T' || ring == 't')return points = segment * 3;
	else if (ring == 'S' || ring == 's')return points = segment;
}
int remainingpoint(int target, int points ) {
	target = target - points;
	if (target < 0) return target = target + points;
	else
		return target;
}
int main() {
	int target, points = 0;
	printf("Target: ");
	scanf("%d", &target);
	while (target > 0) {
		points = pointvalue(points);
		target = remainingpoint(target, points);
		printf("Points: %d\n", target);
	}
	return 0;
}
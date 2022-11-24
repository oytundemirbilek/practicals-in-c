#include <stdio.h>
#include <math.h>

#define PI 3.14159265

void movement(float new_coordinates[][1], float basismatrix[][2]);
void rotation(float basismatrix[][2]);
void changebasis(float basismatrix[][2]);
char a;

int main() {
	int k;
	float new_coordinates[2][1] = { { 0 },{ 0 } }, basismatrix[2][2] = { { 1, 0 },{ 0, 1 } };
	for (k = 0;; k++) {
		a = getchar();
		if (a == 'm') movement(new_coordinates, basismatrix);
		if (a == 'c') changebasis(basismatrix);
		if (a == 'r' || a == 'l') rotation(basismatrix);
		if (a == 'd') {
			printf("Coordinates: %.2f, %.2f\n", new_coordinates[0][0], new_coordinates[1][0]);
			break;
		}
	}
	return 0;
}
void movement(float new_coordinates[][1], float basismatrix[][2]) {
	float vector[2][1];
	int i, j;
	for (i = 0; i < 2; ++i) {
		for (j = 0; j < 1; ++j) {
			scanf("%f", &vector[i][j]);
		}
	}
	new_coordinates[0][0] = basismatrix[0][0] * vector[0][0] + basismatrix[0][1] * vector[1][0] + new_coordinates[0][0];
	new_coordinates[1][0] = basismatrix[1][0] * vector[0][0] + basismatrix[1][1] * vector[1][0] + new_coordinates[1][0];
}
void rotation(float basismatrix[][2]) {
	float x, rad;
	int deg;
	float rotationmatrix[2][2];
	float newbasis[2][2];
	int i, j;
	scanf("%d", &deg);
	rad = PI / 180.0;
	if (a == 'l') {

		rotationmatrix[0][0] = cos(deg*rad);
		rotationmatrix[0][1] = -sin(deg*rad);
		rotationmatrix[1][0] = sin(deg*rad);
		rotationmatrix[1][1] = cos(deg*rad);

		newbasis[0][0] = basismatrix[0][0] * rotationmatrix[0][0] + basismatrix[0][1] * rotationmatrix[1][0];
		newbasis[1][0] = basismatrix[1][0] * rotationmatrix[0][0] + basismatrix[1][1] * rotationmatrix[1][0];
		newbasis[0][1] = basismatrix[0][0] * rotationmatrix[0][1] + basismatrix[0][1] * rotationmatrix[1][1];
		newbasis[1][1] = basismatrix[1][0] * rotationmatrix[0][1] + basismatrix[1][1] * rotationmatrix[1][1];

		basismatrix[0][0] = newbasis[0][0];
		basismatrix[0][1] = newbasis[0][1];
		basismatrix[1][0] = newbasis[1][0];
		basismatrix[1][1] = newbasis[1][1];
	}
	if (a == 'r') {
		rotationmatrix[0][0] = cos(deg*rad);
		rotationmatrix[0][1] = sin(deg*rad);
		rotationmatrix[1][0] = -sin(deg*rad);
		rotationmatrix[1][1] = cos(deg*rad);

		newbasis[0][0] = basismatrix[0][0] * rotationmatrix[0][0] + basismatrix[0][1] * rotationmatrix[1][0];
		newbasis[1][0] = basismatrix[1][0] * rotationmatrix[0][0] + basismatrix[1][1] * rotationmatrix[1][0];
		newbasis[0][1] = basismatrix[0][0] * rotationmatrix[0][1] + basismatrix[0][1] * rotationmatrix[1][1];
		newbasis[1][1] = basismatrix[1][0] * rotationmatrix[0][1] + basismatrix[1][1] * rotationmatrix[1][1];

		basismatrix[0][0] = newbasis[0][0];
		basismatrix[0][1] = newbasis[0][1];
		basismatrix[1][0] = newbasis[1][0];
		basismatrix[1][1] = newbasis[1][1];
	}
}
void changebasis(float basismatrix[][2]) {
	int i, j;
	for (i = 0; i < 2; ++i) {
		for (j = 0; j < 2; ++j) {
			scanf("%f", &basismatrix[i][j]);
		}
	}
}
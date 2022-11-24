#include <stdio.h>
#include <math.h>

#define MAX_ERROR 0.001

float a, b, p, c, t, x;
int up_lim, down_lim;
int coef1, coef2, coef3;
int r1, r2;
float root1, root2;
float bisection1(float a, float b), bisection2(float a, float c), bisection3(float a,float b), numbers(int coef1, int coef2);
float equation(float x);
void findroots(void);

int main() {
	scanf("%d %d %d %d %d", &coef1, &coef2, &coef3, &down_lim, &up_lim);
	printf("Entered equation: %dx^2 + %dx + %d", coef1, coef2, coef3);
	printf("\nDomain: %d, %d", down_lim, up_lim);
	findroots();
	return 0;
}
//main function only calls findroots function, scans the entered numbers and prints domain and equation.
float numbers(int coef1, int coef2) {
	if (coef1 != 0) {
		a = -coef2 / (2 * coef1);
		b = a;
		c = a;
		for (;;) {//searches for roots left of a.
			b--;
			if (equation(a) == 0)break;
			if (coef1*equation(a) > 0) break;
			if (equation(a)*equation(b) < 0) break;
		}
		for (;;) {//searches for roots right of a.
			c++;
			if (equation(a) == 0)break;
			if (coef1*equation(a) > 0) break;
			if (equation(a)*equation(c) < 0) break;
		}
		return a, b, c;
	}
	if (coef1 == 0) {//searches for roots if it is a linear equation.
		a = up_lim;
		b = a;
		for (;;) {
			if (equation(a)*equation(b) <= 0) break;
			if (equation(up_lim)*equation(down_lim) > 0)break;
			b--;
		}
		return a, b;
	}
}
//numbers function chooses the numbers that can use for bisection.
float bisection1(float a, float b) {
	p = (a + b) / 2;
	if (p != b && (equation(p)*equation(b) < 0)) a = p;
	if (p != a && (equation(a)*equation(p) < 0)) b = p;
	else if (((equation(p) < MAX_ERROR) && equation(p) >= 0) || ((equation(p) > -MAX_ERROR) && equation(p) <= 0)) {
		root1 = p;
		return root1;
	}
	return bisection1(a, b);//if the conditions do not exist, function calls itself.
}
//bisection1 function implies the bisection method for root1 which is left of a.
float bisection2(float a, float c) {
	p = (a + c) / 2;
	if (p != c && (equation(p)*equation(c) < 0)) a = p;
	if (p != a && (equation(a)*equation(p) < 0)) c = p;
	else if (((equation(p) < MAX_ERROR) && equation(p) >= 0) || ((equation(p) > -MAX_ERROR) && equation(p) <= 0))  {
		root2 = p;
		return root2;
	}
	return bisection2(a, c);
}
//bisection2 function implies the bisection method for root2 which is right of a.
float bisection3(float a, float b) {
	if (p != b && (equation(p)*equation(b) < 0)) a = p;
	if (p != a && (equation(a)*equation(p) < 0)) b = p;
	else if (((equation(p) < MAX_ERROR) && equation(p) >= 0) || ((equation(p) > -MAX_ERROR) && equation(p) <= 0)) {
		root1 = p;
		r1 = 1;
		return root1;
	}
	p = (a + b) / 2;
	return bisection3(a, b);
}
//bisection3 function implies the bisection method for linear equations.
void findroots(void) {
	float t;
	t = -coef2 / 2 * coef1;
	numbers(coef1, coef2);
	if (coef1*equation(t) < 0) {//bisection functions only work for equations that have at least two different roots.
		bisection1(a, b);
		bisection2(a, c);
		if ((root1 <= up_lim && root1 >= down_lim) && (root2 > up_lim || root2 < down_lim)) printf("\nRoot: x = %.3f ", root1);
		if ((root2 <= up_lim && root2 >= down_lim) && (root1 > up_lim || root1 < down_lim)) printf("\nRoot: x = %.3f ", root2);
		if ((root2 <= up_lim && root2 >= down_lim) && (root1 <= up_lim && root1 >= down_lim)) printf("\nRoots: x = %.3f x = %.3f", root1, root2);
	}
	if ((coef1 == 0)) {//calls the numbers function and applies the bisection for linear equations.
		numbers(coef1, coef2);
		if (b + 1 > down_lim)bisection3(a, b);
		if ((r1 == 1) && (root1 <= up_lim && root1 >= down_lim))printf("\nRoot: x = %.3f ", root1);
	}
	if (equation(t) == 0 || equation(t)*coef1 > 0)printf("\nNo Roots Found");
	if ((root1 > up_lim || root1 < down_lim) && (root2 > up_lim || root2 < down_lim)) printf("\nNo Roots Found");
	printf("\n");
}
//findroots function calls numbers and bisection functions regarding the conditions and prints the roots.
float equation(float x) {
	return coef1*x*x + coef2*x + coef3;
}
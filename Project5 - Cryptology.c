#include <stdio.h>
#include <ctype.h>
void decryptAuxiliaries(int *mod, char *ptrb, int *modifier), checkCorruption(char *ptrc, char *ptrn, char *ptrb, int *check);
void decryptName(int mod, int modifier, char *ptrc), decryptNumber(char *ptrn);
int main() {
	char name[11], number[10], binary[6];
	char *ptrc, *ptrn, *ptrb;
	int i, mod = 0, modifier = 0, check = 1;
	ptrc = name;
	ptrn = number;
	ptrb = binary;
	printf("Enter the line to decrypt: ");
	for (i = 0; i < 24; i++) {
		if (i<10) scanf("%c", ptrc + i);
		else if (i >= 10 && i < 19) scanf("%c", ptrn + (i - 10));
		else if (i >= 19) scanf("%c", ptrb + (i - 19));
	}
	checkCorruption(ptrc, ptrn, ptrb, &check);
	if (check == 0) { 
		printf("Data is Corrupted\n");
		
		return 1;
	}
	else if (check != 0) {
		printf("Decrypted ---");
		decryptAuxiliaries(&mod, ptrb, &modifier);

		printf("\nNumber: ");
		decryptNumber(ptrn);
		for (i = 0; i < 9; i++)printf("%c", *(ptrn + i));

		printf("\nName: ");
		decryptName(mod, modifier, ptrc);
		for (i = 0; i < 10; i++)printf("%c", *(ptrc + i));

		printf("\nMode: %d", mod);
		printf("\nModifier: %d\n", modifier);

	}
	return 0;
}
void decryptName(int mod, int modifier, char *ptrc) {
	int i, counter = 0;
	char x[5], *ptrx = x;
	switch (mod) {
	case 0: break;
	case 1: //decrypts forwardly encrypted text
		for (i = 0; i < 10; i++) {
			while (modifier != 0) {
				if (*(ptrc + i) == 97) { 
					*(ptrc + i) = 122; 
					modifier--;
					counter++;
				}
				else {
					*(ptrc + i) = *(ptrc + i) - 1;
					modifier--;
					counter++;
				}
			}
			if (modifier == 0) {//assigns the modifier for the next character
				modifier = counter;
				counter = 0;
			}
		}
			break;
	case 2: //decrypts backwardly encrypted text
		for (i = 0; i < 10; i++) {
			while (modifier != 0) {
				if (*(ptrc + i) == 122) {
					*(ptrc + i) = 97;
					modifier--;
					counter++;
				}
				else {
					*(ptrc + i) = *(ptrc + i) + 1;
					modifier--;
					counter++;
				}
			}
			if (modifier == 0) {
				modifier = counter;
				counter = 0;
			}
		}
		break;
	case 3:
		for (i = 0; i < 10; i++) {
			if (i < 5) {
				*(ptrx + i) = *(ptrc + i); //keeps the previous character
				*(ptrc + i) = *(ptrc + 9 - i);//assigns the characters to their symmetrical ones
			}
			if(i>=5)*(ptrc + i) = *(ptrx + 9 - i);//assigns other half of the characters to their symmetrical ones
		}
		   break;
	}
}
void decryptNumber(char *ptrn) { //gives the transpose of the number matrix
	char a, b, c; //keeps previous digits
	a = *(ptrn+1);
	*(ptrn+1) = *(ptrn + 3);
	*(ptrn + 3) = a;
	b = *(ptrn + 2);
	*(ptrn + 2) = *(ptrn + 6);
	*(ptrn + 6) = b;
	c = *(ptrn + 5);
	*(ptrn + 5) = *(ptrn + 7);
	*(ptrn + 7) = c;
}
void decryptAuxiliaries(int *mod, char *ptrb, int *modifier) {
	int A[5], i;
	int *ptra = A;
	for (i = 0; i < 5; i++) {
		*(ptra + i) = *(ptrb + i) - '0';
		//assigns binary numbers to an integer array, minus '0' is needed because the computer adds its ASCII value in mathematical operations
	}
	*mod = *ptra * 2 + *(ptra+1); 
	*modifier = *(ptra+2) * 4 + *(ptra+3) * 2 + *(ptra+4);
	//converts binary into decimal system
}
void checkCorruption(char *ptrc, char *ptrn, char *ptrb, int *check) {
	int i;
	for (i = 0; i < 24; i++) {
		if (i < 10) {
			if (!(islower(*(ptrc + i)))) {//checks first 10 characters that must be lower alphabetical characters
				*check = 0;
				break;
			}
		}
		else if (i >= 10 && i < 19) {//checks next 9 characters that must be digits
			if (!(isdigit(*(ptrn + i - 10)))) { 
				*check = 0;
				break;
			}
		}
		else if (i >= 19) {
			if (*(ptrb + i - 19) != '0' && *(ptrb + i - 19) != '1') {//checks next 5 characters that must be 0 or 1
				*check = 0;
				break;
			}
		}
	}
}

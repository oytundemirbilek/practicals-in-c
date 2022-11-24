#include <stdio.h>

int main() {
	int day, month, year, endyear, weekday, q, m, j, k, check = 0, tempyear, i, tempweekday, counter = 0;
	printf("Enter date [year month day]: ");
	scanf("%d", &year);
	scanf("%d", &month);
	scanf("%d", &day);
	if (year < 0 || month < 1 || month > 12) {
		check = 1;
		printf("Invalid date.");
	}
	else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
		if (day < 1 || day > 31) { 
			check = 1; 
			printf("Invalid date."); 
		}
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day < 1 || day > 30) {
			check = 1;
			printf("Invalid date.");
		}
	}
	else if (month == 2 && year % 4 == 0) {
		if (day < 1 || day > 29) {
			check = 1;
			printf("Invalid date.");
		}
	}
	else if (month == 2 && year % 4 != 0) {
		if (day < 1 || day > 28) {
			check = 1;
			printf("Invalid date.");
		}
	}
	if (check == 0) {
		printf("Enter end year: ");
		scanf("%d", &endyear);
		q = day;
		m = month;
		if (m != 1 && m != 2) {

			j = year / 100;
			k = year - 100 * j;
			weekday = (q + k + 5 * j + (k / 4) + (j / 4) + 13 * (m + 1)/5) % 7;
		}
		else {
			m = m + 12;
			tempyear = year - 1;
			j = tempyear / 100;
			k = tempyear - 100 * j;
			weekday = (q + k + 5 * j + (k / 4) + (j / 4) + 13 * (m + 1)/5) % 7;
		}
		switch (weekday){
			case 0: printf("It's a Saturday. \n"); break;
			case 1: printf("It's a Sunday. \n"); break;
			case 2: printf("It's a Monday. \n"); break;
			case 3: printf("It's a Tuesday. \n"); break;
			case 4: printf("It's a Wednesday. \n"); break;
			case 5: printf("It's a Thurday. \n"); break;
			case 6: printf("It's a Friday. \n"); break;
		}
		for (i = year; i < endyear; i++) {
			if (m != 1 && m != 2) {

				j = i / 100;
				k = i - 100 * j;
				tempweekday = (q + k + 5 * j + (k / 4) + (j / 4) + 13 * (m + 1) / 5) % 7;
			}
			else {
				m = m + 12;
				tempyear = i - 1;
				j = tempyear / 100;
				k = tempyear - 100 * j;
				tempweekday = (q + k + 5 * j + (k / 4) + (j / 4) + 13 * (m + 1) / 5) % 7;
			}
			if (tempweekday == weekday)counter++;
		}
		printf("Same day-and-month on same weekday between %d and %d: %d\n", year++, endyear, counter );
		//system("pause");
		return 0;
	}
}

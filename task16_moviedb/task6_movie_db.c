#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Films {
	char  fname[30];
	char  country[15];
	char  bname[30];
	char  bwriter[30];
	char  fyear[5];
	char  byear[5];
	char  adaption[5];
	char  rating[5];
	float ratingf;
};

int main() {
	struct Films Film[500];
	struct Films temp;
	int choice, i = 0, j = 0, k = 0, n, c, back,size=0;
	float a;
	char rec[30];
	char search[30];
	char line[250];
	printf("Welcome to Movie Database!\n");
	for (i = 0;; i++) {
		back = 0;
		printf("Which action do you want :\n");
		printf("\t1 - Insert a movie\n");
		printf("\t2 - Search a movie\n");
		printf("\t3 - Recommend top movies\n");
		printf("\t4 - Exit\n");
		printf("\n");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			getchar();
			for (j = 0;; j++) {

				printf("Insert a movie with its details(for exit please enter -1): ");

				fgets(line, 250, stdin);
				//Changing all spaces to commas and all commas to spaces to make that they are available for sscanf function
				for (k = 0; k < 250; k++) {
					if (line[k] == ' ') line[k] = ',';
					else if (line[k] == ',') line[k] = ' ';
				}
				//Comes back to menu when -1 is entered
				back = atoi(line);

				if (back == -1)break;
				//sscanf function assigns all elements of struct
				sscanf(line, "%s %s %s %s %s %s %s %s", Film[j].fname, Film[j].fyear, Film[j].country, Film[j].rating, Film[j].adaption, Film[j].bname, Film[j].bwriter, Film[j].byear);
				
				Film[j].ratingf = atof(Film[j].rating);

				//rearranging all commas to spaces and all spaces to commas
				for (k = 0; k < 30; k++) {
					if (Film[j].fname[k] == ',') Film[j].fname[k] = ' ';
					else if (Film[j].fname[k] == ' ') Film[j].fname[k] = ',';
				}
				for (k = 0; k < 30; k++) {
					if (Film[j].bname[k] == ',') Film[j].bname[k] = ' ';
					else if (Film[j].bname[k] == ' ') Film[j].bname[k] = ',';
				}
				for (k = 0; k < 30; k++) {
					if (Film[j].bwriter[k] == ',') Film[j].bwriter[k] = ' ';
					else if (Film[j].bwriter[k] == ' ') Film[j].bwriter[k] = ',';
				}
				printf("%s is inserted\n", Film[j].fname);
				size++;
			}
			break;
		case 2: printf("Please Enter at least 3 characters for searching the database: ");
			scanf("%s", search);
			c = strlen(search);
			for (j = 0; j < 500; j++) {
				for (k = 0; k < 30; k++){
					search = strcat(Film[j].bname[k], search);
					if (strncmp(search, Film[j].fname, c + j) == 0) {
						if (!strcmp(Film[j].adaption , "NO")) {
							printf("\n%s\t%s\t%s\t%s\t%s\n", Film[j].fname, Film[j].fyear, Film[j].country, Film[j].rating, Film[j].adaption);
						}
						else if (!strcmp(Film[j].adaption, "YES")) {
							printf("\n%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", Film[j].fname, Film[j].fyear, Film[j].country, Film[j].rating, Film[j].adaption, Film[j].bname, Film[j].bwriter, Film[j].byear);
						}
					}
				}
			}
			break;
		case 3: printf("How many movies will be listed? ");
			scanf("%d", &n);
			printf("\nWe recommend you top %d movies: ", n);
			//Bubble sort algorithm
			for (j = 0; j < size-1; j++){
				for (k = 0; k < size-j-1; k++){
					if(Film[k].ratingf < Film[k+1].ratingf){
						temp = Film[k];
						Film[k] = Film[k + 1];
						Film[k + 1] = temp;
					}
				}
			}
			for (j = 0; j < n; j++) {
				printf("\n%d. %s %.1f", j + 1, Film[j].fname, Film[j].ratingf);
			}
			printf("\n\n");
			break;
		case 4: printf("Goodbye!\n");
			break;
		}
		if (choice == 4)break;
	}
	
	return 0;
}
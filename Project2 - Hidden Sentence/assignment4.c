#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct instruction_s {
	int step; //line adder
	int index; //word number in that line
};

char* get_word(char* line, int wordn) {
	int counter = 1, k = 0, i = 0;
	char takenword[100];
	counter = 0;
	for (i = 0; line[i] != '\0'; i++) {
		if (line[i] == ' ') {
			counter++;
		}
		else if (counter + 1 == wordn) {
			k = 0;
			while ((line[i] >= 'a' && line[i] <= 'z')|| (line[i] >= 'A' && line[i] <= 'Z')) {
				takenword[k] = line[i];
				k++;
				i++;
			}
			takenword[k] = '\0';
			strcpy(line, takenword);
			break;
		}
	}
	return line;
}

void get_sentence(char** lines, struct instruction_s* ins, int insn, char* sentence) {//book[10000][100], ins, insn, takenline
	int j, nline = ins->step;
	for (j = 0; j < 100; j++) {
		sentence[j] = *(*(lines + nline - 1) + j);
	}

}

int main(int argc, char **argv) {
	struct instruction_s ins;
	char takenline[100], hiddensentence[100], filename[25], temp;
	char** book= malloc(sizeof(char*) * 10000);
	int n, insn = 0, i, j;
	for (i = 0; i < 10000; i++) {
		book[i] = malloc(sizeof(char) * 100);
	}
	ins.step = 0;
	strcpy(hiddensentence, "\0");
	
	for (i = 0; i < 25; i++) {
		filename[i] = argv[argc - 1][i];
	}

	FILE *fp1;
	fp1 = fopen(filename, "r");

	FILE *fp2;
	fp2 = fopen("alice.txt", "r");

	for (i = 0; i < 10000; i++) {
		fgets(book[i], 100, fp2);
	}

	fclose(fp2);

	for (i = 0; i < 500; i++) {
		temp = fgetc(fp1);
		if (temp == '\n')insn++;
	}

	rewind(fp1);

	for (j = 0; j < insn; j++) {

		fscanf(fp1, "%d", &n);
		ins.step = ins.step + n;

		get_sentence(book, &ins, insn, takenline);

		fscanf(fp1, "%d", &ins.index);
		strcat(hiddensentence, get_word(takenline, ins.index));
		
		if(j != insn - 1)strcat(hiddensentence, " ");
		
	}
	for (j = 0; j < 100;j++) {
		if (hiddensentence[j] >= 'A' && hiddensentence[j] <= 'Z')hiddensentence[j] = hiddensentence[j] + 32;
	}
	printf("%s\n", hiddensentence);
	fclose(fp1);
	for (i = 0; i < 10000; i++) {
		free(book[i]);
	}
	free(book);
	//system("pause");
	return 0;
}

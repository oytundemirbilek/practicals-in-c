
/* @Author
* Student Name: Oytun Demirbilek
* Student ID : 150150032
* Date: 08.11.2018 */

#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here

#endif //PCH_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <clocale>

struct occur_node {
	char character;
	occur_node *next;
	int occurence;
};
struct vocab_node {
	char character;
	vocab_node *next;
	occur_node *list;
	occur_node *root;
};
struct vocab_list {
	vocab_node *head;
	vocab_node *iterator;
	void create() {
		head = (vocab_node *)malloc(sizeof(vocab_node));
		head->next = NULL;
		head->list = NULL;
		head->character = '*';
		iterator = head;
	}
	void print() {
		if(iterator->character == ' ')printf("<SP>:\n");
		else printf("%c:\n", iterator->character);
		while (iterator->list->next != NULL) {
			if(iterator->list->character == ' ')printf("\t<<SP>,%d>\n", iterator->list->occurence);
			else printf("\t<%c,%d>\n", iterator->list->character, iterator->list->occurence);
			iterator->list = iterator->list->next;
		}
		if(iterator->list->next == NULL && iterator->list->character != ' '&& iterator->list->character != '\0')printf("\t<%c,%d>\n", iterator->list->character, iterator->list->occurence);
		else if(iterator->list->character == ' ')printf("\t<<SP>,%d>\n", iterator->list->occurence);
		else if(iterator->list->character == '\0')printf("\t<<SP>,%d>\n", iterator->list->occurence);
		iterator = iterator->next;
	}
	void add_char(char nextchar) {

		//Converting capital letters
		if (nextchar >= 'A' && nextchar <= 'Z')nextchar = nextchar + 32;
		if (nextchar == '\n')nextchar = ' ';
		//ADD LETTERS
		if (nextchar >= 'a' && nextchar <= 'z') {
			if (head->character == '*')head->character = nextchar;
			else if (nextchar < head->character) {
				vocab_node * temp = (vocab_node*)malloc(sizeof(vocab_node));
				temp->next = head;
				temp->character = nextchar;
				head = temp;
				iterator = temp;
				temp->list = NULL;
			}
			else if (nextchar > head->character) {
				while (iterator->next != NULL && iterator->next->character < nextchar)iterator = iterator->next;
				if (iterator->next != NULL && iterator->next->character == nextchar){}
				else if (iterator->character > nextchar) {
					vocab_node * temp = (vocab_node*)malloc(sizeof(vocab_node));
					temp->character = nextchar;
					temp->next = iterator;
					temp->list = NULL;
				}
				else if (iterator->character < nextchar) {
					vocab_node * temp = (vocab_node*)malloc(sizeof(vocab_node));
					temp->character = nextchar;
					temp->next = iterator->next;
					iterator->next = temp;
					temp->list = NULL;
				}
			}
		}
		//ADD OTHER CHAR
		else {
			while (iterator->next != NULL && iterator->character != nextchar)iterator = iterator->next;
			if (iterator->character == nextchar){}
			else {
				vocab_node * temp = (vocab_node*)malloc(sizeof(vocab_node));
				temp->character = nextchar;
				temp->next = NULL;
				iterator->next = temp;
				temp->list = NULL;
			}
		}
		iterator = head;
	}
	void add_occurence(char c1, char c2) {
		if (c1 >= 'A' && c1 <= 'Z')c1 = c1 + 32;
		if (c2 >= 'A' && c2 <= 'Z')c2 = c2 + 32;
		if (c1 == '\n')c1 = ' ';
		if (c2 == '\n')c2 = ' ';
		while (iterator->next != NULL && iterator->character != c1)iterator = iterator->next;
		//Creating first occur node
		if (iterator->list == NULL) {
			occur_node * add = (occur_node*)malloc(sizeof(occur_node));
			add->character = c2;
			add->occurence = 1;
			iterator->root = add;
			iterator->list = add;
			add->next = NULL;
		}
		else {
			while (iterator->list->next != NULL && iterator->list->character != c2)iterator->list = iterator->list->next;
			if (iterator->list->character == c2)iterator->list->occurence++;
			else {
				occur_node * add = (occur_node*)malloc(sizeof(occur_node));
				add->character = c2;
				add->occurence = 1;
				iterator->list->next = add;
				add->next = NULL;
			}
		}
		iterator->list = iterator->root;
		iterator = head;
	}
	int get_occurence(char c) {
		int counter = 0;
		iterator->list = iterator->root;
		while (iterator->next != NULL && iterator->character != c)iterator = iterator->next;
		if (iterator->list->next == NULL && iterator->character == c)counter = counter + iterator->list->occurence;

		while (iterator->list->next != NULL && iterator->character == c) {
			counter = counter + iterator->list->occurence;

			iterator->list = iterator->list->next;
			if (iterator->list->next == NULL)counter = counter + iterator->list->occurence;

		}
		return counter;
	}
	int get_union_occurence(char c1, char c2) {
		int counter = 0;
		iterator->list = iterator->root;
		while (iterator->next != NULL && iterator->character != c1)iterator = iterator->next;
		while (iterator->list->next != NULL && iterator->list->character != c2)iterator->list = iterator->list->next;
		counter = iterator->list->occurence;
		return counter;
	}
};
struct language_model {
	vocab_list *vocabularylist;
	void readData(const char * filename) {
		vocabularylist = (vocab_list*)malloc(sizeof(vocab_list));

		FILE *fp1 = fopen(filename, "r");
		int counter = 0;
		while (!feof(fp1)) {
			fgetc(fp1);
			counter++;
		}

		rewind(fp1);

		char *input;
		input = (char*)malloc(counter * sizeof(char));
		fgets(input, counter, fp1);

		char c0;
		char c1, c2;

		vocabularylist->create();

		for (int i = 0; i < counter; i++) {
			c0 = input[i];
			vocabularylist->add_char(c0);
		}

		rewind(fp1);
		fgets(input, counter, fp1);

		for (int i = 0; i < counter; i++) {
			c1 = input[i];
			c2 = input[i + 1];
			vocabularylist->add_occurence(c1, c2);
		}
		fclose(fp1);
	}
	double calculateProbability(char x1, char x2) {
		double prob;
		double n1;
		double n2;
		n1 = vocabularylist->get_union_occurence(x1,x2);
		n2 = vocabularylist->get_occurence(x1);
		if(n2 != 0)prob = n1 / n2;
		else prob = 0;
		return prob;
	}
};

struct language_model *getinput;

int main(int argc, char **argv)
{
	getinput = (language_model*)malloc(sizeof(language_model));
	double probability;
	
	setlocale(LC_ALL, "Turkish");
	
	char inputc1, inputc2;
	if (argc > 2) {//if 2 extra chars are entered
		if(!strcmp("<SP>", argv[2]))argv[2][0] = ' ';
		if(!strcmp("<SP>", argv[3]))argv[3][0] = ' ';
		inputc1 = argv[2][0];
		inputc2 = argv[3][0];
		getinput->readData(argv[1]);
		probability = getinput->calculateProbability(inputc1, inputc2);
		printf("%lf", probability);
	}
	else {//if only the file name is entered
		getinput->readData(argv[1]);
		while(getinput->vocabularylist->iterator->next != NULL)getinput->vocabularylist->print();
	}
	
	return 0;
}

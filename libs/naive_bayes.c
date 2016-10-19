#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "naive_bayes.h"

struct listD{
	int documentClass;
	List* pointer;
	ListD* next;
};

ListD* initialize_D(){
	return NULL;
}

ListD* insertD(ListD* listD, List* list, int Dclass){
	ListD* newNode = (ListD*)malloc(sizeof(ListD));

	newNode->pointer = list;
	newNode->documentClass = Dclass;
	newNode->next = listD;
	return newNode;
}

int lenClass(ListD* list, int Dclass){
	int size = 0;
	while (list != NULL){
		if (list->documentClass == Dclass)
			size += len(list->pointer);
		list = list->next;
	}

	return size;
}

void printListD(ListD* list){							//usada para testes
	while (list != NULL){
		printList(list->pointer);
		printf("\n\n");
		list = list->next;
	}
}

int occurrenceD(ListD* list, char* word, int Dclass){	//ocorrencia da palavra "word" nos documentos lista "list" de classe "Dclass" 
	int count = 0;

	while (list != NULL){
		if (list->documentClass == Dclass)
			count += occurrence(list->pointer, word);
		list = list->next;
	}

	return count;
}

int occurrenceT(ListD* list, char* word){				//ocorrencia da palavra "word" em toda a lista
	int count = 0;

	while (list != NULL){
		count += occurrence(list->pointer, word);
		list = list->next;
	}

	return count;
}

double prob(ListD* list, List* text, int Dclass, double probC){
	char word[30];
	double numWord1 = lenClass(list, class1);
	double numWord2 = lenClass(list, class2);
	double numWord3 = lenClass(list, class3);
	double numWord = 0;
	double numTotal = numWord1 + numWord2 + numWord3;
	double prob = log10(probC);
	double aux;
	int* qtd = (int*)malloc(sizeof(int));
	
	switch (Dclass){
		case class1: numWord = numWord1;  break;
		case class2: numWord = numWord2;  break;
		case class3: numWord = numWord3;  break;
	}

	text = content(text, word, qtd);

	while (text != NULL) {
		prob += (*qtd)*log10((occurrenceD(list, word, Dclass) + occurrenceT(list, word)) / (numWord + numTotal));;
		text = content(text, word, qtd);
	}

	aux = (*qtd)*log10((occurrenceD(list, word, Dclass) + occurrenceT(list, word)) / (numWord + numTotal));
	prob += aux;
	free(qtd);
	return prob;
}
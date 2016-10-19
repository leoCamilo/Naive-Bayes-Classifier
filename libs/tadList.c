#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadList.h"

struct list
{
	int qtd;
	char word[30];		// maior palavra do vocabulario brasileiro tem 29 letras
	List* next;
};

List* initialize(){
	return NULL;
}

List* find(List* list, char* word){			//encrontra uma palavra "word" na lista 
	while (list != NULL){
		if (!strcmp(list->word, word))
			return list;
		list = list->next;
	}
	
	return NULL;
}

List* insert(List* list, char* word){
	List* aux = find(list, word);			//caso a palavra já exista na lista, não é alocado um novo nó, ao invés disso é incrementado a sua qtd

	if (aux != NULL){
		aux->qtd++;
		return list;
	}
	else{
		List* newNode = (List*)malloc(sizeof(List));
		sprintf(newNode->word, "%s", word);
		newNode->qtd = 1;
		newNode->next = list;
		return newNode;
	}
}

void printList(List* list){
	while (list != NULL){
		printf(" %d -- %s\n",list->qtd,list->word);
		list = list->next;
	}
}

int len(List* list){						//numero de palavras na lista
	int count = 0;
	
	while (list != NULL){
		count += list->qtd;
		list = list->next;
	}
	
	return count;
}

int isSeparator(char charactere){			//usada internamente, retorna 1 caso o "charactere" seja algum separador
	int i;
	char separators[] = { ' ', ',', '.', ';', '!', '?', '(', ')', '"', '"', '\n', ':', '-', '\0'};
	
	for (i = 0; separators[i]; i++)
		if (charactere == separators[i])
			return 1;
	
	return 0;
}

void addChar(char* word, char C){			//adiciona um char "C" a string "word"
	int i;

	for (i = 0; word[i]; i++);
	word[i] = C;
	word[i + 1] = '\0';
}

List* convertToList(char* text){
	List* wordList = initialize();
	char aux[30] = "";
	int i;

	for (i = 0; text[i]; i++){
		if (isSeparator(text[i])){
			if (aux[0]){
				wordList = insert(wordList, aux);
				aux[0] = '\0';
			}
		}
		else{
			addChar(aux, text[i]);
		}
	}

	if (aux[0])
		wordList = insert(wordList, aux);

	return wordList;
}

List* content(List* list, char* word, int* qtd){
	if (list != NULL){
		strcpy(word, list->word);
		*qtd = list->qtd;
		return list->next;
	}
	else{
		return NULL;
	}
}

int occurrence(List* list, char* word){
	while (list != NULL){
		if (!strcmp(list->word, word))
			return list->qtd;
		list = list->next;
	}

	return 0;
}
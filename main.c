#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libs\tadList.h"
#include "libs\naive_bayes.h"

#define TAM_TEXT_D 14
#define TAM_TEXT_T 100
#define text_teste "clubes catarinenses clubes cultural"	//utilizado para testes

void main(){
	FILE* arqIndex;
	FILE* arqDocument;
	ListD* documentList = initialize_D();	// lista de documentos
	List* textList = initialize();			// lista do texto
	char document[TAM_TEXT_D];				// nome do documento a ser aberto
	char text[TAM_TEXT_T];					// string do texto extraido do documento
	char Dclass;							// numero que representa qual classe o documento está
	int i;

	double qtdDocuments = 0;			// numero total de documentos
	double qtdClass1 = 0;				// numero de documentos da classe 1
	double qtdClass2 = 0;				// numero de documentos da classe 2
	double qtdClass3 = 0;				// numero de documentos da classe 3

	double probClass;
	double probClass2;
	double probClass3;
	double bigestProb = -100;

	clock_t duration;

	arqIndex = fopen("index.txt", "r");
	Dclass = fgetc(arqIndex);

	while (Dclass != -1){
		qtdDocuments++;
		fgets(document, TAM_TEXT_D, arqIndex);
		fgetc(arqIndex);
		arqDocument = fopen(document, "r");
		fgets(text, TAM_TEXT_T, arqDocument);
		documentList = insertD(documentList, convertToList(text), Dclass - 48);
		fclose(arqDocument);

		switch (Dclass){
			case '1': qtdClass1++; break;
			case '2': qtdClass2++; break;
			case '3': qtdClass3++; break;
		}

		Dclass = fgetc(arqIndex);
	}

	fclose(arqIndex);
	//printf(" Digite o texto a ser comparado: ");
	//gets(text);
	printf(" texto de teste: %s\n", text_teste);
	textList = convertToList(text_teste);

	for (i = 0; i < 3; i++){
		probClass = prob(documentList, textList, i + 1, (qtdClass1 / qtdDocuments));
		if (probClass > bigestProb){
			bigestProb = probClass;
			Dclass = i + 1;
		}

	}

	switch (Dclass){
		case 1: printf(" %f - texto da classe Cultura\n", bigestProb); break;
		case 2: printf(" %f - texto da classe Esporte\n", bigestProb); break;
		case 3: printf(" %f - texto da classe Policia\n", bigestProb); break;
		default: printf(" texto sem classificacao definida\n ");
	}

	duration = clock();
	printf(" O programa foi executado em: %.9f segundos\n\n ", ((float)duration) / CLOCKS_PER_SEC);
	system("PAUSE");
}
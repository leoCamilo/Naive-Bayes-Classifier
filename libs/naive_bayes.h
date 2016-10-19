#include "tadList.h"

#define class1 1	// cultura
#define class2 2	// esporte
#define class3 3	// policial

typedef struct listD ListD;	// lista de documentos, lista de lista de palavras

ListD* initialize_D();	//inicializa uma lista de documentos

ListD* insertD(ListD* listD, List* list, int Dclass);	//insere uma lista de palavras na lista de documentos

int lenClass(ListD* list, int Dclass);	//total de palavras da classe "Dclasse" na lista de documentos

double prob(ListD* list, List* text, int Dclass, double probC); // probabilidade ou estimativa de "text" dada uma lista de documentos "list" ser ca classe Dclass
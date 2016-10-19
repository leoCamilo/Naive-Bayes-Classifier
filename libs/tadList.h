typedef struct list List;	// lista de palavras

List* initialize();	//inicializa uma lista de palavras

List* insert(List* list, char* word);	//insere uma palavra na lista

void printList(List* list);	//usada para testes

int len(List* list);	//retorna o numero de palavras da lista

List* convertToList(char* text);	// recebe o texto como argumentos e o converte para uma lista de palavras

List* content(List* list, char* word, int* qtd);	//funciona como um pop, porém não deleta o no antigo e retorna um endereco

int occurrence(List* list, char* word);	//dada uma lista de palavras retorna a quantidade de ocorrencias da mesma
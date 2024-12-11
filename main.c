// Gustavo Rocha Barros 2310505
// Maria Luiza Dutra Gonzalez de Almeida 2310509
// Turma C
#include <stdio.h>
#include <stdlib.h>

struct paciente
{
	int chegada;
	char cor;
	struct paciente *prox;
};
typedef struct paciente Paciente;

FILE *openFile(char *nome, char *modo);
Paciente *insereLista(Paciente *p, int chegada, char cor);
Paciente *removeLista(Paciente *p, int chegada, char cor);
void printaLista(FILE *arq, Paciente *p);
void printaTotais(FILE *arq, Paciente *p);

FILE *openFile(char *nome, char *modo)
{
	FILE *arq = fopen(nome, modo); // inicializa o arquivo desejado no modo desejado

	if (arq == NULL) // confere se o arquivo foi inicializado corretamente
	{
		printf("Erro ao abrir o arquivo txt %s.\n", nome);
		exit(1);
	}

	return arq;
}

Paciente *insereLista(Paciente *pHead, int chegada, char cor)
{
	Paciente *pAux = pHead;								   // inicializa um ponteiro auxiliar para a lista de pacientes
	Paciente *pAuxAux;									   // inicializa um ponteiro para auxiliar nas operações e não perder valores necessários
	Paciente *novo = (Paciente *)malloc(sizeof(Paciente)); // inicializa um ponteiro para adicionar um novo paciente

	if (!novo) // confere se o ponteiro foi inicializado corretamente
	{
		printf("Erro ao alocar memória para inserir novo paciente.\n");
		exit(1);
	}
	novo->chegada = chegada; // insere os valores do paciente no ponteiro
	novo->cor = cor;

	if (pAux == NULL)
	{
		// caso a lista comece vazia
		novo->prox = pAux; // insere o novo no início apontando para NULL
		pHead = novo;	   // a cabeça da lista se torna o novo
	}
	else
	{
		// caso a lista já esteja com informações
		while (pAux != NULL)
		{ // loop percorrendo a lista
			if (cor == 'R')
			{
				// se a cor do novo for vemelha
				if (pAux->cor == 'R')
				{ // se a cor do atual for vermelha
					if ((pAux->prox->cor == 'Y') || (pAux->prox->cor == 'G') || (pAux->prox == NULL))
					{ // caso a próxima cor não seja vermelha
						pAuxAux = pAux->prox;
						pAux->prox = novo;	  // o próximo do atual será o novo paciente
						novo->prox = pAuxAux; // o próxmo do novo paciente será o antigo próximo do atual
						break;
					}
				}
				else if ((pAux->cor == 'Y') || (pAux->cor == 'G'))
				{					   // caso a cor do primeiro da lista não seja vermelha
					pHead = novo;	   // a cabeça da lista é o novo paciente
					novo->prox = pAux; // o próximo do novo é o antigo primeiro
					break;
				}
			}
			else if (cor == 'Y')
			{
				// se a cor do novo for amarela
				if ((pAux->cor == 'Y') || (pAux->cor == 'R'))
				{ // se a cor do atual for amarela ou vermelha
					if ((pAux->prox->cor == 'G') || (pAux->prox == NULL))
					{ // se a cor do próximo for verde ou não houver próximo
						pAuxAux = pAux->prox;
						pAux->prox = novo;	  // o próximo do atual é o novo
						novo->prox = pAuxAux; // o próximo do novo é o antigo próximo do atual
						break;
					}
				}
				else if (pAux->cor == 'G')
				{					   // caso o primeiro da lista seja verde
					pHead = novo;	   // a cabeça da lista é o novo paciente
					novo->prox = pAux; // o próximo do novo é o atual
					break;
				}
			}
			else if (cor == 'G')
			{
				// se a cor do novo for verde
				if (pAux->prox == NULL)
				{ // caso seja o atual último da lista
					pAuxAux = pAux->prox;
					pAux->prox = novo;	  // o próximo do atual é o novo paciente
					novo->prox = pAuxAux; // o próximo do novo é o antigo próximo do atual
					break;
				}
			}
			pAux = pAux->prox; // continua o loop fazendo o atual ser o próximo
		}
	}

	return pHead; // retorna a cabeça da lista alterada
}

Paciente *removeLista(Paciente *p, int chegada, char cor)
{
	Paciente *pAux = p;	   // inicializa um ponteiro auxiliar para a lista de pacientes
	Paciente *pAnt = NULL; // inicializa um ponteiro para o paciente anterior

	if (p == NULL)
	{ // print de lista vazia
		printf("A lista está vazia\n");
		return p;
	}

	while (pAux)
	{														  // realiza um loop passando por toda a lista de pacientes
		if ((chegada == pAux->chegada) && (cor == pAux->cor)) // faz algo caso encontre o paciente desejado
		{
			if (pAnt == NULL) // caso o paciente seja o primeiro da lista
			{
				p = pAux->prox; // a cabeça da lista se torna o próximo
				free(pAux);		// libera o espaço do paciente removido
				return p;		// retorna a lista alterada
			}

			else // caso ele não seja o primeiro da lista
			{
				pAnt->prox = pAux->prox; // faz com que o próximo do anterior seja o próximo do atual, removendo o atual da lista
				free(pAux);				 // libera o espaço de memória do paciente atual
				return p;
			}
		}
		pAnt = pAux;	   // faz o ponteiro do anterior ser o do atual caso não tenha achado
		pAux = pAux->prox; // faz o ponteiro do atual ser o do próximo
	}

	printf("Paciente não encontrado\n"); // caso nenhuma condição seja atendida, significa que não encontrou o paciente
	return p;
}

void printaLista(FILE *arq, Paciente *p)
{
	Paciente *pAux = p; // inicializa um ponteiro auxiliar para a lista de pacientes
	if (!pAux)
	{ // print de lista vazia
		fprintf(arq, "0\n");
		return;
	}

	while (pAux)
	{					// realiza um loop passando por toda a lista de pacientes e escrevendo cada um
		if (pAux->prox) // caso a lista possua um próximo item, ela vai escrever com uma vírgula e espaço
		{
			fprintf(arq, "%c%d, ", pAux->cor, pAux->chegada); // escreve a cor e a ordem de chegada do paciente
		}
		else
		{ // caso seja o final da lista, ela vai escrever apenas o último pacientre
			fprintf(arq, "%c%d", pAux->cor, pAux->chegada);
		}
		pAux = pAux->prox; // ponteiro auxiliar aponta para o próximo para continuar o loop
	}
	fprintf(arq, "\n"); // insere uma quebra de linha no final para preparar o arquivo para futuras escritas
}

void printaTotais(FILE *arq, Paciente *p)
{
	Paciente *pAux = p; // inicializa um ponteiro auxiliar para a lista de pacientes
	int auxG, auxY, auxR;
	auxG = auxY = auxR = 0; // inicializa variáveis que servem de contadores da quantidade de pacientes
	while (pAux)
	{
		switch (pAux->cor) // percorre a lista e adiciona 1 a cada variável dependendo de sua cor
		{
		case 'G':
			auxG++;
			break;

		case 'Y':
			auxY++;
			break;

		case 'R':
			auxR++;
			break;
		}
		pAux = pAux->prox; // aponta o auxiliar para o próximo da lista para continuar o loop
	}

	fprintf(arq, "G-%d\tY-%d\tR-%d\n", auxG, auxY, auxR); // escreve no arquivo de totais a cor e a quantidade de pacientes
}

int main()
{
	FILE *arqEntrada = openFile("pacientes.txt", "r");		  // inicializa o arquivo de onde virão as entradas e saídas de pacientes
	FILE *arqPacientes = openFile("pacientesLista.txt", "w"); // escreve arquivo onde ficará a lista de pacientes na fila de espera
	FILE *arqTotal = openFile("totalCores.txt", "w");		  // escreve arquivo que consta a quantidade de pacientes de cada cor

	char entSai;
	int chegada;
	char cor;
	Paciente *p = (Paciente *)malloc(sizeof(Paciente));
	p = NULL; // inicializando a lista encadeada

	while (fscanf(arqEntrada, "%c, %c, %d\n", &entSai, &cor, &chegada) > 0)
	{ // lê as informações de cada linha do arquivo para saber o que fazer com o paciente
		if (entSai == 'E')
		{
			p = insereLista(p, chegada, cor); // insere o paciente que acabou de chegar
		}
		else if (entSai == 'S')
		{
			p = removeLista(p, chegada, cor); // retira o paciente atendido
		}

		printaLista(arqPacientes, p); // chama a função que escreve no arquivo com a lista de pacientes
		printaTotais(arqTotal, p);	  // chama a função que escreve no arquivo com os totais de pacientes
	}

	fclose(arqEntrada);
	fclose(arqPacientes);
	fclose(arqTotal);
	return 0;
}

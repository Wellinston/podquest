#include "linkedlist.h"


/**
* @brief Função que aloca um espaço do tamanho de uma Celula na memória
* @param info -> Número inteiro a ser guardado nessa Celula
* @return novaCelula, a nova célula som os apontamentos de memória para o próximo ou anterior
*/
Celula llCriaCelula(int info) {

	//Aloca um espaço na memória do tamanho de uma Celula.
	Celula novaCelula = (Celula) malloc(sizeof(No));

	//Setta os valores dessa célula para "vazio".
	novaCelula->info = info;
	novaCelula->prox = NULL;
	novaCelula->prev = NULL;

	//Retorna a nova Celula.
	return novaCelula;
}

/**
* @brief 
* @param 
* @return 
*/
Lista* llCriarLista() {

	//Aloca um espaço na memória do tamando de uma Lista.
	Lista* novaLista = (Lista*) malloc(sizeof(struct lista));

	//Setta o início e fim da lista para "vazio".
	novaLista->inicio = NULL;
	novaLista->fim = NULL;

	//Retorna a nova Lista.
	return novaLista;
}

/**
* @brief
* @param
* @return
*/
void llInsereNoFim(Lista* lista, int info) {

	//Cria a nova Celula a qual vai ser adicionada na Lista.
	Celula novaCelula = llCriaCelula(info);

	//Caso 1: 
	//Se a Lista estiver vazia [...]
	if (lista->inicio == NULL)
	{
		// [...] A nova Celula é inserida e passa a ser o começo e o fim da Lista.
		lista->inicio = novaCelula;
		lista->fim = novaCelula;

		//Sai da função.
		return;
	}

	//Caso 2:
	//Caso a Lista não esteja vazia [...]

	// [...] A próxima Celula do fim atual passa a ser a nova Celula.
	lista->fim->prox = novaCelula;

	// [...] A Celula anterior da nova Celula passa a ser o fim atual da Lista.
	novaCelula->prev = lista->fim;

	// [...] Atualiza-se o fim da lista para a nova Celula.
	lista->fim = novaCelula;
}

/**
* @brief
* @param
* @return
*/
void llInsereNoInicio(Lista* lista, int info) {

	//Cria a nova Celula a qual vai ser adicionada na Lista.
	Celula novaCelula = llCriaCelula(info);

	//Caso 1: 
	//Se a Lista estiver vazia [...]
	if (lista->inicio == NULL)
	{
		// [...] A nova Celula é inserida e passa a ser o começo e o fim da Lista.
		lista->inicio = novaCelula;
		lista->fim = novaCelula;

		//Sai da função.
		return;
	}

	//Caso 2:
	//Caso a Lista não esteja vazia [...]

	// [...] A próxima Celula da nova Celula passa a ser o início atual da Lista.
	novaCelula->prox = lista->inicio;

	// [...] A Celula anterior do inicio atual passa a ser a nova Celula.
	lista->inicio->prev = novaCelula;

	// [...] Atualiza-se o início da lista para a nova Celula.
	lista->inicio = novaCelula;
}

/**
* @brief
* @param
* @return
*/
void llInsereAntesDe(Lista* lista, int info, int alvo) {

	//Cria a nova Celula a qual vai ser adicionada na Lista.
	Celula novaCelula = llCriaCelula(info);

	//Busca a Celula que a nova Celula será inserida antes.
	Celula buscada = llBusca(lista, alvo);

	//Caso 1:
	//Se a Celula existir na Lista [...]
	if (buscada != NULL)
	{

		// [...] A Celula anterior da nova Celula passa a ser o anterior da buscada.
		novaCelula->prev = buscada->prev;

		//Caso 1.1:
		//Caso exista uma Celula antes da Celula buscada [...]
		if (buscada->prev != NULL)
		{
			// [...] essa Celula anterior passa a apontar para a nova Celula.
			buscada->prev->prox = novaCelula;
		}

		//A Celula anterior da Celula buscada passa a ser a nova Celula.
		buscada->prev = novaCelula;

		//A próxima Celula da nova Celula passa a ser a Celula buscada.
		novaCelula->prox = buscada;
	}

	//Caso 2:
	//A Celula buscada não existe na Lista [...]
	else
	{
		// [...] Então será inserida no início da Lista.
		llInsereNoInicio(lista, info);
		free(novaCelula);
	}
}

/**
* @brief
* @param
* @return
*/
void llInsereDepoisDe(Lista* lista, int info, int alvo) {

	//Cria a nova Celula a qual vai ser adicionada na Lista.
	Celula novaCelula = llCriaCelula(info);

	//Busca a Celula que a nova Celula será inserida depois.
	Celula buscada = llBusca(lista, alvo);

	//Caso 1:
	//Se a Celula existir na Lista [...]
	if (buscada != NULL)
	{

		// [...] A Celula seguinte da nova Celula passa a ser o seguinte da buscada.
		novaCelula->prox = buscada->prox;

		//Caso 1.1:
		//Caso exista uma Celula seguinte da Celula buscada [...]
		if (buscada->prox != NULL)
		{
			// [...] essa Celula seguinte passa a apontar para a nova Celula como anterior.
			buscada->prox->prev = novaCelula;
		}

		//A Celula seguinte da Celula buscada passa a ser a nova Celula.
		buscada->prox = novaCelula;

		//A anterior Celula da nova Celula passa a ser a Celula buscada.
		novaCelula->prev = buscada;
	}

	//Caso 2:
	//A Celula buscada não existe na Lista [...]
	else
	{
		// [...] Então será inserida no fim da Lista.
		llInsereNoFim(lista, info);
		free(novaCelula);
	}
}

/**
* @brief
* @param
* @return
*/
void llInsereOrdenado(Lista* lista, int info) {

	//Caso 1:
	//A Lista está vazia ou o número a ser inserido é menor que o número atualmente no início:
	if (lista->inicio == NULL || info < lista->inicio->info)
	{
		//O número é inserido no início.
		llInsereNoInicio(lista, info);
	}

	//Caso 2:
	//O número a ser inserido é maior que o número que está atualmente no fim:
	else if (info > lista->fim->info)
	{
		//O número é inserido no fim.
		llInsereNoFim(lista, info);
	}

	//Caso 3:
	//O número deve ser inserido no meio da Lista:
	else
	{

		//Cria a nova Celula a qual vai ser adicionada na Lista.
		Celula novaCelula = llCriaCelula(info);

		//Criada uma Celula auxiliar, que será usada para percorrer a Lista.
		Celula aux = lista->inicio;

		//Percorrendo a Lista até que seja encontrado o maior número que seja menor que o número que vai ser inserido na Lista.
		while (aux->prox->info <= info)
		{
			aux = aux->prox;
		}

		//A Celula seguinte da nova Celula aponta para a Celula seguinte da Celula auxiliar.
		novaCelula->prox = aux->prox;

		//A Celula seguinte da Celula auxiliar passa a ser a nova Celula.
		aux->prox = novaCelula;

		//A Celula anterior da nova Celula passa a ser a Celula auxiliar
		novaCelula->prev = aux;
	}
}

/**
* @brief
* @param
* @return
*/
void llRemoveFim(Lista* lista) {

	//Caso 1:
	//Se a lista não estiver vazia:
	if (lista->inicio != NULL)
	{
		//Salva o antigo fim da Lista.
		Celula fimRemovido = lista->fim;

		//O penúltimo elemento passa a ser o fim da lista.
		lista->fim = lista->fim->prev;

		//O penúltimo elemento deixa de apontar para um elemento seguinte.
		lista->fim->prox = NULL;

		//Desaloca o espaço da Celula que era o fim.
		free(fimRemovido);
	}
}

/**
* @brief
* @param
* @return
*/
void llRemoveInicio(Lista* lista) {

	//Caso 1:
	//Se a lista não estiver vazia:
	if (lista->inicio != NULL)
	{
		//Salva o antigo início da Lista.
		Celula inicioRemovido = lista->inicio;

		//O segundo elemento passa a ser o início da lista.
		lista->inicio = lista->inicio->prox;

		//O início da Lista deixa de apontar para um elemento anterior.
		lista->inicio->prev = NULL;

		//Desaloca o espaço da Celula que era o início.
		free(inicioRemovido);
	}
}

/**
* @brief
* @param
* @return
*/
Celula llRemoveNo(Lista* lista, int info) {

	//Busca a Celula que será removida.
	Celula buscada = llBusca(lista, info);

	//Caso 1:
	//Caso essa Celula exista:
	if (buscada != NULL)
	{
		//Caso 1.1:
		//A Celula buscada é o início da Lista:
		if (buscada == lista->inicio)
		{
			//O início é removido.
			llRemoveInicio(lista);
		}

		//Caso 1.2:
		//A Celula buscada é o fim da Lista:
		else if (buscada == lista->fim)
		{
			//O fim é removido.
			llRemoveFim(lista);
		}

		//Caso 1.3:
		//A Celula está no meio da Lista
		else
		{
			//A Celula seguinte da Celula anterior da Celula buscada passa a apontar para a Celula anterior da Celula buscada.
			buscada->prox->prev = buscada->prev;

			//A Celula anterior da Celula Seguinte da Celula buscada passa a apontar para a Celula seguinte da Celula buscada.
			buscada->prev->prox = buscada->prox;

			//Retorna a Celula removida.
			return buscada;
		}
	}

	//Caso 2:
	//A Celula não existe.
	return NULL;
}

/**
* @brief
* @param
* @return
*/
Celula llBusca(Lista* lista, int info) {
	
	//Percorre a Lista inteira.
	for (Celula aux = lista->inicio; aux != NULL; aux = aux->prox)
	{
		//Caso o número desejado exista na Lista [...]
		if (aux->info == info)
		{
			// [...] ele é retornado.
			return aux;
		}
	}

	//O número não existe na Lista.
	return NULL;
}

/**
* @brief
* @param
* @return
*/
void llImprimeLista(Lista* lista) {

	//Percorre a Lisa inteira [...]
	for (Celula aux = lista->inicio; aux != NULL; aux = aux->prox)
	{
		// [...] imprimindo o número dentro da Celula atual.
		printf("%d ", aux->info);
	}
	printf("\n");
}

void llImprimePonteiros(Lista* lista) {

	//Percorre a Lisa inteira [...]
	for (Celula aux = lista->inicio; aux != NULL; aux = aux->prox)
	{
		// [...] imprimindo os ponteiros da Celula anterior, Celula atual e Celula seguinte.
		printf("%p <- %p -> %p\n", aux->prev, aux, aux->prox);
	}
	printf("\n");
}

/**
* @brief
* @param
* @return
*/
int llTemCiclo(Lista* lista) {

	//Criadas duas Celulas e apontando-as ao início da Lista.
	Celula rapida = lista->inicio;
	Celula devagar = lista->inicio;

	//Enquanto as Celulas não forem nulas e a primeira tiver Celulas seguintes [...]
	while (rapida != NULL && devagar != NULL && rapida->prox != NULL)
	{

		// [...] A primeira anda duas posições [...]
		rapida = rapida->prox->prox;

		// [...] A segunda anda uma posição [...]
		devagar = devagar->prox;

		// [...] Se elas se encontrarem existe um ciclo.
		if (rapida == devagar)
		{
			return 1;
		}
	}

	//Não existe um ciclo.
	return 0;
}

/**
* @brief
* @param
* @return
*/
Celula swapCelulas(Celula a, Celula b) {
	Celula temp = b;
	a->prox = b->prox;
	a->prev = b;
	b->prox->prev = a;
	b->prev = temp->prev;
	b->prox = a;
	return b;
}

/**
* @brief
* @param
* @return
*/
Celula bubbleList(Celula inicio) {
	if (inicio == NULL || inicio->prox == NULL)
	{
		return;
	}

	Celula atual, prev, head;
	int swapped;

	head = llCriaCelula(-999);
	head->prox = inicio;
	do
	{
		swapped = 0;
		prev = head;
		atual = head->prox;
		while (atual->prox != NULL)
		{
			if (atual->info > atual->prox->info) 
			{
				prev->prox = swapCelulas(atual, atual->prox);
				swapped = 1;
			}

			prev = atual;
			if (atual->prox != NULL)
			{
				atual = atual->prox;
			}
		}

	} while (swapped);

	atual = head->prox;
	free(head);
	return atual;
}
#include <stdlib.h>
#include <stdio.h>

typedef struct episodio {
	int id;
	struct Ep* prox;
	struct Ep* prev;
}Ep;

typedef struct listaEp {
	struct Ep* inicio;
	struct Ep* ultimo;
}ListaEp;

typedef struct podcast{
	int id;
	char nome[10];
	struct Podcast* prox;
	struct Podcast* prev;
	struct ListaEp* epsList;
}Podcast;

typedef struct podCastList {
	struct Podcast* inicio;
	struct Podcast* ultimo;
}podCastList;

typedef struct playlist {
	int tamanho;

	struct podCastList* podCastList;
}Playlist;

typedef struct episodeoAtual{
	struct Ep* episodio;
	struct Podcast* podcast;
}episodeoAtual;

typedef Ep* ep;
typedef Podcast* podcast;
typedef Playlist* playlist;
typedef episodeoAtual* EpisoidoAtual;

void adicionarEpisodio(playlist playlist);
void adicionarPodcast(playlist playlist);
void removerEpisodio(playlist playlist);
void tocarEpisodio(EpisoidoAtual episodeoAtual, playlist playlist);
void shuffle();
void proximo();
void mostarEpisodio(playlist playlist);
void Menu(playlist playlist);

ep criarEp();
playlist criarPlaylist();

int main() {
	playlist playlist = criarPlaylist();
	Menu(playlist);
	return 0;
}


void Menu(playlist playlist) {
	int opcao = -1;
	EpisoidoAtual episodeoAtual = (EpisoidoAtual)malloc(sizeof(EpisoidoAtual));
	episodeoAtual->episodio = NULL;
	episodeoAtual->podcast = NULL;

	while (opcao != 6) {
    printf("1 - Adicionar Podcast\n");
    printf("2 - Adicionar Episódio\n");
    printf("3 - Remover Episódio\n");
    printf("4 - Mostrar Episódio\n");
    printf("5 - Tocar Episódio\n");
    printf("6 - Sair\n");
    printf("\nDigite uma opção: ");
		scanf("%d", &opcao);
    
    if(opcao == 1 ){
      adicionarPodcast(playlist);
    }
    if(opcao == 2 ){
      adicionarEpisodio(playlist);
    }
    if(opcao == 3 ){
      removerEpisodio(playlist);
    }
    if(opcao == 4 ){
      mostarEpisodio(playlist);
    }
    if(opcao == 5 ){
      tocarEpisodio(episodeoAtual, playlist);
    }
	}
}


playlist criarPlaylist() {
	playlist lista = (playlist)malloc(sizeof(playlist));
	podCastList* listaSec = (podCastList*)malloc(sizeof(podCastList));
	listaSec->inicio = NULL;
	listaSec->ultimo = NULL;
	lista->podCastList = listaSec;
	lista->tamanho = 0;
	return lista;
}


void mostarEpisodio(playlist playlist) {
	
	podCastList* podCastListSec = playlist->podCastList;

	
	if (podCastListSec->inicio == NULL) {
		printf("Não há nad ana playlist! \n");
		return;
	}

	
	if (podCastListSec->inicio == podCastListSec->ultimo) {
		podcast podCastSec = podCastListSec->inicio;
		ListaEp* episodioListaSec = podCastSec->epsList;

		if (episodioListaSec->inicio == NULL) {
			printf("Podcast: %s não existe \n", podCastSec->nome);
			return;
		}

		ep episodioSec = episodioListaSec->inicio;

		printf("Podcast: %s \n", podCastSec->nome);

		
		if (episodioSec == episodioListaSec->ultimo) {
			printf("Ep. %d | ", episodioSec->id);
			episodioSec = episodioListaSec->ultimo;
		}

		for (; episodioSec != NULL; episodioSec = episodioSec->prox) {
			printf("Ep. %d | ", episodioSec->id);
		}
		printf("\n");
		return;
	}

	for (podcast podcastSec = podCastListSec->inicio; podcastSec != NULL; podcastSec = podcastSec->prox) {
		ListaEp* episodioListaSec = podcastSec->epsList;
		
		if (episodioListaSec->inicio == NULL) {
			printf("Podcast: %s não existe! \n", podcastSec->nome);
		}
		else {
			ep episodioSec = episodioListaSec->inicio;

			printf("Podcast: %s \n", podcastSec->nome);

			if (episodioSec == episodioListaSec->ultimo) {
				printf("Ep. %d | ", episodioSec->id);
				episodioSec = episodioListaSec->ultimo;
			}

			for (; episodioSec != NULL; episodioSec = episodioSec->prox) {
				printf("Ep. %d | ", episodioSec->id);
			}
			printf("\n");
		}
	}
}


ep criarEp() {
	ep podcastNovo = (ep)malloc(sizeof(ep));

	printf("Insira o numero do novo episódio: ");
	scanf("%d", &podcastNovo->id);

	podcastNovo->prev = NULL;
	podcastNovo->prox = NULL;
	return podcastNovo;
}

void adicionarEpisodio(playlist playlist) {
	ep podcastNovo = criarEp();
	
	int idPodcast;
	printf("Insira o id do podcast para adicionar: ");
	scanf("%d", &idPodcast);

	podcast podcastSec = NULL;
	podCastList* podcastSecList = playlist->podCastList;
	for (podcast podcast = podcastSecList->inicio; podcast != NULL; podcast = podcast->prox) {
		if (podcast->id == idPodcast) {
			podcastSec = podcast;
			break;
		}
	}

	if (podcastSec == NULL) {
		printf("Não foi possivél achar o Podcast de id %d \n", idPodcast);
		return;
	}

  ListaEp* episodioListaSec = podcastSec->epsList;
	if (episodioListaSec->inicio != NULL) {
		ep aux = episodioListaSec->inicio;
		aux->prev = podcastNovo;
		podcastNovo->prox = aux;
	}
	if (episodioListaSec->ultimo == NULL) {
		episodioListaSec->ultimo = podcastNovo;
	}
	episodioListaSec->inicio = podcastNovo;
}


void adicionarPodcast(playlist playlist) {
	podcast podcastNovo = (podcast)malloc(sizeof(Podcast));
	podcastNovo->prox = NULL;
	podcastNovo->prev = NULL;
	
	podcastNovo->id = playlist->tamanho;
	playlist->tamanho += 1;

	printf("Insira o nome do Podcast: ");
	scanf("%s", &podcastNovo->nome, 10);

	ListaEp* episodeos = (ListaEp*)malloc(sizeof(ListaEp));
	episodeos->inicio = NULL;
	episodeos->ultimo = NULL;

	podcastNovo->epsList = episodeos;

	podCastList* podCastList = playlist->podCastList;

	printf("%s Foi adicionado com Id [%d]. \n", podcastNovo->nome, podcastNovo->id);
	if (podCastList->inicio == NULL) {
		podCastList->inicio = podcastNovo;
		podCastList->ultimo = podcastNovo;		
		return;
	}

	podcast inicio = podCastList->inicio;
	inicio->prev = podcastNovo;
	podcastNovo->prox = inicio;
	podCastList->inicio = podcastNovo;
}


void removerEpisodio(playlist playlist) {
	int idPocast;
	int numEp;

	printf("Insira o Id do PodCast: ");
	scanf("%d", &idPocast);
	
	printf("Insira o numero do ep a ser removido: ");
	scanf("%d", &numEp);


	podCastList* listaSec = playlist->podCastList;

	if (playlist->tamanho <= 0) {
		printf("A playlist está vazia.\n");
		return;
	}

	for (podcast podcast = listaSec->inicio; podcast != NULL; podcast = podcast->prox) {
		if (podcast->id == idPocast) {
			ListaEp* episodioListaSec = podcast->epsList;

			if (episodioListaSec->inicio == NULL) {
				printf("A lista de episódios está vazia.\n");
				return;
			}

			for (ep episodio = episodioListaSec->inicio; episodio != NULL; episodio = episodio->prox) {
				if (episodio->id == numEp) {
					printf("Episódio %d do Podcast %s removido!.\n", numEp, podcast->nome);
					if (episodio->prox == NULL && episodio->prev == NULL) {
						episodioListaSec->inicio = NULL;
						episodioListaSec->ultimo = NULL;
						break;
					}

					if (episodio == episodioListaSec->ultimo) {
						ep prevSec = episodio->prev;
						prevSec->prox = NULL;
						episodioListaSec->ultimo = prevSec;
						break;
					}

					ep prevSec = episodio->prev;
					ep proxSec = episodio->prox;

					prevSec->prox = proxSec;
					proxSec->prev = prevSec;
					break;
				}
			}
			break;
		}
	}
}


void tocarEpisodio(EpisoidoAtual episodeoAtual, playlist playlist) {
	podCastList* podcasts = playlist->podCastList;
	if (episodeoAtual->episodio == NULL) {
		episodeoAtual->podcast = podcasts->inicio;

		Podcast* podcastSec = podcasts->inicio;
		ListaEp* episodioListaSec = podcastSec->epsList;
		Ep* episodioSec = episodioListaSec->inicio;
		episodeoAtual->episodio = episodioSec;
	}

	if (episodeoAtual->episodio != NULL) {
		Ep* episodioSec = episodeoAtual->episodio;
		Podcast* podcastSec = episodeoAtual->podcast;
		printf("Tocando o ep. %d do Podcast: %s\n", episodioSec->id, podcastSec->nome);
	}
}

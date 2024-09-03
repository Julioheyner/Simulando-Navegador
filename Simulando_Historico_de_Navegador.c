#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<locale.h>
/*Estrutura para representar um site*/
typedef struct {
    char pagina[50];
    char dataHora[50];
} Site;
/*Estrutura para representar um nó da pilha*/
typedef struct No {
    Site site;
    struct No* proximo;
} No;
/*Função para criar um novo nó*/
No* criarNo(char pagina[], char dataHora[]) {
    No* novoNo = (No*)malloc(sizeof(No));
    strcpy(novoNo->site.pagina, pagina);
    strcpy(novoNo->site.dataHora, dataHora);
    novoNo->proximo = NULL;
    return novoNo;
}
/*Função para empilhar um site*/
void empilhar(No** topo, char pagina[], char dataHora[]) {
    No* novoNo = criarNo(pagina, dataHora);
    novoNo->proximo = *topo;
    *topo = novoNo;
}
/*Função para desempilhar um site*/
Site desempilhar(No** topo) {
    if (*topo == NULL) {
        Site siteVazio = {"", ""};
        return siteVazio;
    }

    No* aux = *topo;
    *topo = (*topo)->proximo;
    Site siteDesempilhado = aux->site;
    free(aux);
    return siteDesempilhado;
}
/*Função para exibir o histórico de navegação*/
void exibirHistorico(No* topo) {
    No* atual = topo;
    while (atual != NULL) {
        printf("Data: %s  %s\n", atual->site.dataHora, atual->site.pagina);
        atual = atual->proximo;
    }
}
int main() {
	setlocale(LC_ALL, "Portuguese");
    No* novosSites = NULL;
    No* sitesDevolvidos = NULL;

    char entrada[50];
    char dataHora[50];
    time_t t;
    struct tm* horaLocal;
    int opcao;
    int historicoVazio = 1;/*Variável para controlar se o histórico está vazio*/

    do {
        printf("\n\t\033[1;32m==== NAVEGADOR =====\033[0m\n\n");
        printf("1. Adicionar site\n");
        printf("2. Exibir histórico de navegação\n");
        printf("3. Retornar ao site anterior\n");
        printf("0. Sair\n");
        printf("\n\033[0;33m*Opção:\033[0m ");
        scanf("%d", &opcao);
        printf("----------------------------------------");
        fflush(stdin);

        switch (opcao) {
            case 1:
                printf("\n\n\033[1;34mSite a pesquisar: \033[0m");
                scanf("%s", entrada);
                time(&t);
                horaLocal = localtime(&t);
                strftime(dataHora, sizeof(dataHora), "%d-%m-%y %H:%M:%S", horaLocal);
                empilhar(&novosSites, entrada, dataHora);
                historicoVazio = 0;/*Atualiza para indicar que há pelo menos um item no histórico*/
                break;
            case 2:
                printf("\nHistórico de Pesquisa:\n");
                if (historicoVazio && novosSites == NULL) {
                    printf("*** Sem registro de visitas ***\n");
                    printf("----------------------------------------");
                } else {
                    exibirHistorico(novosSites);
                    printf("----------------------------------------");
                }
                break;
            case 3:
                if (novosSites != NULL) {
                    Site siteDevolvido = desempilhar(&novosSites);
                    empilhar(&sitesDevolvidos, siteDevolvido.pagina, siteDevolvido.dataHora);
                    printf("\n\nRetornando ao site anterior:\n\n");
                    if (novosSites != NULL) {
                        printf("Data: %s  %s\n",
                               novosSites->site.dataHora, novosSites->site.pagina);
                               printf("----------------------------------------");
                    } else {
                        printf("\nNenhum site restante.\n");
                        historicoVazio = 1;/*Atualiza para indicar que o histórico está vazio novamente*/
                    }
                } else {
                    printf("\nNenhum site para retornar!\n");
                    printf("----------------------------------------");
                }
                break;
            case 0:
            printf("\nSaindo do navegador!\n");
            printf("----------------------------------------\n");
                break;
            default:
                printf("\nEscolha inválida...Tente novamente!\n");
                printf("----------------------------------------");
        }
    } while (opcao != 0);
/*Liberando a memória das pilhas*/
    while (novosSites != NULL) {
        desempilhar(&novosSites);
    }
    while (sitesDevolvidos != NULL) {
        desempilhar(&sitesDevolvidos);
    }
    return 0;
}
/*Developed by Julio Gonzales*/
    
    
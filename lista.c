#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

struct lista *lista_cria()
{
    struct lista *l;

    l = malloc(sizeof(struct lista));
    
    if (l == NULL)
        return NULL;

    l->ini = NULL;
    l->tamanho = 0;

    return l;
}

void lista_destroi(struct lista **lista)
{
    if (lista == NULL || *lista == NULL) return;

    struct nodo* atual = (*lista)->ini;
    struct nodo* temp;

    while (atual != NULL) 
    {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }

    free(*lista);
    *lista = NULL;
}

int lista_insere_inicio(struct lista *lista, int chave)
{
    struct nodo *novo;

    novo = malloc(sizeof(struct nodo));
    if (novo == NULL) return 0;

    novo->chave = chave;
    novo->prox = lista->ini;

    lista->ini = novo;
    (lista->tamanho)++;
    return 1;
}

int lista_insere_fim(struct lista *lista, int chave)
{
    struct nodo* novo;

    novo = malloc(sizeof(struct nodo));
    if (novo == NULL) return 0;

    novo->chave = chave;
    novo->prox = NULL;

    if (lista->ini == NULL) 
    {
        lista->ini = novo;
    } 
    else 
    {
        struct nodo* atual = lista->ini;
        while (atual->prox != NULL) 
        {
            atual = atual->prox;
        }
        atual->prox = novo;
    }

    (lista->tamanho)++;
    return 1;
}

int lista_insere_ordenado(struct lista *lista, int chave)
{
    struct nodo* novo;
    
    novo = malloc(sizeof(struct nodo));
    if (novo == NULL) return 0;

    novo->chave = chave;

    if (lista->ini == NULL || lista->ini->chave >= chave)
    {
        novo->prox = lista->ini;
        lista->ini = novo;
    }
    else 
    {
        struct nodo* atual = lista->ini;
        while (atual->prox != NULL && atual->prox->chave < chave) 
        {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }

    (lista->tamanho)++;
    return 1;
}

int lista_remove_inicio(struct lista *lista, int *chave)
{
    struct nodo *aux;
    if (lista_vazia(lista)) return 0;

    *chave = lista->ini->chave;
    aux = lista->ini;
    lista->ini = lista->ini->prox;
    (lista->tamanho)--;
    free(aux); 
    aux = NULL;
    return 1;
}

int lista_remove_fim(struct lista *lista, int *chave)
{
    struct nodo *aux1, *aux2;

    if (lista_vazia(lista)) return 0;

    if (lista_tamanho(lista) == 1)
    {
        *chave = lista->ini->chave;
        (lista->tamanho)--;
        free(lista->ini);
        lista->ini = NULL; 
        return 1;
    }
    
    aux1 = lista->ini;
    aux2 = aux1->prox;

    while (aux2->prox != NULL)
    {
        aux1 = aux2;
        aux2 = aux2->prox;
    }
    
    *chave = aux2->chave;
    free(aux2);
    aux1->prox = NULL;
    (lista->tamanho)--;
    return 1;
}

int lista_remove_ordenado(struct lista *lista, int chave)
{
    if (lista_vazia(lista)) return 0;

    struct nodo* atual = lista->ini;
    struct nodo* anterior = NULL;
    while (atual != NULL && atual->chave != chave)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return 0;

    if (anterior == NULL)
    {
        lista->ini = atual->prox;
    }
    else
    {
        anterior->prox = atual->prox;
    }

    free(atual);
    (lista->tamanho)--;
    return 1;
}

int lista_vazia(struct lista *lista)
{
    if (lista->tamanho == 0)
        return 1;
    return 0;
}

int lista_tamanho(struct lista *lista)
{
    return lista->tamanho;
}

int lista_pertence(struct lista *lista, int chave)
{
    struct nodo* atual = lista->ini;

    while (atual != NULL) 
    {
        if (atual->chave == chave) return 1;
        atual = atual->prox;
    }
    return 0;
}

void lista_inicia_iterador(struct lista *lista)
{
    lista->ptr = lista->ini;
}

int lista_incrementa_iterador(struct lista *lista, int *chave)
{
    if (lista->ptr == NULL) return 0;

    *chave = lista->ptr->chave;
    lista->ptr = lista->ptr->prox;
    return 1;
}

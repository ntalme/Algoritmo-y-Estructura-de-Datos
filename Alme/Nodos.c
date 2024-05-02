
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo
{
    int info;
    struct nodo *sig;
};
typedef struct nodo tNodo;
typedef tNodo *Lista;

Lista *creaNodo(int valor)
{
    Lista p;

    p = malloc(sizeof(tNodo));
    p->info = valor;
    p->sig = NULL;

    return p;
}

int localiza(Lista L, int dato)
{
    Lista aux;
    int i;

    aux =L;
    i=1;
    while(aux != NULL)
    {
        if (aux ->info == dato)
        {
            return i;
        }

        aux = aux->sig;
        i++;
    }
    return -1;
}

int main()
{
    Lista L;

    L = creaNodo(40);

    localiza(L, 40);

    printf("%i", L->info);

    return 0;
}

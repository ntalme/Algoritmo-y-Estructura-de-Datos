
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct nodo{
    char rut[11];
    char nombre [25];
    int entradas;
    struct nodo *sig;
};

typedef struct nodo tNodoPerso;
typedef tNodoPerso *LISTA;

LISTA creaNodo(char rut[11], char nombre[25], int entradas)
{
    LISTA p;

    if (p == NULL)
    {
        printf("no hay memoria, adios");
        exit(-1);
    }

    p= malloc(sizeof(tNodoPerso));
    strcpy(p->rut, rut);
    strcpy(p->nombre, nombre);
    p->entradas = entradas;
    p->sig = NULL;

    return p;
}
void imprimeLista (LISTA L)
{
    LISTA aux;

    aux = L;
    while(aux != NULL)
    {
        printf("%s %s %i \n", aux->rut, aux->nombre, aux->entradas);
        aux = aux->sig;
    }
}

LISTA insertaFinal (LISTA L, char rut[11], char nombre[25], int entradas )
{
    LISTA aux;
    if(L == NULL)
    {
        L =creaNodo(rut, nombre, entradas);
    }
    else
    {
        aux = L;
        while(aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = creaNodo(rut, nombre, entradas);
        aux = NULL;
    }
    return L;
}

void EntradasporRut(LISTA L, char rut[11])
{
    LISTA aux;
    aux = L;

    int entradas = 0;

    while (aux != NULL)
    {
        if (aux->rut == rut)
        {
            entradas += aux->entradas;
        }
        aux = aux->sig;
    }

    printf("El rut %s tiene %d entradas\n", rut, entradas);
}

//void penalizaciones(LISTA L, int entradas)
//{
//    LISTA aux;
//    aux = L;
//
//    if (entradas 2)
//    {
//         printf("El rut %s tiene  entradas\n", rut, entradas);
//    }
//}


void procesoPrincipal()
{

    LISTA L;

    L = NULL;
    L = insertaFinal(L, "21227314-7", "Almendra Manriquez", 2);
    L = insertaFinal(L, "21227314-7", "alme", 2);
    L = insertaFinal(L, "20586214-5", "Bryan Salinas", 4);
    L = insertaFinal(L, "15724068-4", "Catherine Torres", 1);
    L = insertaFinal(L, "20586214-5", "Bryan Salinas", 3);
    imprimeLista(L);

    EntradasporRut(L, "21227314-7");
    EntradasporRut(L, "20586214-5");
    EntradasporRut(L, "15724068-4");
}

int main()
{
    procesoPrincipal();
    return 0;
}

Lista PersonasInscritas(Lista L)
{
   Lista aux;
   Lista nuevaLista = NULL;

   aux = L;

   while(aux != NULL)
   {
        if(aux->entradas < 5)
        {
            nuevaLista = insertaFinal(nuevaLista, aux->rut, aux->nombre, aux->entradas);
        }
    aux = aux->sig;
   }
   return nuevaLista;
}

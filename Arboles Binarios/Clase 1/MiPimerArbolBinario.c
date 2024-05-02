#include <stdio.h>
#include <stdlib.h>

struct nodo{
    int info;
    struct nodo *izq;
    struct nodo *der;
};
typedef struct nodo tNodo;
typedef tNodo * AB;
int contador=0;

AB creaNodo(int a)
{
    AB p;

    p = malloc(sizeof(tNodo));

    if (p == NULL)
    {
        printf("Sin memoria");
        exit(-1);
    }
    p->info = a;
    p->izq = NULL;
    p->der = NULL;
    return p;
}
void ImprimeElementosNivel(AB A, int nivel)
{
    if (A == NULL)
        printf(" - ");
    else
    {
        if (nivel == 0)
            printf(" %i ", A->info);
        else
        {
            ImprimeElementosNivel(A->izq, nivel-1);
            printf(" | ");
            ImprimeElementosNivel(A->der, nivel-1);
        }
    }
 }
int Maximo(int a, int b)
{
    if (a>b)
        return a;
    else
        return b;
}
int Altura(AB A)
{
    if (A == NULL)
        return 0;
    else
        return Maximo(Altura(A->izq), Altura(A->der)) + 1;
}
void ImprimeArbol(AB A)
{
    int h, i;

    h = Altura(A);

    printf("\n");
    for(i=0;i<h;i++)
    {
        ImprimeElementosNivel(A,i);
        printf("\n");
    }
}
int Peso(AB a)
{
    int x,i,d;
    contador++;

    if (a == NULL)
    {
        return 0;
    }
    else
    {
        i = Peso(a->izq);
        d = Peso(a->der);
        x = 1 + i + d;
        return x;
    }
}
int main()
{
    AB arbol;
    int x;
    arbol = NULL;

    arbol = creaNodo(6);
    arbol->izq = creaNodo(2);
    arbol->der = creaNodo(3);
    arbol->izq->izq = creaNodo(0);
    arbol->der->der = creaNodo(1);
    arbol->izq->der = creaNodo(7);
    arbol->der->izq = creaNodo(4);

    ImprimeArbol(arbol);
    x = Peso(arbol);
    printf("\nNumero de nodos del AB: %i\n", x);
    printf("Numero de ejecuciones: %i\n", contador);

    return 0;
}




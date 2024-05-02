#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
    char rut[12];
    char nombre[30];
    int entradas;
    struct nodo *izq;
    struct nodo *der;
};
typedef struct nodo tNodo;
typedef tNodo *ABO;

//----- FUNCIONES PARA IMPRIMIR EL ÁRBOL BINARIO ORDENADO ----//
void ImprimeElementosNivel(ABO A, int nivel)
{
    if (A == NULL)
        printf(" - ");
    else
    {
        if (nivel == 0)
            printf(" %s ", A->rut);
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
int Altura(ABO A)
{
    if (A == NULL)
        return 0;
    else
        return Maximo(Altura(A->izq), Altura(A->der)) + 1;
}
void ImprimeArbol(ABO A)
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
//---------------- FIN IMPRIMIR --------------------//
ABO creaNodo(char rut[11], char nombre[30], int entradas)
{
   ABO aux;

   aux = malloc(sizeof(tNodo));
   if (aux != NULL)
   {
      strcpy(aux->rut, rut);
      strcpy(aux->nombre, nombre);
      aux->entradas = entradas;
      aux->izq = NULL;
      aux->der = NULL;
   }
   else
   {
       printf("\nNo hay memoria suficiente.");
       exit(1);
   }
   return aux;
}

ABO Insertar(ABO T, char rut[12], char nombre[30], int entradas)
{
    if (T == NULL)
    {
        T = creaNodo(rut, nombre, entradas);
    }
    else
    {
        if (strcmp(rut, T->rut) == -1)///Si el rut es menor que T->rut
        {
            T->izq = Insertar(T->izq, rut, nombre, entradas);
        }
        else
        {
            T->der = Insertar(T->der, rut, nombre, entradas);
        }
    }
    return T;
}

int main()
{
    ABO arbol;
    int i, numNodos, entradas;
    char rut[12], nombre[30];

    numNodos = 3; ///Revisa con diferentes valores, para que valides el árbol que se construye: Debe estar ordenado!

    arbol = NULL;
    for(i=0; i<numNodos; i++)
    {
        printf("Ingresa un rut: ");
        fgets(rut, 12, stdin);
        strtok(rut, "\n");

        printf("Ingresa un nombre: ");
        fgets(nombre, 30, stdin);
        strtok(nombre, "\n");

        printf("Ingresa la cantidad de entradas: ");
        scanf("%i", &entradas);
        fflush(stdin);

        arbol = Insertar(arbol, rut, nombre, entradas );
    }
    ImprimeArbol(arbol);

    printf("\n\n");
    return 0;
}

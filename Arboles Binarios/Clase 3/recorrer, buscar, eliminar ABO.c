#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct nodo{
    int info;
    struct nodo *izq;
    struct nodo *der;
};
typedef struct nodo tNodo;
typedef tNodo *ABO;

int cont;

//----- FUNCIONES PARA IMPRIMIR EL ÁRBOL BINARIO ORDENADO ----//
void ImprimeElementosNivel(ABO A, int nivel)
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
ABO creaNodo(int valor)
{
   ABO aux;

   aux = malloc(sizeof(tNodo));
   if (aux != NULL)
   {
      aux->info = valor;
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
ABO Insertar(ABO A, int dato)
{
    if (A == NULL)
    {
        A = creaNodo(dato);
    }
    else
    {
        if (dato < A->info)
        {
            A->izq = Insertar(A->izq, dato);
        }
        else
        {
            A->der = Insertar(A->der, dato);
        }
    }
    return A;
}
int Menor(ABO A)
{
    if (A->izq == NULL)
        return A->info;
    else
        return Menor(A->izq);
}
ABO Eliminar(ABO A, int dato)
{
    ABO p;
    int menor;

    if (A == NULL)
    {
        return NULL;
    }
    if (A->info == dato) // El valor a eliminar está en la raíz
    {
        if (A->izq == NULL && A->der == NULL)   //El árbol tiene solo un nodo.
        {
            free(A);
            return NULL;
        }
        if (A->izq == NULL) //El árbol solo tiene hijo derecho.
        {
            p = A->der;
            A->der = NULL;
            free(A);
            return p;
        }
        if (A->der == NULL) //El árbol solo tiene hijo izquierdo.
        {
            p = A->izq;
            A->izq = NULL;
            free(A);
            return p;
        }
        menor = Menor(A->der);
        A->info = menor;
        A->der = Eliminar(A->der, menor);
    }
    else    // Llama recursivamente para buscar el dato a eliminar
    {
        if (dato < A->info)
            A->izq = Eliminar(A->izq, dato);
        else
            A->der = Eliminar(A->der, dato);

    }
    return A;
}

void preOrden(ABO A)
{
    if (A != NULL)
    {
        printf("%i ", A->info);
        preOrden(A->izq);
        preOrden(A->der);
    }
}

void inOrden(ABO A)
{
    if (A != NULL)
    {
        inOrden(A->izq);
        printf("%i ", A->info);
        inOrden(A->der);
    }
}

void postOrden(ABO A)
{
    if (A != NULL)
    {
        postOrden(A->izq);
        postOrden(A->der);
        printf("%i ", A->info);
    }
}

bool buscaElemento(ABO A, int dato)
{
    cont++;
    if (A == NULL)
        return false;
    if (dato == A->info)
        return true;
    if (dato < A->info)
        return buscaElemento(A->izq, dato);
    else
        return buscaElemento(A->der, dato);
}

int niveles(ABO A, int X)
{
    if (A == NULL)
    {
        return 0;
    }
    if (A->info == X)
    {
       return 1
    }
    return niveles(A->izq, X) + niveles(A->der, X);
}

int main()
{
    ABO arbol;
    int dato;

    ///Primer ABO:
//    arbol = NULL;
//    arbol = Insertar(arbol, 205);
//    arbol = Insertar(arbol, 120);
//    arbol = Insertar(arbol, 320);
//    arbol = Insertar(arbol, 23);
//    arbol = Insertar(arbol, 180);
//    arbol = Insertar(arbol, 210);
//    arbol = Insertar(arbol, 360);
//    arbol = Insertar(arbol, 150);
//    arbol = Insertar(arbol, 250);
//    arbol = Insertar(arbol, 370);
//    arbol = Insertar(arbol, 130);
//    arbol = Insertar(arbol, 220);
//    ImprimeArbol(arbol);

    ///Segundo ABO:
    arbol = NULL;
    arbol = Insertar(arbol, 60);
    arbol = Insertar(arbol, 41);
    arbol = Insertar(arbol, 74);
    arbol = Insertar(arbol, 16);
    arbol = Insertar(arbol, 53);
    arbol = Insertar(arbol, 65);
    arbol = Insertar(arbol, 25);
    arbol = Insertar(arbol, 46);
    arbol = Insertar(arbol, 55);
    arbol = Insertar(arbol, 63);
    arbol = Insertar(arbol, 70);
    arbol = Insertar(arbol, 42);
    arbol = Insertar(arbol, 62);
    arbol = Insertar(arbol, 64);
    ImprimeArbol(arbol);

///Descomenta abajo para probar los recorridos:
    printf("\nPreorden: ");
    preOrden(arbol);
    printf("\nInorden: ");
    inOrden(arbol);
    printf("\nPostorden: ");
    postOrden(arbol);

    printf("\n\nEl nodo es de nivel: %i", niveles(arbol, 74));

///Descomenta abajo para probar la búsqueda:
//    printf("\nIngresa el valor deseas buscar: ");
//    scanf("%i", &dato);
//
//    cont = 0;
//    if (buscaElemento(arbol, dato))
//    {
//        printf("\nEl valor %i SI esta en el arbol.", dato);
//    }
//    else
//    {
//        printf("\nEl valor %i NO esta en el arbol.", dato);
//    }
//    printf("\nLa busqueda se ejecuto %i veces.", cont);
//
///Descomenta abajo para probar la eliminación:
//    printf("\nIngresa el valor deseas eliminar: ");
//    scanf("%i", &dato);
//
//    arbol = Eliminar(arbol, dato);
//    ImprimeArbol(arbol);
//
//    printf("\n\n");
//    return 0;
}


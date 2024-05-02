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
int cuentaMenoresQueValor(ABO A)
{
    if (A == NULL)
    {
        return 0;
    }
    else
    {
        if (A->info < 50)
        {
            return 1 + cuentaMenoresQueValor(A->izq) + cuentaMenoresQueValor(A->der);
        }
        else
        {
            return cuentaMenoresQueValor(A->izq);
        }
    }
}

void escribe(ABO A, FILE *archivo)
{
    if (A != NULL)
    {
        escribe(A->izq, archivo);
        if (A-> info < 50)
        {
            fprintf(archivo,"%i\n", A->info);
        }
        escribe(A->der, archivo);
    }
}

void escribeEnArchivo(ABO A)
{
    FILE * archivo;

    archivo = fopen("tareita.amt", "w");
    escribe(A, archivo);
    fclose(archivo);
}

int main()
{
    ABO arbol;
    int cont;

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

    cont = cuentaMenoresQueValor(arbol);

    printf("\nNumero de nodos menores que 50: %i\n", cont);

    escribeEnArchivo(arbol);

    printf("\n\n");
    return 0;
}


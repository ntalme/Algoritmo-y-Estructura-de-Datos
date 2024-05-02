#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo {
    char nombreColegio[60];
    char region[60];
    char comuna[15];
    float diferenciaPuntaje;
    int indicador;
    struct nodo *sig;
};
typedef struct nodo tNodo;
typedef tNodo *Lista;


Lista creaNodo(char nom[60], char reg[60], char com[15], float difPtje, int ind)
{
    Lista aux;

    aux = malloc(sizeof(tNodo));
    if (aux != NULL)
    {
        strcpy(aux->nombreColegio, nom);
        strcpy(aux->region, reg);
        strcpy(aux->comuna, com);
        aux->diferenciaPuntaje = difPtje;
        aux->indicador = ind;
        aux->sig = NULL;
    }
    else
    {
        system("cls");
        printf("\n\tERROR: No hay memoria suficiente para generar un nuevo Nodo.");
        printf("\n\tEste programa se cerrar%c.", 160);
        exit(1);
    }
    return aux;
}

void imprimeLista(Lista L)
{
    Lista aux;

    aux = L;
    while(aux != NULL)
    {
        printf("\n%s,%s,%s,%.1f,%i", aux->nombreColegio, aux->region, aux->comuna, aux->diferenciaPuntaje, aux->indicador);
        aux = aux->sig;
    }
    printf("NULL");

}
Lista insertaFinal(Lista L, char nom[60], char reg[60], char com[15], float difPtje, int ind)
{
    Lista pNodo, aux;

    pNodo = creaNodo(nom, reg, com, difPtje, ind);
    if (L == NULL)
        L = pNodo;
    else
    {
        aux = L;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = pNodo;
        aux = NULL;
    }
    pNodo = NULL;
    return L;
}

Lista procesaLinea(Lista L, char linea[200])
{
    char *trozo;
    char nombreColegio[60];
    char region[60];
    char comuna[15];
    float diferenciaPuntaje;
    int indicador;

    trozo = strtok(linea, ",");
    strcpy(nombreColegio, trozo);

    trozo = strtok(NULL, ",");
    strcpy(region, trozo);

    trozo = strtok(NULL, ",");
    strcpy(comuna, trozo);

    trozo = strtok(NULL, ",");
    diferenciaPuntaje = atof(trozo);

    trozo = strtok(NULL, ",");
    indicador = atoi(trozo);

    printf("\n%s,%s,%s,%.1f,%i", nombreColegio, region, comuna, diferenciaPuntaje, indicador);

    L = insertaFinal(L, nombreColegio, region, comuna, diferenciaPuntaje, indicador);
    return L;
}

void leeArchivo(char nombre[20])
{
    FILE *archivo;
    char linea[200];
    int largo;
    Lista L = NULL;

    archivo = fopen(nombre, "r");
    if(archivo == NULL)
    {
        printf("No se puede leer el archivo %s", nombre);
        exit(0);
    }
    while (feof(archivo) == 0)
    {
        linea[0] = '\0'; //Con esto se "limpia" la línea antes de leer la siguiente.
        fgets(linea, 200, archivo);
        largo = strlen(linea);
        if (linea[largo-1] == '\n')
            linea[largo-1] = '\0';
        if (strlen(linea) == 0) //Sí la linea solo tiene un "ENTER" que ya se sacó, se acabó el archivo
            break;              //... por lo que se termina el proceso.
        L = procesaLinea(L, linea);
    }
    fclose(archivo);
    imprimeLista(L);
}

int main()
{
    char nomArchivo[20];

    printf("Ingresa el nombre del archivo: ");
    gets(nomArchivo);
    leeArchivo(nomArchivo);

    return 0;
}

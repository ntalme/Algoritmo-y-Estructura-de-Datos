#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Entrada: Las estructuras no tienen Entradas.
Salida: Las estructuras no tienen Salidas.
Proceso: Es una estructura que tiene como par�metros: rut, que es de tipo char con un m�ximo de 11 caracteres; nombre, que es de tipo char con un m�ximo de 30 caracteres;
         entradas, de tipo entero. Adem�s, la variable estruct personas se le asgina el puntero izq y el puntero der, los cuales representan el hijo izquierdo y el
         hijo derecho de un nodo.
         Luego se le redefine un nombre a la estructura persona por tPersonas, luego se define a este como un puntero a una variable de tipo ABO.
*/
struct personas{
    char rut[11];
    char nombre[30];
    int entradas;
    struct personas *izq;
    struct personas *der;
};
typedef struct personas tPersonas;
typedef tPersonas *ABO;
/*
Entrada: Recibe los par�metros de la estructura personas.
Salida: Retorna un puntero de la estructura de tipo ABO.
Proceso: La funci�n inicia creando una variable puntero de tipo ABO llamada aux. Luego, con la funci�n malloc, se busca un espacio en la RAM para tPersonas.
         Luego, con un if se revisa si el puntero aux es distinto de NULL, de ser as� se igualara aux->rut con la variable rut, aux->nombre con la variable nombre,
         pero al ser estas variables de tipo char, se debe usar strcpy para poder copiar el contenido. Luego, se igualara aux->entradas con la variable entradas y, por
         �ltimo, se le asiganar� a aux->sig y aux->der el valor NULL.
         Por ultimo se retorna el puntero al nuevo nodo creado.
         En el caso de que aux == NULL, significa que no se pudo asignar memoria, por lo que la funci�n imprimir� el mensaje "No hay memoria suficiente" y
         terminar� el programa sin retornar el puntero aux.
*/
ABO creaNodo(char rut[11], char nombre[30], int entradas)
{
   ABO aux;

   aux = malloc(sizeof(tPersonas));
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
/*
Entrada: Recibe un puntero de la estructura de tipo ABO y todos los par�metros que posee la estructura personas.
Salida: Retorna un puntero de la estructura de tipo ABO.
Proceso: Primero, con un if se revisa si la variable de tipo ABO, llamada A, es igual a NULL. Esto significa que el �rbol est� vac�o, por lo que se crea un nuevo nodo llamando
         a la funci�n creaNodo la cual se le asigna a la variable A.
         En el caso de que el �rbol no est� vac�o, se comparar� con la funci�n strcmp si el rut ingresado es igual al rut del nodo actual (A->rut), de ser as� se suma la
         variable entradas a la variable entradas del nodo actual.
         En el caso de que los rut no sean iguales, se comparar� con la funci�n strcmp si el rut ingresado es menor al rut del nodo actual, de ser as� se hara una llamada recursiva
         de la funci�n Insertar pero pasando como par�metro al sub�rbol izquierdo, para que as� se cree el hijo izquierdo del nodo actual(A->izq).
         En el caso de que el rut ingresado sea mayor que el rut del nodo actual, se hara una llamada recursiva de la funci�n Insertar pero pasando como par�metro al sub�rbol
         derecho para que as� se cree el hijo derecho del nodo actual (A->der).
         Por ultimo se retorna la variable A de tipo ABO que se ha creado.

*/
ABO Insertar(ABO A, char rut[12], char nombre[30], int entradas)
{
    if (A == NULL)
    {
        A = creaNodo(rut, nombre, entradas);
    }
    else
    {
        if (strcmp(rut, A->rut) == 0)
        {
            A->entradas += entradas;
        }
        else
        {
            if (strcmp(rut, A->rut) == -1)
            {
                A->izq = Insertar(A->izq, rut, nombre, entradas);
            }
            else
            {
                A->der = Insertar(A->der, rut, nombre, entradas);
            }
        }
    }
    return A;
}
/*
Entrada: Recibe una variable de tipo char de 30 caracteres con el nombre del archivo que digite el usuario.
Salida: Retorna un puntero de la estructura de tipo ABO.
Proceso: Se define la variable de tipo ABO A como NULL lo que signifca que estamos definiendo el �rbol como vacio.
         Luego como la funci�n recibe el nombre del archivo que se quiere leer, se abre este mismo archivo en modo lectura. Si el archivo no se encuentra, se le avisa al usuario.
         Si el archivo es encontrado, se va leyendo linea por linea del archivo con un while y la funcion fgets. Luego, se separa cada dato con strtok cada vez que este
         encuentre una coma y se le asignar� una variable a cada uno, como en el archivo la cantidad de entradas estan en tipo de variable char, con la funci�n atoi para
         convertirla a una variable de tipo entero.
         Luego, se llama a la funci�n Insertar para guardar los datos obtenidos en la variable de tipo ABO A.
         Por ultimo, se cierra el archivo y se retorna la variable de tipo ABO A resultante.
*/
ABO LeerArchivo(char NombreArchivo [20])
{
    char lineas[100];
    char *rut;
    char *nombre;
    char *cadena;
    int entradas;
    FILE * archivo;
    ABO A;

    A = NULL;

    archivo = fopen(NombreArchivo, "r");

    if (archivo == NULL)
    {
        printf("No se encontro el archivo, adios");
        exit(-1);
    }
    else
    {
        while (fgets(lineas, 100, archivo) != 0)
        {
            strtok(lineas, "\n");
            rut = strtok(lineas, ","),
            nombre = strtok(NULL,",");
            cadena = strtok(NULL,",");
            entradas = atoi(cadena);

            A = Insertar(A, rut, nombre, entradas);
        }
        fclose(archivo);
        return A;
    }
}
/*
Entrada: Recibe un puntero de la estructura de tipo ABO.
Salida: Retorna un entero.
Proceso: Primero se revisa con un if si la variable de tipo ABO, llamada A, es igual a NULL, lo cual significa que el �rbol est� vac�o, por lo que se retorna 0.
         En el caso que el �rbol no est� vac�o, se revisa si la cantidad de entradas del nodo actual es mayor a 2, de ser as� se retornar� la suma de 1 (para contar el nodo
         actual), m�s lo que resulte de la llamada recursiva a la funci�n ContarMayoresQue2 recibiendo como par�metro el sub�rbol izquierdo, m�s lo que resulte de la llamada
         recursiva a la funci�n ContarMayoresQue2 recibiendo como par�metro el sub�rbol derecho. Al sumarle uno significa que el nodo actual que se esta revisando cumple con
         la condici�n de que su cantidad de entradas es mayor a 2, por lo que de esta forma se puede obtener la cantidad de personas que cumplen con la condici�n.
         En el caso de que la cantidad de entradas del nodo actual sea igual o menor a 2, solo se retorna lo que resulte de la llamada recursiva a la funci�n ContarMayoresQue2
         recibiendo como par�metro el sub�rbol izquierdo, m�s lo que resulte de la llamada recursiva a la funci�n ContarMayoresQue2 recibiendo como par�metro el sub�rbol derecho.
         Aqui no debe sumar 1 debido a que significa que el rut no cumple con la condici�n, por lo que no nos sirve contar a las personas que no poseen m�s de dos entradas.
         Luego de que termine la funci�n se retornara la cantidad de personas que poseen m�s de 2 entradas.
*/
int ContarMayoresQue2(ABO A)
{
    if (A == NULL)
    {
        return 0;
    }
    else
    {
        if (A->entradas > 2)
        {
            return 1 + ContarMayoresQue2(A->izq) + ContarMayoresQue2(A->der);
        }
        else
        {
            return ContarMayoresQue2(A->izq) + ContarMayoresQue2(A->der);
        }
    }
}
/*
Entrada: Recibe un puntero de la estructura de tipo ABO y un puntero a un archivo.
Salida: No retorna nada.
Proceso: Primero, se revisa con un if si la variable de tipo ABO, llamada A, es distinto de NULL, lo cual significa que el �rbol no est� vac�o, por lo que
         se hara una llamada recursiva a la funci�n Masde2Entradas entreg�ndole como par�metro el sub�rbol izquierdo y la variable archivo.
         Luego, se revisa si la cantidad de entradas del nodo actual que se esta revisando es mayor a 2, de ser as�, se imprimir� en el archivo
         con la funci�n fprintf el rut de la persona, su nombre y la cantidad de entradas que solicito.
         Luego, se hara una llamada recursiva a la funci�n Masde2Entradas entregandole como par�metro el sub�rbol derecho y la variable archivo.
         Todo esto se hace para poder recorrer de manera ordenada todo el �rbol A, para que as� los rut se puedan imprimir de menor a mayor.
*/
void Masde2Entradas(ABO A, FILE *archivo)
{
    if (A != NULL)
    {
        Masde2Entradas(A->izq, archivo);
        if (A->entradas > 2)
        {
            fprintf(archivo, "%s, %s: %i\n", A->rut, A->nombre, A->entradas);
        }
        Masde2Entradas(A->der, archivo);
    }
}
/*
Entrada: Recibe un puntero de la estructura de tipo ABO y una variable de tipo char con el nombre del archivo que digite el usuario.
Salida: No retorna nada.
Proceso: La funci�n comienza abriendo el archivo que d�gito el usuario en modo lectura, si el archivo no se encuntra se le avisa al usuario.
         Luego, se copia el nombre del archivo en la variable PersonasArchivo hasta el primer punto que se encuentre, y con la funci�n strcat se reemplaza todo
         lo que est� despu�s del punto por .sde. Despu�s de eso, se modifica la variable archivo para que se abra con el archivo creado llamado PersonasArchivo
         pero esta vez en modo escritura.
         Luego se llama a la funci�n Masde2Entradasa la cual se le debe pasar como par�metro la variable A de tipo ABO y la variable archivo la cual se defini� anteriormente,
         esta funci�n nos ayudar� para poder imprimir en el archivo la gente que solicito m�s de dos entradas, lo bueno es que esta funci�n ya implementa la funci�n fprintf
         que se utiliza para imprimir en un archivo, por lo que no causara ningun error llamar a esta func�on.
         Luego a la variable contador que anteriormente se defini� como una varible de tipo entero, se le iguala a la funci�n ContarMayoresQue2 pasandole como parametro
         la variable de tipo ABO A, recordemos que esta funci�n contiene a la cantidad de personas que pidieron m�s de dos entradas.
         Luego con fprintf imprimimos en el archivo la variable contador, indicando que es el total de personas con m�s de dos entradas.
         Luego con la funci�n fclose se cierra el archivo.
         Por ultimo con la funci�n printf se le avisa al usuario que el archivo fue creado, indicandole el nombre del archivo creado.
*/
void CreaArchivo(ABO A, char NombreArchivo [20])
{
    char lineas[100];
    char * PersonasArchivo;
    int contador;
    FILE * archivo;

    archivo = fopen(NombreArchivo, "r");

    if (archivo == NULL)
    {
        printf("No se encontro el archivo, adios");
        exit(-1);
    }

    PersonasArchivo = strtok(NombreArchivo, ".");
    strcat(PersonasArchivo, ".sde");

    archivo = fopen(PersonasArchivo, "w");

    Masde2Entradas(A, archivo);

    contador = ContarMayoresQue2(A);

    fprintf(archivo, "\nTotal: %i", contador);

    fclose(archivo);

    printf("\nEl archivo %s fue generado\n", PersonasArchivo);
}
/*
Entrada: No recibe nada como entrada.
Salida: La funci�n no retorna nada.
Proceso: En esta funci�n se crean 3 variables, una de tipo ABO llamada A, otra de tipo char de 20 caracteres llamado NombreArchivo y una de tipo entero llamado contador
         Luego la funci�n le pedir� a el usuario que escriba el nombre del archivo que quiere abrir y se guaradara en la variable NombreArchivo.
         Luego, se definir� a la variable de tipo ABO, llamada A, llamando a la funci�n LeerArchivo pasandole como par�meto el nombre del archivo que d�gito el usuario.
         Despues, a la variable de tipo entero contador se le iguala a la funci�n ContarMayoresQue2 pasandole como par�metro la variable de tipo ABO A, recordemos
         que esta funci�n contiene a la cantidad de personas que pidieron m�s de dos entradas.
         Luego con un if, verificaremos si la variable contador es igual a 0, lo que significa que no existen personas que hayan pedido m�s de dos entradas, por lo que con la
         funci�n fprint se le imprimira por pantalla al usuario que "Todos solicitaron la cantidad correcta de entradas" y no se creara un nuevo archivo.
         En el caso de que la variable contador sea distinto de 0, lo que significa que existen personas que hayan pedido m�s de dos entradas, se creara el archivo llamando
         a la funcion CreaArchivo pasandole como par�metros el ABO A, el cual fue definida anteriormente y el nombre del archivo que d�gito el usuario.
*/
void procesoPrincipal()
{
    ABO A;
    char NombreArchivo[20];
    int contador;

    printf("Ingrese nombre del archivo: ");
    fgets(NombreArchivo, 20, stdin);
    strtok(NombreArchivo, "\n");

    A = LeerArchivo(NombreArchivo);

    contador = ContarMayoresQue2(A);

    if (contador == 0)
    {
        printf("\nTodos solicitaron la cantidad correcta de entradas\n");
    }
    else
    {
        CreaArchivo(A, NombreArchivo);
    }
}
/*
Entrada: No recibe nada como entrada.
Salida: La funci�n retorna un entero.
Proceso: Esta funci�n es la funci�n principal del codigo, con esta podemos correr el codigo haciendo que llame la funci�n procesoPrincipal,
         luego que esta se ejecute se retornar� un 0 para indicar que el programa se ejecuto de manera correcta.
*/
int main ()
{
    procesoPrincipal();
    return 0;
}

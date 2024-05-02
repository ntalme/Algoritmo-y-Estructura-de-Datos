#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Entrada: Las estructuras no tienen Entradas.
Salida: Las estructuras no tienen Salidas.
Proceso: Es una estructura que tiene como parametros: rut que es de tipo char con un maximo de caracteres 11, nombre que es de tipo char con un maximo de caracteres 40,
         entradas de tipo entero y por ultimo la variable estruct personas se le asgina el puntero sig, esto es muy imporante ya que sin este campo no se podra crear
         una lista dinamica.
*/
struct personas{
    char rut[11];
    char nombre[40];
    int entradas;
    struct personas *sig;
};
typedef struct personas tPersonas;
typedef tPersonas *Lista;
/*
Entrada: Resive los parametros de la estructura personas.
Salida: Retorna un nodo de la Lista Dinamica.
Proceso: La funcion inicia creando una variable puntero de tipo Lista llamada p, luego de esto con la funcion malloc se busca un espacio
         en la RAM para tPersonas, y mientras el puntero p sea distinto de NULL se igualara p->rut con la variable rut, p->nombre con la variable nombre pero como estas
         son de tipo char se debe usar strcpy para que esto ocurra, luego se igualara p->entradas con la variable entradas y por ultimo se le asiganara p->sig el valor NULL,
         para luego retornar el puntero al nuevo nodo creado.
         En el caso de que p = NULL es decir no se pudo asignar memoria la funcion imprimira el mensaje "no hay memoria, adios! y terminara el programa sin retornar el puntero p.
*/
Lista creaNodo(char rut[11], char nombre[40], int entradas)
{
    Lista p;

    p = malloc(sizeof(tPersonas));

    if (p != NULL)
    {
        strcpy(p->rut, rut);
        strcpy(p->nombre, nombre);
        p->entradas = entradas;
        p->sig = NULL;
    }
    else
    {
        printf("no hay memoria, adios");
        exit(-1);
    }
    return p;
}
/*
Entrada: Resive un puntero de la estructura de tipo Lista y ademas resive todos los parametros que posee la estructura personas.
Salida: Retorna un puntero tipo Lista que apunta ha una lista dinamica.
Proceso: La funcion crea dos variables punteros de tipo lista.
         Luego la variable pPersonas se iguala llamando a la funcion creaNodo para poder ir creando nodos en la funcion.
         Despues se revisa si la lista L esta vacia, si es así esta se iguala a el nodo tPersonas.
         Pero en el caso de que la lista ya tiene datos con un while se revisara que la variable auxliar siguiente sea disntito a nulo
         (este ciclo no recorre toda la lista ya que queremos llegar al ultimo nodo para asi poder cambiarle su valor), cabe aclarar que
         el puentero aux es igual a la lista L, por lo que aux pasara a ser igual a aux->sig, pero en el caso de que aux->sig sea igual a
         NULL se igualara con el nodo pPersonas por lo que se ira creando una lista dinamica la cual los datos se van insertando desde el final del nodo.
         Por ultimo se retorna una lista dinamica.
*/
Lista insertaFinal(Lista L, char rut[11], char nombre[40], int entradas)
{
    Lista pPersonas;
    Lista aux;

    pPersonas = creaNodo(rut, nombre, entradas);

    if (L == NULL)
    {
        L = pPersonas;
    }
    else
    {
        aux = L;
        while (aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = pPersonas;
        aux = NULL;
    }
    return L;
}
/*
Entrada: Resive el nombre del archivo que queremos leer con un maximo de 20 caracteres.
Salida: Retorna un puntero tipo Lista que apunta ha una lista dinamica con todos los datos que leyo el archivo.
Proceso: La funcion resive el nombre del archivo que se quiere leer, luego se abre este mismo archivo en modo escritura, si el archivo no se encuntra le avisa al usuario.
         En cambio si el archivo se encuentra se va leyendo linea por linea del archivo con un while y la funcion fgets. Luego de esto se separa cada dato con strtok cada
         vez que este encuentre una coma los separa por variable, en el caso de la variable entrada se tiene que su valor en el archivo es de tipo char por lo que la debemos
         cambiar con la funcion atoi para que este sea un entero.Luego guardamos todos esto datos en una variable tipo de lista L con la funcion insertar al final. Por ultimo
         se cerrara el archivo con la funcion fclose y se retornara la lista L creada.
*/
Lista LeerArchivo(char NombreArchivo [20])
{
    char lineas[100];
    char *rut;
    char *nombre;
    char *cadena;
    int entradas;
    FILE * archivo;
    Lista L;

    L = NULL;

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

            L = insertaFinal(L, rut, nombre, entradas);
        }
        fclose(archivo);
        return L;
    }
}
/*
Entrada: Resive un puntero de la estructura de tipo Lista
Salida: Retorna un puntero tipo Lista que apunta ha una lista dinamica y contiene el total de entradas que existen por cada rut.
Proceso: La funcion crea 4 variables puntero de tipo lista y 2 variables de tipo entero, luego al puntero aux se le da el valor de la lista ingresada L y al puntero nuevalista se le asigna el valor NULL.
         Luego con un bucle while recorremos toda la lista L con el puntero aux, e igualaremos el puntero aux2 con nuevaLista, luego de esto se iniciara un bucle while donde se recorrera toda la lista nuevaista
         con ayuda del puntero aux2, dentro de este while se comparara el rut que este apuntando aux en la lista L y el rut que este apuntando aux2 en la lista nuevaLista, si es que ambos rut son iguales la variable contador
         se igualara a 1, lo que nos indicaria que el rut ya existe en nuestra lista Nuevalista (La primera vez que se ejecute este codigo aux2 sera igual a NULL debido a que la lista no tendra datos para comparar por lo que el primer while no se tendria en cuneta)
         En caso de que los rut comparados no sean iguales, el contador quedara con el valor 0 por lo que se definira la variable entera entradas como 0 y el puntero aux3 seria igual a la lista ingresada L.
         Luego de esto se ejecutara un ultimo bucle while donde se recorrera la lista L con el puntero aux3 y se compararán los rut a los que esten apuntendo aux3 y aux, si estos rut son iguales se sumara la cantidad de entradas del rut comparado, de no ser asi se parasa al siguiente nodo
         este proceso se realizara hasta que se recorra toda la lista con el aux3. Una vez que aux 3 sea igual a NULL coon la funcion inserta al final se agregaran los valores a la variable tipo lista llamada nuevalistapero en vez de poner aux->entradas se pondra la suma de entradas por rut que
         se hixo anteriormente en la variable entera entradas.
         Finalmennte el puntero aux se mueve al siguiente nodo de la lista y se iniciara todo el proceso nuevamente hasta que el puntero aux recorra cada nodo de la Lista L.
*/
Lista EntradasPorRut(Lista L)
{
    Lista aux;
    Lista aux2;
    Lista aux3;
    Lista nuevaLista;
    int contador;
    int entradas;

    aux = L;
    nuevaLista = NULL;

    while (aux != NULL)
    {
        contador = 0;
        aux2 = nuevaLista;

        while (aux2 != NULL)
        {
            if (strcmp(aux2->rut, aux->rut) == 0)
            {
                contador = 1;
            }
            aux2 = aux2->sig;
        }
        if (contador == 0)
        {
            entradas = 0;
            aux3 = L;

            while (aux3 != NULL)
            {
                if (strcmp(aux3->rut, aux->rut) == 0)
                {
                    entradas += aux3->entradas;
                }
                aux3 = aux3->sig;
            }
            nuevaLista = insertaFinal(nuevaLista, aux->rut, aux->nombre, entradas);
        }
        aux = aux->sig;
    }
    return nuevaLista;
}
/*
Entrada: Resive un puntero de la estructura de tipo Lista
Salida:  Retorna un puntero tipo Lista que apunta ha una lista dinamica pero con solo las personas que compraron igual o menos de 5 entradas.
Proceso: La funcion crea dos variables puntero de tipo Lista y una variables de tipo entero para saber las cantidad de entradas totales que se asignaron, despues igualamos al puntero personasIncritas como NULL, al puntero aux le damos el valor de la lista L y a la variable asignadas le damos el valor inicial 0.
         Luego con un while se va verificando si se cumple que la cantidad de entradas es menor a 50 y recorremos toda la lista mientras el puntero aux sea distinto de nulo.
         Luego con un if revisamos si la cantidad de entradas por rut es igual o menor a 50 si es asi, se cumplira que:
         Si la cantidad de entradas solicitadas es mayor o igual a 2 y la cantidad de entradas asignadas es igual a 49 solo se entregara una entrada ya que lo maximo
         de entradas es 50, luego si esto no se cumple se revisara si la cantidad de entradas es mayor a 5 si es asi al usuario solo se le entregaran 2 entradas y luego
         si tampoco se cumple esa condicion se le entragarn las entradas solcitadas por el usuario, luego el puntero aux pasara al siguiente nodo hasta que este
         sea igual a NULL y cuando esto ocurra la funcion terminara retornando una variable tipo lista que cumplan con las condiciones antes descritas.
*/
Lista PersonasInscritas(Lista L)
{
    Lista aux;
    Lista personasinscritas;
    int asignadas;

    personasinscritas = NULL;
    aux = L;
    asignadas = 0;

    while(aux != NULL && asignadas < 50)
    {
        if(aux->entradas <= 5)
        {
            if (aux->entradas >= 2 && asignadas == 49)
            {
                personasinscritas = insertaFinal(personasinscritas, aux->rut, aux->nombre, 1);
                asignadas += 1;
            }
            else if (aux->entradas > 2)
            {
                personasinscritas = insertaFinal(personasinscritas, aux->rut, aux->nombre, 2);
                asignadas += 2;
            }
            else
            {
                personasinscritas = insertaFinal(personasinscritas, aux->rut, aux->nombre, aux->entradas);
                asignadas += aux->entradas;
            }
        }
        aux = aux->sig;
    }
    return personasinscritas;
}
/*
Entrada: Resive dos variable de tipo Lista una con la lista original y otra con la lista creada en la funcion PersonasInscritas
Salida: Retorna un puntero tipo Lista que apunta ha una lista dinamica con las personas que quedaron afuera de la promocion pero que no estan penalizadas.
Proceso: La funcion crea tres variables puntero de tipo lista y una variable entera llamada asignadas, luego el puntero aux se iguala a la lista L y listaDeEspera toma el valor NULL.
         Luego con un bucle while mientras el puntero aux sea distinto de NULL se recorre toda la lista y se revisa si la cantidad de entradas sea igual a 1 o sea igual a 2
         se iniciara la variable asignadas con el valor 0 y el puntero aux2 se igualara a la lista ingresada PI la cual es la lista que se creo en la funcion PersonasInscritas.
         Luego mientras aux2 sea distinto de NULL se recorrera toda la lista y se comparara el rut al que este apuntando aux y el rut que este apuntando aux2, si ambos rut
         son iguales a la variable asignada se le sumara la cantidad de entradas a la que apunte aux2,si no, se pasara al siguiente nodo hasta que se recorra toda la lista PI.
         Luego de recorrer toda la lista PI se revisara si las entradas asignadas son menor a las entradas a las que este apuntando aux y que ala vez la cantidad de entradas pedidas
         a la que este apuntando aux se igual o menor a 2, si esto es asi a listaDeEspera llamara a la funcion insertaFinal para que asi se cree una nueva lista dinamica con solo
         las personas a las que no se le han dado todas sus entradas pedidas mientras sean 2 o menos. Por ultimo la funcion retorna la lista dinamica llamada listaDeEspera que contiene
         los datos anteriormete señalados.
*/
Lista ListaDeEspera(Lista L, Lista PI)
{
    Lista aux;
    Lista aux2;
    Lista listaDeEspera;
    int asignadas;

    aux = L;
    listaDeEspera = NULL;

    while (aux != NULL)
    {
        if (aux->entradas == 1 || aux->entradas == 2)
        {
            asignadas = 0;
            aux2 = PI;

            while (aux2 != NULL)
            {
                if (strcmp(aux->rut, aux2->rut) == 0)
                {
                    asignadas += aux2->entradas;
                }
                aux2 = aux2->sig;
            }
            if (asignadas < aux->entradas && aux->entradas <= 2)
            {
                listaDeEspera = insertaFinal(listaDeEspera, aux->rut, aux->nombre, 1);
            }
        }
        aux = aux->sig;
    }
    return listaDeEspera;
}
/*
Entrada: Resive dos variables, una de tipo Lista llamada L y una variable de tipo char con el nombre del archivo que ponga el usuario.
Salida: No retorna nada, pero crea un archivo de tipo asg solo con las personas que alcanzaron la promocion.
Proceso: La funcion abre el archivo en modo lectura con el nombre que se ingresa en la funcion LeerArchivo, luego el puntero PersonasAsignadas copia
         el nombre del archivo hasta el primer punto que se encuntre para luego cambiar lo que haya despues del punto por .asg. Luego de esto se vuelve
         a abrir el archivo en modo escritura pero con el nombre asignado en PersonaAsignadas. Despues se verifica que la variable auxiliar (que es igual
         a la lista ingresada) sea distinta de nulo, si es asi, se copiaran los datos en el archivo y se sumaran todas las entradas asignadas para luego
         pasar al siguiente nodo hasta que aux sea igual a nulo. Por ultimo se le edita el valor a la variable pendiente para que se le reste la cantidad de entradas
         asignadas, y asi con la funcion printf imprimimos en el archivo la cantidad de entradas asignadas y pendientes, para que luego de esto se cierre el archivo.
*/
void ArchivoAsignadas (Lista L, char NombreArchivo[20])
{
    char * PersonasAsignadas;
    FILE * archivo;
    int asignadas;
    int pendientes;
    Lista aux;

    aux = L;
    asignadas = 0;
    pendientes = 50;

    archivo = fopen(NombreArchivo, "r");

    PersonasAsignadas = strtok(NombreArchivo, ".");
    strcat(PersonasAsignadas, ".asg");

    archivo = fopen(PersonasAsignadas, "w");

    while (aux != NULL)
    {
        fprintf(archivo, "%s,%s,%i \n", aux->rut, aux->nombre, aux->entradas);
        asignadas += aux->entradas;
        aux = aux->sig;
    }
    pendientes -= asignadas;
    fprintf(archivo, "\nAsignadas: %i\n", asignadas);
    fprintf(archivo, "Pendientes: %i\n", pendientes);
    fclose(archivo);
}
/*
Entrada: Resive dos variables, una de tipo Lista llamada L y una variable de tipo char con el nombre del archivo que ponga el usuario.
Salida: No retorna nada, pero crea un archivo de tipo esp solo con las personas que no alcanzaron la promocion pero que no estan penalizadas.
Proceso: La funcion revisa si la lista ingresada es nula, de ser asi no crea el archivo de la lista de espera, en cambio si la lista no esta vacia se abre el archivo
         con el nombre que se ingreso en la funcion LeerArchivo en modo lectura, luego al archivo de las personas de espera se le copia el nombre del archivo hasta el
         primer punto que se encuntre para luego cambiar lo que haya despues del punto por .esp. Por ultimo se edita la variable archivo para que se abra con el nombre
         de PersonasEspera pero esta vez en modo escritura y mientras el auxiliar (que es igual a la lista ingresada) sea distinto de nulo se imprimiran los datos en
         el archivo. Luego de recorrer toda la lista hasta que aux se vuelva nulo se cierra el archivo.

*/
void ArchivoEspera (Lista L, char NombreArchivo[20])
{
    if (L == NULL)
    {
        return;
    }
    char * PersonasEspera;
    FILE * archivo;
    Lista aux;

    aux = L;

    archivo = fopen(NombreArchivo, "r");

    PersonasEspera = strtok(NombreArchivo, ".");
    strcat(PersonasEspera, ".esp");

    archivo = fopen(PersonasEspera, "w");

    while (aux != NULL)
    {
        fprintf(archivo, "%s,%s \n", aux->rut, aux->nombre);
        aux = aux->sig;
    }
    fclose(archivo);
}
/*
Entrada: No resive nada como entrada.
Salida: La funcion no retorna nada.
Proceso: En esta funcion se crean 3 variables punteros de tipo Lista y una variable de tipo char, luego esta funcion hara que el usuario digite el nombre del archivo que quiere abrir.
         Despues la variable puntero L se le da el valor de la funcion LeerArchivo que resive como entrada el NombreArchivo ingresado por el usuario, luego esta misma lista L se
         le cambiara el valor llamando a la funcion EntradasPorRut que resive como entrada la L, luego de esto al puntero L2 se le da el valor de la funcion PersonasIncritas y esta
         resivira la variable de tipo Lista L, por ultimo al puntero L3 se le asiganara la funcion ListadeEspera que resivira la variable de tipo Lista L y L2.
         Despues llamamos la funcion ArchivoAsignada a la cual se le entrega la variable de Lista L2 y el NombreArchivo ingresado para asi poder crear el archivo con las personas
         que alcanzaron la promocion y tambien llamamos a la funcion ArchivoEspera a la cual se le entrega la variable de Lista L3 y el NombreArchivo ingresado para asi poder
         crear el archivo con las personas que no alcanzaron la promocion pero que no estan penalizadas.
*/
void procesoPrincipal()
{
    Lista L;
    Lista L2;
    Lista L3;
    char NombreArchivo[20];

    printf("Ingrese nombre del archivo: ");
    fgets(NombreArchivo, 20, stdin);
    strtok(NombreArchivo, "\n");

    L = LeerArchivo(NombreArchivo);
    L = EntradasPorRut(L);
    L2 = PersonasInscritas(L);
    L3 = ListaDeEspera(L, L2);

    ArchivoAsignadas(L2, NombreArchivo);
    ArchivoEspera(L3, NombreArchivo);
    printf("\nSe han generado los archivos corresponientes\n");
}
/*
Entrada: No resive nada como entrada.
Salida: La funcion retorna un entero.
Proceso: Esta funcion es la funcion principal del codigo, con esta podemos correr el codigo haciendo que llame la funcion procesoPrincipal, luego que esta se ejecute la funcion
         retornara un 0 para indicar que el programa se ejecuto de manera correcta.
*/
int main()
{
    procesoPrincipal();
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NULL 0
#define TRUE_FILE 0
#define TRUE 1
#define FALSE 0 

void ERROR_HAPPED(int error);
char *EXTRACT_FILE_NAME(char *char1);
char *EXTRACT_EXTENSION_FILE(char *char1, int point);
char *JOIN_STRINGS(char *cadena1, char *cadena2);

int main(int argc, char *argv[])
{
    if (argc >= 1)
    {
        // el primero es el nombre del presente programa (run)
        // el siguiente debe ser el archivo a compilar y ejecutar
        // los consiguientes son los parametros del anterior
        FILE *file = fopen(argv[1], "r");

        // ayuda sobre la funcionalidad del programa run
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "help") == 0)
        {
            printf("Usar run en la terminal:\n");
            printf("\trun [archivo.c] [parametros]\n");
            printf("\trun [..\\archivo.c] [parametros]\n");
            printf("Donde parametros pueden ser n cantidad que adminta el ejecutable destino\n");
            printf("Ejemplo:\n");
            printf("\trun other.c hola mundo");
            printf("\trun other.cpp hola mundo");
            exit(0);
        }
        // existe el archivo
        else if (file != NULL) //other.cpp
        {
            char *fileName = EXTRACT_FILE_NAME(argv[1]);
            char *extension = EXTRACT_EXTENSION_FILE(argv[1], strlen(fileName)); 
            char *shell = (strcmp(".cpp", extension) != FALSE)? "g++ -o \0": "gcc -o \0";
            shell = JOIN_STRINGS(shell, fileName); 
            shell = JOIN_STRINGS(shell, " ");
            shell = JOIN_STRINGS(shell, argv[1]);
            // compilar archivo seleccionado
            if (system(shell) == TRUE_FILE)
            {
                fclose(file);
                char *aux = "";
                aux = JOIN_STRINGS(aux, "./");
                aux = JOIN_STRINGS(aux, fileName);
                aux = JOIN_STRINGS(aux, ".exe");
                // se agregan los parametros pasados por consola
                for (int j = 2; j < argc; ++j)
                {
                    aux = JOIN_STRINGS(aux, " ");
                    aux = JOIN_STRINGS(aux, argv[j]);
                }
                // correr archivo ejecutable
                if (system(aux) == TRUE_FILE)
                {
                    fileName = JOIN_STRINGS(fileName, ".exe");
                    // se elimina el archivo ejecutable
                    remove(fileName);
                    exit(0);
                }
                else
                {
                    fileName = JOIN_STRINGS(fileName, ".exe");
                    // eliminando el reciduo si se ejecuta con errores
                    // el compilador gcc igualmente crea el ejecutable
                    remove(fileName);
                    ERROR_HAPPED(3);
                    exit(1);
                }
            }
            else
            {
                fileName = JOIN_STRINGS(fileName, ".exe");
                // se elimina el archivo ejecutable
                remove(fileName);
                ERROR_HAPPED(2);
                exit(1);
            }
        }
        else
        {
            ERROR_HAPPED(1);
            exit(1);
        }
    }
    else
    {
        ERROR_HAPPED(0);
        exit(1);
    }
    return 0;
}

// imprime los errores segun corresponda
void ERROR_HAPPED(int error)
{
    switch (error)
    {
    case 0:
        printf("\nERROR 0\tNo se ha especificado un archivo");
        break;
    case 1:
        printf("\nERROR 1\tNo se ha encontrado el archivo en la direccion especificada");
        break;
    case 2:
        printf("\nERROR 2\tNo se ha podido ejecutar la compilacion");
        break;
    case 3:
        printf("\nERROR 3\tNo se puede correr el ejecutable");
        break;
    default: // nunca se ejecuta
        break;
    }
}

// se extrae el nombre de un archivo sin la extencion
char *EXTRACT_FILE_NAME(char *char1)
{
    char *aux = malloc(strlen(char1) - 2);
    int point = 0;
    while (char1[point] != '.')
    {
        aux[point] = char1[point];
        ++point;
    }
    return aux;
}

// se extrae la extención del archivo
char *EXTRACT_EXTENSION_FILE(char *char1, int point)
{
    char *second_aux = (char *) malloc(sizeof(char) * (strlen(char1) - point)); 
    int delimiter = FALSE;
    while (point < strlen(char1))
    {
        second_aux[point] = char1[point + 1]; 
        ++point;
    }
    return second_aux;
}

// une dos strings, una a continuacion de la otra
// en una tercera resultante
char *JOIN_STRINGS(char *char1, char *char2)
{
    char *aux = malloc(strlen(char1) + strlen(char2) + 2);
    sprintf(aux, "%c", 0);
    for (int i = 0; i < strlen(char1); i++)
    {
        sprintf(aux, "%s%c", aux, char1[i]);
    }
    for (int i = 0; i < strlen(char2); i++)
    {
        sprintf(aux, "%s%c", aux, char2[i]);
    }
    return aux;
}
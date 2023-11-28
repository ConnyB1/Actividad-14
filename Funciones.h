#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>


int valinum(int fi, int fu) 
{
    int num, vali;
    char cadena[100];

    do 
    {
        vali = 0;
        printf("\n\nIngrese un número entre %d y %d: ", fi, fu);

        if (fgets(cadena, sizeof(cadena), stdin) == NULL) 
        {
            printf("Error al leer la entrada.\n");
            return -1;
        }

        if (cadena[0] != '\0' && cadena[0] != '\n') 
        {
            for (int i = 0; cadena[i] != '\0' && cadena[i] != '\n'; i++) 
            {
                if (!isdigit(cadena[i])) 
                {
                    
                    vali = 1;
                }
            }
            if(vali == 1)
            {
                printf("Por favor, ingrese solo numeros.\n");
            }
            if (!vali) 
            {
                num = atoi(cadena);
                if (num < fi || num > fu) 
                {
                    printf("Asegúrate de que esté en este rango (%d-%d)\n", fi, fu);
                    vali = 1;
                }
            }
        } 
        else 
        {
            vali = 1; 
        }
    } while (vali == 1);
    return num;
}

int esCadenaValida(const char *cadena) 
{
    int i = 0;

    while (cadena[i] != '\0') 
    {
        char caracter = cadena[i];

        if (caracter >= 'A' && caracter <= 'Z' ) 
        {
            if (caracter >= '0' && caracter <= '9')
            {
                return 0; 
            }
        }
        i++;
    }

    return 1; 
}
void convertirAMayusculas(char *cadena) {
    int i = 0;
    while (cadena[i] != '\0') {
        if (islower(cadena[i])) {
            cadena[i] = toupper(cadena[i]);
        }
        i++;
    }
}

int leercadena(char *str, int fi) {
    int tecla, i = 0;
    int esp = 1;
    
    do {
        tecla = getch();
        tecla = toupper(tecla);

        if (tecla != 13) 
        { 
            if (i < fi - 1)
            {
                if (isalpha(tecla) || (tecla == 32 && esp == 0)) 
                {
                    printf("%c", tecla);
                    str[i++] = tecla;
                    esp = (tecla == 32) ? 1 : 0;
                }
                if (tecla == 164 || tecla == 165) 
                {
                    printf("%c", tecla);
                    str[i++] = tecla;
                    esp = 0;
                }
            }
        }
    } while (tecla != 13); 
    str[i] = '\0';
    return i;
}


int valinumran(int fi, int fu)  
{
    int num;  
    int valido = 0;
    do 
    {
        num = rand() % (fu - fi + 1) + fi;
        if (num >= fi && num <= fu) 
        {
            valido = 1;
        }
    } while (!valido);

    return num; 
}

int contarRegistrosEnArchivo(const char *nombreArchivo) 
{
    char nombreCompleto[100]; 
    sprintf(nombreCompleto, "C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 12\\%s.txt", nombreArchivo);
    FILE *archivo = fopen(nombreCompleto, "r");
    int contador = 0;
    char linea[1000];

    if (archivo == NULL) 
    {
        return -1;
    }

    if (fgets(linea, sizeof(linea), archivo) == NULL) 
    {
        fclose(archivo);
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL) 
    {
        if (strlen(linea) > 1) 
        {  
            contador++;
        }
    }

    fclose(archivo);
    return contador;
}


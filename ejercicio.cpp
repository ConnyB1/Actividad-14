//Cesar Alejandro Velazquez Mercado
//372329
//Me guarda unos registros y me da el archivo de texto y un archivo binario
//19/11/2023
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include "Funciones.h"

typedef int Tkey;
typedef struct _Wrkr
{
    int status;
    Tkey enrollment;
    char name[30];
    char Lastname1[50];
    char Lastname2[50];
    char sex[15];
    char jobposition[30];
    char state[30];
    int age;
    char* cellphone;
} TWrkr;

typedef struct _IndexEntry
{
    Tkey key;
    int index;
} TIndexEntry;

void cargarArchivoBinario(TIndexEntry indices[], int *n, int *maxSize);

void agregarAutomatico(TWrkr trabajadores[], TIndexEntry indices[], int *n, int maxSize);
char *nombres(char genero);
char *apellidos();
char *estado();
char *posicionTrabajo();
char *generarNumeroTelefono();
//Tkey generarNumeroTelefono();

void eliminarRegistro(TWrkr trabajadores[], TIndexEntry indices[], int *n, FILE *archivoBinario, int matricula);

void imprimirRegistro(TWrkr registro);
int buscarPorMatricula(TWrkr trabajadores[], TIndexEntry indices[], int n, int matricula, FILE *archivoBinario);
int buscarPorMatriculaSecuencial(TWrkr trabajadores[], TIndexEntry indices[], int n, int matricula, FILE *archivoBinario);
int buscarPorMatriculaBinaria(TIndexEntry indices[], int n, int matricula, FILE *archivoBinario);


void ordenarPorMatricula(TWrkr trabajadores[], int n);
int estaOrdenadoPorMatricula(TWrkr trabajadores[], int n);
void ordenarPorMatriculaSeleccion(TWrkr trabajadores[], int n);

void ordenarPorMatriculaBurbuja(TWrkr trabajadores[], int n);

void imprimirRegistrosArchivoOriginal(TWrkr trabajadores[], int n, FILE *archivoBinario);
void generarArchivoTexto(TWrkr trabajadores[], int n);

void empaquetarRegistros(TWrkr trabajadores[], int *n);
int contarRegistrosBinario(const char *nombreArchivo);


int buscarPorMatriculaSecuencial(TWrkr trabajadores[], TIndexEntry indices[], int n, int matricula, FILE *archivoBinario);
int determinarMetodoBusquedaOptimo(int n);
void imprimirRegistros(TWrkr trabajadores[], int n);

int main()
{
    srand(time(NULL));
    TWrkr trabajadores[5000];
    TIndexEntry indices[6250]; 
    int n = 0;                  
    int maxSize = 6250;  
    FILE *archivoBinario = fopen("C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 14\\datos.dat", "rb");
    
    int matricula; 
    cargarArchivoBinario(indices, &n, &maxSize);
    n = 0;
    int op;
    while (op != 0)
    {
    
    
        printf("\n\tMenu\n");
        printf("1.- AGREGAR\n");
        printf("2.- ELIMINAR\n");
        printf("3.- BUSCAR\n");
        printf("4.- ORDENAR\n");
        printf("5.- IMPRIMIR REGISTROS ARCHIVO ORIGINAL\n");
        printf("6.- IMPRIMIR REGISTROS ARCHIVO ORDENADO\n");
        printf("7.- GENERAR ARCHIVO TEXTO\n");
        printf("8.- EMPAQUETAR\n");
        printf("0.- SALIR\n");
        op = valinum(0, 8);

        if (op == 1)
        {
            agregarAutomatico(trabajadores, indices, &n, maxSize);
        }
        else
        {
            if(op == 2)
            {
                printf("Ingrese la matrícula a eliminar: ");
                matricula = valinum(300000, 399999); 
                eliminarRegistro(trabajadores, indices, &n, archivoBinario, matricula);
            }
            else
            {
                if (op == 3)
                {
                    printf("Ingrese la matricula que desea buscar: ");
                    matricula = valinum(300000, 399999);
                    buscarPorMatricula(trabajadores, indices, n, matricula, archivoBinario);
                    printf("\n\n");
                    system("pause");
                    system("cls");
                }
                else
                {
                    if (op == 4)
                    {
                        ordenarPorMatricula(trabajadores, n);
                    }
                    else
                    {
                        if (op == 5)
                        {
                            imprimirRegistrosArchivoOriginal(trabajadores, n, archivoBinario);
                        }
                        else
                        {
                            if (op == 6)
                            {
                                printf("Registros ordenados por matrícula:\n");
                                imprimirRegistros(trabajadores, n);
                            }
                            else
                            {
                                if (op == 7)
                                {
                                    generarArchivoTexto(trabajadores, n);
                                }
                                else
                                {
                                    if (op == 8)
                                    {
                                        empaquetarRegistros(trabajadores, &n);
                                    }
                                }
                                
                            }
                            
                        }
                        
                    }
                    
                }
                
            }
        }
    }
    printf("Adios");
    fclose(archivoBinario);
    return 0;
}

void agregarAutomatico(TWrkr trabajadores[], TIndexEntry indices[], int *n, int maxSize)
{
    if (*n + 100 > maxSize)
    {
        printf("No se pueden agregar 100 registros automáticamente, ya que superaría el límite de registros.\n");
        return;
    }

    int indice = *n;
    for (int i = 0; i < 100; i++)
    {
        if (indice >= maxSize)
        {
            printf("Se ha alcanzado el máximo de registros permitidos.\n");
            break;
        }
        trabajadores[indice].status = 1;
        trabajadores[indice].enrollment = valinumran(300000, 399999);
        trabajadores[indice].age = valinumran(18, 80);
        int matriculaRepetida = 0;
        for (int j = 0; j < *n; j++)
        {
            if (indices[j].key == trabajadores[indice].enrollment)
            {
                matriculaRepetida = 1;
                break;
            }
        }

        if (matriculaRepetida)
        {
            i--; 
        }
        
        char gen = (rand() % 2 == 0) ? 'M' : 'F';
        if (gen == 'F')
        {
            strcpy(trabajadores[indice].sex, "MUJER");
        }
        if (gen == 'M')
        {
            strcpy(trabajadores[indice].sex, "HOMBRE");
        }
        indices[*n].key = trabajadores[indice].enrollment;
        indices[*n].index = indice;

        char *nombreGenerado = nombres(gen);
        strcpy(trabajadores[indice].name, nombreGenerado);
        strcpy(trabajadores[indice].Lastname1, apellidos());
        strcpy(trabajadores[indice].Lastname2, apellidos());
        char *num = generarNumeroTelefono();
        trabajadores[indice].cellphone = num;

        

        char *posicionGenerada = posicionTrabajo();
        strcpy(trabajadores[indice].jobposition, posicionGenerada);

        const char estados[32][30] = {
            "AGUASCALIENTES", "BAJA CALIFORNIA", "BAJA CALIFORNIA SUR", "CAMPECHE", "COAHUILA",
            "COLIMA", "CHIAPAS", "CHIHUAHUA", "CIUDAD DE MEXICO", "DURANGO",
            "GUANAJUATO", "GUERRERO", "HIDALGO", "JALISCO", "MEXICO",
            "MICHOACAN", "MORELOS", "NAYARIT", "NUEVO LEON", "OAXACA",
            "PUEBLA", "QUERETARO", "QUINTANA ROO", "SAN LUIS POTOSI", "SINALOA",
            "SONORA", "TABASCO", "TAMAULIPAS", "TLAXCALA", "VERACRUZ", "YUCATAN", "ZACATECAS"
        };

        int estadoSeleccionado = rand() % 32;
        strcpy(trabajadores[indice].state, estados[estadoSeleccionado]);


        (*n)++;
        indice++;
    }
    *n = indice;
}

char *generarNumeroTelefono()
{
    int random1, random2;

    random1 = valinumran(100, 999);
    random2 = valinumran(1000, 9999);

    char *numeroTelefono = (char *)malloc(20);
    sprintf(numeroTelefono, "52 %d 555 %d", random1, random2);
    
    return numeroTelefono;
    free(numeroTelefono);
}








char *nombres(char genero)
{
    char nombresMas[][30] = {
        "Juan", "Carlos", "Luis", "Segismundo", "Diego",
        "Andres", "Soponcio", "Jose", "Felipe", "Rafael",
        "Obama", "Adolfo", "Fernando", "Cipriano", "Francisco",
        "David", "Emilio", "Miguel", "Alberto", "Roberto"
    };
    char nombresFem[][30] = {
        "Maria", "Ana", "Sofia", "Laura", "Isabel",
        "Digna", "Clara", "Adriana", "Valeria", "Daniela",
        "Carolina", "Paola", "Camila", "Natalia", "Andrea",
        "Lucia", "Verónica", "Ana", "Beatriz", "Marciana"
    };

    char *nombreElegido = (char *)malloc(31);
    if (genero == 'M')
    {
        int nom = rand() % 20;
        strcpy(nombreElegido, nombresMas[nom]);
    }
    else
    {
        int nom = rand() % 20;
        strcpy(nombreElegido, nombresFem[nom]);
    }

    return nombreElegido;

}

char *apellidos()
{
    char listaApellidos[][30] = {
        "Garcia", "Martinez", "Lopez", "Rodriguez", "Perez",
        "Fernandez", "Gonzalez", "Sánchez", "Ramirez", "Torres",
        "Jimenez", "Díaz", "Vargas", "Romero", "Suarez",
        "Mendoza", "Ortega", "Hernández", "Silva", "Rojas",
        "Cruz", "Morales", "Núñez", "Guerrero", "Paredes",
        "Salazar", "Estrvez", "Figueroa", "Valencia", "Molina"
    };

    char *apellidoElegido = (char *)malloc(31); 
    int indice = rand() % 30;
    strcpy(apellidoElegido, listaApellidos[indice]);

    return apellidoElegido;
}

char *posicionTrabajo()
{
    char listaPosiciones[][30] = {
        "Analista de Datos", "Desarrollador de Software", "Ingeniero de Sistemas",
        "Diseñador Gráfico", "Especialista en Redes", "Gerente de Proyectos",
        "Analista de Marketing", "Contador", "Economista",
        "Arquitecto", "Médico", "Enfermero",
        "Profesor", "Psicólogo", "Abogado",
        "Chef", "Recepcionista", "Asistente Administrativo",
        "Técnico de Soporte", "Asesor Financiero", "Investigador Científico",
        "Periodista", "Artesano", "Electricista",
        "Piloto", "Bombero", "Policía",
        "Actor", "Astronauta", "Traductor"
    };

    char *posicionElegida = (char *)malloc(31); 
    int indice = rand() % 30;
    strcpy(posicionElegida, listaPosiciones[indice]);

    return posicionElegida;
}

void eliminarRegistro(TWrkr trabajadores[], TIndexEntry indices[], int *n, FILE *archivoBinario, int matricula)
{

    int indice = -1;
    for (int i = 0; i < *n; i++)
    {
        if (indices[i].key == matricula)
        {
            indice = indices[i].index;
            break;
        }
    }

    if (indice != -1)
    {
        fseek(archivoBinario, indice * sizeof(TWrkr), SEEK_SET);
        TWrkr registro;
        fread(&registro, sizeof(TWrkr), 1, archivoBinario);
        printf("Registro encontrado:\n");
        printf("Matrícula: \t%d\n", registro.enrollment);
        printf("Nombre: \t%s\n", registro.name);
        printf("Apellido Paterno: \t%s\n", registro.Lastname1);
        printf("Apellido Materno: \t%s\n", registro.Lastname2);
        printf("Sexo: \t%s\n", registro.sex);
        printf("¿Desea eliminar este registro (s/n)? ");

        char respuesta = tolower(getch());

        if (respuesta == 's')
        {
            registro.status = 0;
            fseek(archivoBinario, indice * sizeof(TWrkr), SEEK_SET);
            fwrite(&registro, sizeof(TWrkr), 1, archivoBinario);

            printf("Registro con matrícula %d eliminado de forma lógica.\n", matricula);
        }
        else
        {
            printf("Registro no eliminado.\n");
        }
    }
    else
    {
        printf("No se encontró un registro con la matrícula %d.\n", matricula);
    }
}

int buscarPorMatricula(TWrkr trabajadores[], TIndexEntry indices[], int n, int matricula, FILE *archivoBinario)
{
    int metodoBusquedaOptimo = determinarMetodoBusquedaOptimo(n);

    if (metodoBusquedaOptimo == 1)
    {
        return buscarPorMatriculaSecuencial(trabajadores, indices, n, matricula, archivoBinario);
    }
    else
    {
        return buscarPorMatriculaBinaria(indices, n, matricula, archivoBinario);
    }
}

int determinarMetodoBusquedaOptimo(int n)
{
    if (n <= 50)
    {
        return 1; 
    }
    else
    {
        return 2; 
    }
}

int contarRegistrosBinario(const char *nombreArchivo) 
{
    FILE *archivoBinario = fopen(nombreArchivo, "rb");
    if (archivoBinario == NULL) {
        printf("Error al abrir el archivo binario.\n");
        return -1;
    }

    fseek(archivoBinario, 0, SEEK_END);
    int tamanoArchivo = ftell(archivoBinario);
    fclose(archivoBinario);

    return tamanoArchivo / sizeof(TWrkr);
}

void imprimirRegistro(TWrkr trabajadores)
{
    printf("%-12d %-30s %-50s %-50s %-15d %-30s %-30s %-15s %-12s\n", trabajadores.enrollment, trabajadores.name, trabajadores.Lastname1, trabajadores.Lastname2, trabajadores.age, trabajadores.sex, trabajadores.jobposition, trabajadores.state, trabajadores.cellphone);
}




int buscarPorMatriculaSecuencial(TWrkr trabajadores[], TIndexEntry indices[], int n, int matricula, FILE *archivoBinario)
{
    for (int i = 0; i < n; i++)
    {
        if (indices[i].key == matricula)
        {
            fseek(archivoBinario, indices[i].index * sizeof(TWrkr), SEEK_SET);
            TWrkr registro;
            fread(&registro, sizeof(TWrkr), 1, archivoBinario);

            imprimirRegistro(registro);

            return indices[i].index;
        }
    }

    printf("No se encontró un registro con la matrícula %d.\n", matricula);
    return -1;
}


int buscarPorMatriculaBinaria(TIndexEntry indices[], int n, int matricula, FILE *archivoBinario)
{
    int inicio = 0;
    int fin = n - 1;
    printf("%-12s %-30s %-50s %-50s %-15s %-30s %-30s %-15s %-12s\n", "Matrícula", "Nombre", "Apellido Paterno", "Apellido Materno", "Edad", "Sexo", "Posición de Trabajo", "Estado", "Celular");
    while (inicio <= fin)
    {
        int medio = (inicio + fin) / 2;

        if (indices[medio].key == matricula)
        {
            fseek(archivoBinario, indices[medio].index * sizeof(TWrkr), SEEK_SET);
            TWrkr registro;
            fread(&registro, sizeof(TWrkr), 1, archivoBinario);

            imprimirRegistro(registro);
            return indices[medio].index;
        }
        else 
        {
            if (indices[medio].key < matricula)
            {
            inicio = medio + 1;
            }
            else
        {
            fin = medio - 1;
        }
        }
        
    }

    printf("No se encontró un registro con la matrícula %d.\n", matricula);
    return -1;
}

void ordenarPorMatricula(TWrkr trabajadores[], int n)
{
    if (estaOrdenadoPorMatricula(trabajadores, n))
    {
        printf("El arreglo ya está ordenado por matrícula. No es necesario ordenarlo de nuevo.\n");
    }
    else
    {
        int tamanio = n;

        if (tamanio <= 100)
        {
            ordenarPorMatriculaSeleccion(trabajadores, tamanio);
            printf("El arreglo ha sido ordenado por matrícula utilizando el algoritmo de selección.\n");
        }
        else
        {
            ordenarPorMatriculaBurbuja(trabajadores, tamanio);
            printf("El arreglo ha sido ordenado por matrícula utilizando el algoritmo de burbuja.\n");
        }
    }
}

int estaOrdenadoPorMatricula(TWrkr trabajadores[], int n)
{
    for (int i = 1; i < n; i++)
    {
        if (trabajadores[i].enrollment < trabajadores[i - 1].enrollment)
        {
            return 0; 
        }
    }
    return 1; 
}

void ordenarPorMatriculaSeleccion(TWrkr trabajadores[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (trabajadores[j].status == 1 && (trabajadores[j].enrollment < trabajadores[minIndex].enrollment))
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            TWrkr temp = trabajadores[i];
            trabajadores[i] = trabajadores[minIndex];
            trabajadores[minIndex] = temp;
        }
    }
}

void ordenarPorMatriculaBurbuja(TWrkr trabajadores[], int n)
{

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (trabajadores[j].status == 1 && (trabajadores[j].enrollment > trabajadores[j + 1].enrollment))
            {
                TWrkr temp = trabajadores[j];
                trabajadores[j] = trabajadores[j + 1];
                trabajadores[j + 1] = temp;
            }
        }
    }
}

void imprimirRegistrosArchivoOriginal(TWrkr trabajadores[], int n, FILE *archivoBinario)
{
    fseek(archivoBinario, 0, SEEK_SET);
    TWrkr registro;
    printf("%-12s %-30s %-50s %-50s %-15s %-30s %-30s %-15s %-12s\n", "Matrícula", "Nombre", "Apellido Paterno", "Apellido Materno", "Edad", "Sexo", "Posición de Trabajo", "Estado", "Celular");
    while (fread(&registro, sizeof(TWrkr), 1, archivoBinario) == 1)
    {
        if (registro.status == 1)
        {
            imprimirRegistro(registro);
        }
    }
    
}

void imprimirRegistros(TWrkr trabajadores[], int n)
{
    printf("%-12s %-30s %-50s %-50s %-15s %-30s %-30s %-15s %-12s\n", "Matrícula", "Nombre", "Apellido Paterno", "Apellido Materno", "Edad", "Sexo", "Posición de Trabajo", "Estado", "Celular");
    for (int i = 0; i < n; i++)
    {
        if (trabajadores[i].status == 1)
        {
            imprimirRegistro(trabajadores[i]);
        }
    }
}


void cargarArchivoBinario(TIndexEntry indices[], int *n, int *maxSize)
{
    FILE *archivoBinario;
    TWrkr registro;
    int registrosValidos = 0;

    archivoBinario = fopen("C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 14\\datos.dat", "rb");

    fseek(archivoBinario, 0, SEEK_END);
    int tamanoArchivo = ftell(archivoBinario);
    fseek(archivoBinario, 0, SEEK_SET);
    *maxSize = (tamanoArchivo / sizeof(TWrkr)) * 1.25;

    while (fread(&registro, sizeof(TWrkr), 1, archivoBinario) == 1)
    {
        if (registro.status == 1)
        {
            indices[*n].key = registro.enrollment;
            indices[*n].index = registrosValidos;
            (*n)++;
        }
        registrosValidos++;
    }

    fclose(archivoBinario);
    printf("Archivo binario cargado correctamente.\n");
}


void generarArchivoTexto(TWrkr trabajadores[], int n)
{
    char nombreArchivo[50];
    printf("Ingresa el nombre del archivo (sin la extensión .txt): ");
    scanf("%s", nombreArchivo);

    FILE *archivo;
    char nombreCompleto[100]; 
    sprintf(nombreCompleto, "C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 14\\%s.txt", nombreArchivo);

    archivo = fopen(nombreCompleto, "w");

    int ordenado;
    printf("¿Desea imprimir los registros ordenados? (1 sí, 0 no): ");
    scanf("%d", &ordenado);

    if (ordenado)
    {
        ordenarPorMatricula(trabajadores, n);
        printf("Registros ordenados por matrícula:\n");
        fprintf(archivo, "%-12s %-30s %-50s %-50s %-15s %-30s %-30s %-15s %-12s\n", "Matrícula", "Nombre", "Apellido Paterno", "Apellido Materno", "Edad", "Sexo", "Posición de Trabajo", "Estado", "Celular");
        for (int i = 0; i < n; i++)
        {
            if (trabajadores[i].status == 1)
            {
                fprintf(archivo, "%-12d %-30s %-50s %-50s %-15d %-30s %-30s %-15s %-12d\n", trabajadores[i].enrollment, trabajadores[i].name, trabajadores[i].Lastname1, trabajadores[i].Lastname2, trabajadores[i].age, trabajadores[i].sex, trabajadores[i].jobposition, trabajadores[i].state, trabajadores[i].cellphone);
            }
        }
    }
    else
    {
        printf("Registros en su orden original:\n");
        fprintf(archivo, "%-12s %-30s %-50s %-50s %-15s %-30s %-30s %-15s %-12s\n", "Matrícula", "Nombre", "Apellido Paterno", "Apellido Materno", "Edad", "Sexo", "Posición de Trabajo", "Estado", "Celular");
        for (int i = 0; i < n; i++)
        {
            if (trabajadores[i].status == 1)
            {
                fprintf(archivo, "%-12d %-30s %-50s %-50s %-15d %-30s %-30s %-15s %-12d\n", trabajadores[i].enrollment, trabajadores[i].name, trabajadores[i].Lastname1, trabajadores[i].Lastname2, trabajadores[i].age, trabajadores[i].sex, trabajadores[i].jobposition, trabajadores[i].state, trabajadores[i].cellphone);
            }
        }
    }

    fclose(archivo);
    printf("Archivo de texto generado correctamente.\n");
}

void empaquetarRegistros(TWrkr trabajadores[], int *n)
{
    FILE *copiaSeguridad = fopen("C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 14\\datos.bak", "wb");
    if (copiaSeguridad == NULL)
    {
        printf("Error al crear la copia de seguridad.\n");
        return;
    }

    fwrite(trabajadores, sizeof(TWrkr), *n, copiaSeguridad);
    fclose(copiaSeguridad);

    FILE *archivoBinario = fopen("C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 14\\datos.dat", "rb+");
    if (archivoBinario == NULL)
    {
        printf("Error al abrir el archivo binario para empaquetar.\n");
        return;
    }

    fseek(archivoBinario, 0, SEEK_SET);
    FILE *temporal = fopen("C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 14\\temp.dat", "wb");
    if (temporal == NULL)
    {
        printf("Error al abrir el archivo temporal para empaquetar.\n");
        fclose(archivoBinario);
        return;
    }

    for (int i = 0; i < *n; i++)
    {
        if (trabajadores[i].status == 1)
        {
            fwrite(&trabajadores[i], sizeof(TWrkr), 1, temporal);
        }
    }

    fclose(temporal);
    fclose(archivoBinario);

    remove("C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 14\\datos.dat");
    rename("C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 14\\temp.dat", "C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 14\\datos.dat");

    printf("Registros inválidos empaquetados y archivo binario actualizado.\n");
    *n = contarRegistrosBinario("C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 14\\datos.dat");
}
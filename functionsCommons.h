#ifndef FUNCTIONS_COMMONS_H
#define FUNCTIONS_COMMONS_H

// UTILIDADES CON LISTAS
void limpiarCadena(char *cadena, int longitud);
int verificarFechaBaja(int idBuscar, MedxUsu *lista);

// UTILIDADES ARCHIVOS 
int verificarUltimaLineaFacturasLDE(char *nombreArchivo);

// UTILIDADES GENERAL
void obtenerFecha(const char* formato, char *cadenaDestino);
int obtenerFechaEnEntero();
void mostrarMensaje(int codigo);
void mostrarMensajeError(int codigo);


/*
	:::::::::::::::::::::::::::  UTILIDADES CON LISTAS  :::::::::::::::::::::::::::
*/

void limpiarCadena(char *cadena, int longitud){
    int i = 0;
    for (i=0; i < longitud; i++){
        cadena[i] = '\0';
    }
}

/**
 * @brief Su funcion es verificar si se ha dado de baja el usuario, para ello 
 * buscar en la lista MedxUsuario el id de la cuenta.
 * 
 * @param idBuscar Id o valor entero a buscar en la lista 
 * @param lista Lista donde se realizara la busqueda (MedxUsu)
 * @return int Devuelve un 1 si se dio de baja, 0 si es nulo
 */
int verificarFechaBaja(int idBuscar, MedxUsu *lista){
    int verificacion = 0; // 1 si se dio de baja, 0 si es nulo

    while (lista != NULL){
        if (lista->idCuenta == idBuscar){
            if (lista->fechaBaja != 0){
                verificacion = 1; 
            }
        }
        lista = lista->sgte;
    }

    return verificacion;
}

/*
	:::::::::::::::::::::::::::  UTILIDADES ARCHIVOS  :::::::::::::::::::::::::::
*/

/**
 * @brief Verificar ultimo caracter del archivo es un salto de linea
 * 
 * @param nombreArchivo Nombre del archivo a leer.
 * @return int Retorna 1 si encuentra un salto de linea "\n", 0 sino lo encuentra 
 */
int verificarUltimoCaracter(char *nombreArchivo){
    FILE *archivo = fopen(nombreArchivo, "r");
    char caracterActual;
    int encontrado = 0;
    
    if (archivo != NULL) {
        // Verificar si el archivo esta vacio
        while (!feof(archivo)){
            // Verificar último caracter
            caracterActual = fgetc(archivo);
        }
        fseek(archivo, -1, SEEK_CUR);
        caracterActual = fgetc(archivo);

        if (caracterActual == '\n') {
            encontrado = 1;
        }
    }else printf("No se pudo abrir el archivo.\n");

    fclose(archivo);
    
    return encontrado; 
}

/*
	:::::::::::::::::::::::::::  UTILIDADES GENERAL :::::::::::::::::::::::::::
*/

/**
 * @brief Funcion que devuelve entero la fecha actual del sistema en 
 * el formato deseado.
 * 
 * @param formato Formato deseado ( "%Y%m%d"  "%Y/%m/%d" )
 * @param cadenaDestino Cadena de destino con fecha actual del sistema 
 */
void obtenerFecha(const char* formato, char *cadenaDestino) {
    time_t tiempo;
    struct tm* fechaActual;
    char buffer[80];

    time(&tiempo);
    fechaActual = localtime(&tiempo);

    strftime(buffer, sizeof(buffer), formato, fechaActual);

    strcpy(cadenaDestino, buffer);
}

/**
 * @brief  Funcion que convierte la fecha actual de cadena de carateres a 
 * entero
 * 
 * @return int Fecha actual con formato ( %Y%m%d )
 */
int obtenerFechaEnEntero(){
    char cadena[80];
    obtenerFecha("%Y%m%d", cadena);
    return atoi(cadena);
}

void mostrarMensaje(int codigo){
    switch (codigo){
    case 1:
        printf("Proceso terminado correctamente.. :)\n\n");
        break;
    case 2:
        printf("Proceso no terminado correctamente.. :(\n");
        break;
    case 3:
        printf("El TAD Cola esta vacio..\n");
        break;
	case 4:
        printf("Archivo no creado correctamente.. :(\n");
        break;
	case 5:
        printf("Archivo no leido correctamente.. :(\n");
        break;
    case 6:
        printf("Archivo no se pudo abrir correctamente.. :(\n");
        break;
    case 7:
        printf("Lista vacia.. :(\n");
        break;
    case 8:
        printf("Lista cargada correctamente.. :)\n");
        break;
    case 9:
        printf("Archivo CSV cargado correctamente.. :)\n");
        break;
    case 10:
        printf("Id Buscado no encontrado.. :(\n");
        break;
    case 404:
        printf("Error en asignacion de memoria.. :(\n");
        break;
    case 500:
        system("pause");
        //system("cls");
        break;
    case 600:
        printf("Todo el equipo de desarrolladores le pide disculpas. Error nivel pro.!");
        system("pause");
        //system("cls");
        break;
    default:
        system("pause");
        system("cls");
        break;
    }
}

void mostrarMensajeError(int codigo){
    switch (codigo){
    case 1:
        printf("Error: Se ha ingresado un caracter, se requiere un numero.. :(\n");
        system("pause");
        system("cls");
        break;
    case 2:
        printf("Error: Numero ingresado es negativo.. :(\n");
        system("pause");
        system("cls");
        break;
    case 3:
        printf("Error en la lista..\n");
        system("pause");
        system("cls");
        break;
	case 4:
        printf("Archivo no creado correctamente.. :(\n");
        system("pause");
        system("cls");
        break;
	case 5:
        printf("Archivo no leido correctamente.. :(\n");
        system("pause");
        system("cls");
        break;
    case 6:
        printf("Archivo no se pudo abrir correctamente.. :(\n");
        system("pause");
        system("cls");
        break;
    case 7:
        printf("Error: Numero ingresado es mayor a 2 :(\n");
        system("pause");
        system("cls");
        break;
    default:
        system("pause");
        system("cls");
        break;
    }
}

void pause(int segundos) {
    clock_t tiempoInicio = clock();
    while ((clock() - tiempoInicio) / CLOCKS_PER_SEC < segundos);
}

// Debug de variable entera
void debugVar(int var){
    printf("\nDebug Var: %d\n",var);
}

#endif
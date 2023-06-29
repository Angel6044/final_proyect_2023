#ifndef FUNCTIONS_CSV_H
#define FUNCTIONS_CSV_H

void leerDatosCSVMediciones(mediciones **lMediciones, MedxUsu *lMedxUsu);
void escribirDatosCSVMediciones(char *nombreArchivo, char *tipo, mediciones *lMediciones);

void leerDatosCSVMedxUsu(MedxUsu **lMedxUsu);
void escribirDatosCSVMedxUsu(char *nombreArchivo, char *tipo, MedxUsu *lMedxUsu);

void leerDatosCSVUsuarios(usuarios **lUsuarios);
void escribirDatosCSVUsuarios(char *nombreArchivo, char *tipo, usuarios *lUsuarios);

void leerDatosCSVCostos(costos **lCostos);
void escribirDatosCSVCostos(char *nombreArchivo, char *tipo, costos *lCostos);

void leerDatosCSVFacturas(facturas **lFacturas);
void escribirDatosCSVFacturas(char *nombreArchivo, char *tipo, facturas *lFacturas);

void leerDatosCSVMedidores(medidores **lMedidores);
void escribirDatosCSVMedidores(char *nombreArchivo, char *tipo, medidores *lMedidores);

void showOptionsReadAll(usuarios **l1, medidores **l2, MedxUsu **l3, mediciones **l4, facturas **l5, costos **l6);
void readAllFilesCSV(usuarios **l1, medidores **l2, MedxUsu **l3, mediciones **l4, facturas **l5, costos **l6);
void writeAllFilesCSV(usuarios *l1, medidores *l2, MedxUsu *l3, mediciones *l4, facturas *l5, costos *l6);
void backupFilesCSV(usuarios *l1, medidores *l2, MedxUsu *l3, mediciones *l4, facturas *l5, costos *l6);

/*
	::::::::::::::::::::::::::::::: ALL :::::::::::::::::::::::::::::::::::
*/

/**
 * @brief Menu de opciones y control de opcion, para la lectura de archivos.
 * 
 * @param l1 lista de Usuarios 
 * @param l2 lista de Medidores
 * @param l3 lista de Medidores x Usuario
 * @param l4 lista de Mediciones
 * @param l5 lista de Facturas
 * @param l6 lista de Costos
 */
void showOptionsReadAll(usuarios **l1, medidores **l2, MedxUsu **l3, mediciones **l4, facturas **l5, costos **l6){
    int opcion;
    int valueEnd = 0;
    int ErrorNoNumeric = 0;
    char fechaActual[11];

    do {
        system("cls");
        obtenerFecha("%Y/%m/%d", fechaActual);
        printf("Fecha Actual: %s\n", fechaActual);
        printf("\n");
        printf("============================================================================================================================================\n");
        printf("                                                       MENU LECTURA DE ARCHIVOS\n");
        printf("============================================================================================================================================\n");
        printf("\n");
        printf("Desea borrar las listas existentes o insertar en las existentes?\n\n");
        printf(" >> [1] - Borrar listas existentes y leer nuevamente los archivos\n");
        printf(" >> [2] - Leer archivos y insertar en las listas existentes\n");
        printf(" >> [0] - Salir\n");
        printf(" >> >> Escriba una opcion: ");
        while(valueEnd == 0){
            fflush(stdin);
            if (scanf("%d", &opcion) != 1) ErrorNoNumeric = 1;
            if (opcion < 0 || ErrorNoNumeric == 1 || opcion > 2){
                if (ErrorNoNumeric == 1) mostrarMensajeError(1);    // Error Caracter ingresado
                if (opcion < 0) mostrarMensajeError(2);             // Error Numero ingresado < 0
                if (opcion > 2) mostrarMensajeError(7);             // Error Numero ingresado > 2
                ErrorNoNumeric = 0;
                printf(" >> [1] - Borrar listas existentes y leer nuevamente los archivos\n");
                printf(" >> [2] - Leer archivos y insertar a las listas existentes\n");
                printf(" >> [0] - Salir\n");
                printf ("Ingrese nuevamente una opcion: ");
            }else{
                valueEnd = 1; 
            }   
        }

        switch (opcion) {
            case 1:
                printf("Borrarando listas existentes y leyendo nuevamente los archivos.!\n");
                freeAllLists(&(*l1), &(*l2), &(*l3), &(*l4), &(*l5), &(*l6));
                break;
            case 2:
                printf("Leyendo archivos y insertando a las listas existentes.!\n");
                system("pause");
                break;
        }

        if (opcion != 0){
            readAllFilesCSV(&(*l1), &(*l2), &(*l3), &(*l4), &(*l5), &(*l6));
        }

        valueEnd = 0; 

    } while (opcion != 0);

    
}

/**
 * @brief Su funcion es leer todos los archivos CSV correspondientes que proporcionan
 * los datos y crean las listas para que sistema funcione correctamente.  
 * 
 * @param l1 lista de Usuarios 
 * @param l2 lista de Medidores
 * @param l3 lista de Medidores x Usuario
 * @param l4 lista de Mediciones
 * @param l5 lista de Facturas
 * @param l6 lista de Costos
 */
void readAllFilesCSV(usuarios **l1, medidores **l2, MedxUsu **l3, mediciones **l4, facturas **l5, costos **l6){
    printf(">> Leyendo archivo de Usuarios...\n"); //pause(1);
    leerDatosCSVUsuarios(&(*l1));
    printf(">> Leyendo archivo de Medidores...\n"); //pause(1);
    leerDatosCSVMedidores(&(*l2));
    printf(">> Leyendo archivo de MedidoresXUsuarios...\n"); //pause(1);
    leerDatosCSVMedxUsu(&(*l3));
    printf(">> Leyendo archivo de Mediciones...\n"); //pause(1);
    leerDatosCSVMediciones(&(*l4), (*l3));
    printf(">> Leyendo archivo de Facturas...\n"); //pause(1);
    leerDatosCSVFacturas(&(*l5));
    printf(">> Leyendo archivo de Costos...\n"); //pause(1); 
    leerDatosCSVCostos(&(*l6));
    system("pause");
}

/**
 * @brief Su funcion es crear nuevamente los archivos CSV correspondientes, con las listas existentes.
 * 
 * @param l1 lista de Usuarios 
 * @param l2 lista de Medidores
 * @param l3 lista de Medidores x Usuario
 * @param l4 lista de Mediciones
 * @param l5 lista de Facturas
 * @param l6 lista de Costos
 */
void writeAllFilesCSV(usuarios *l1, medidores *l2, MedxUsu *l3, mediciones *l4, facturas *l5, costos *l6){
    char nombreArchivo[30];

    printf(">> ESCRITURA: Archivo de Usuarios...\n"); //pause(1);
    strcpy(nombreArchivo, "usuarios.csv");
    escribirDatosCSVUsuarios(nombreArchivo, "w", l1);
    limpiarCadena(nombreArchivo, sizeof(nombreArchivo));

    printf(">> ESCRITURA: Archivo de Medidores...\n"); //pause(1);
    strcpy(nombreArchivo, "medidores.csv");
    escribirDatosCSVMedidores(nombreArchivo, "w", l2);
    limpiarCadena(nombreArchivo, sizeof(nombreArchivo));

    printf(">> ESCRITURA: Archivo de MedidoresXUsuarios...\n"); //pause(1);
    strcpy(nombreArchivo, "MedXUsuario.csv");
    escribirDatosCSVMedxUsu(nombreArchivo, "w", l3);
    limpiarCadena(nombreArchivo, sizeof(nombreArchivo));

    printf(">> ESCRITURA: Archivo de Mediciones...\n"); //pause(1);
    strcpy(nombreArchivo, "Mediciones.csv");
    escribirDatosCSVMediciones(nombreArchivo, "w", l4);
    limpiarCadena(nombreArchivo, sizeof(nombreArchivo));

    printf(">> ESCRITURA: Archivo de Facturas...\n"); //pause(1);
    strcpy(nombreArchivo, "Facturas.csv");
    escribirDatosCSVFacturas(nombreArchivo, "w", l5);
    limpiarCadena(nombreArchivo, sizeof(nombreArchivo));

    printf(">> ESCRITURA: Archivo de Costos...\n"); //pause(1); 
    strcpy(nombreArchivo, "Costos.csv");
    escribirDatosCSVCostos(nombreArchivo, "w", l6);
    limpiarCadena(nombreArchivo, sizeof(nombreArchivo));

    system("pause");
}

/**
 * @brief Su funcion es crear una copia de seguridad de los archivos CSV correspondientes, 
 * con las listas existentes.
 * 
 * @param l1 lista de Usuarios 
 * @param l2 lista de Medidores
 * @param l3 lista de Medidores x Usuario
 * @param l4 lista de Mediciones
 * @param l5 lista de Facturas
 * @param l6 lista de Costos
 */
void backupFilesCSV(usuarios *l1, medidores *l2, MedxUsu *l3, mediciones *l4, facturas *l5, costos *l6){
    char nombreArchivo[50];
    char extension[] = ".csv";

    char fechaActual[10];
    obtenerFecha("%Y%m%d", fechaActual);

    printf(">> ESCRITURA: Archivo de Usuarios...\n"); 
    strcpy(nombreArchivo, "backup/backup_usuarios_");
    strcat(nombreArchivo, fechaActual);
    strcat(nombreArchivo, extension);
    escribirDatosCSVUsuarios(nombreArchivo, "w", l1);
    limpiarCadena(nombreArchivo, sizeof(nombreArchivo));

    printf(">> ESCRITURA: Archivo de Medidores...\n"); 
    strcpy(nombreArchivo, "backup/backup_medidores");
    strcat(nombreArchivo, fechaActual);
    strcat(nombreArchivo, extension);
    escribirDatosCSVMedidores(nombreArchivo, "w", l2);
    limpiarCadena(nombreArchivo, sizeof(nombreArchivo));

    printf(">> ESCRITURA: Archivo de MedidoresXUsuarios...\n"); 
    strcpy(nombreArchivo, "backup/backup_MedXUsuario_");
    strcat(nombreArchivo, fechaActual);
    strcat(nombreArchivo, extension);
    escribirDatosCSVMedxUsu(nombreArchivo, "w", l3);
    limpiarCadena(nombreArchivo, sizeof(nombreArchivo));

    printf(">> ESCRITURA: Archivo de Mediciones...\n"); 
    strcpy(nombreArchivo, "backup/backup_mediciones_");
    strcat(nombreArchivo, fechaActual);
    strcat(nombreArchivo, extension);
    escribirDatosCSVMediciones(nombreArchivo, "w", l4);
    limpiarCadena(nombreArchivo, sizeof(nombreArchivo));

    printf(">> ESCRITURA: Archivo de Facturas...\n"); 
    strcpy(nombreArchivo, "backup/backup_facturas_");
    strcat(nombreArchivo, fechaActual);
    strcat(nombreArchivo, extension);
    escribirDatosCSVFacturas(nombreArchivo, "w", l5);
    limpiarCadena(nombreArchivo, sizeof(nombreArchivo));

    printf(">> ESCRITURA: Archivo de Costos...\n");  
    strcpy(nombreArchivo, "backup/backup_costos_");
    strcat(nombreArchivo, fechaActual);
    strcat(nombreArchivo, extension);
    escribirDatosCSVCostos(nombreArchivo, "w", l6);
    limpiarCadena(nombreArchivo, sizeof(nombreArchivo));

    system("pause");
}

/*
::::::::::::::::::::::::::::::::::::::: Costos :::::::::::::::::::::::::::::::::::::::
*/

/**
 * @brief Leer los datos del archivo CSV de Costos. Donde cada linea representa
 * un registro y necesita ser pasada a nodos.
 * 
 * @param lCostos lista de costos, para insertar los nodos creados.
 */
void leerDatosCSVCostos(costos **lCostos){
    costos *nv = NULL;
    char nombreArchivo[] = "Costos.csv";
    int valueSave = 0;
    int bandEnd = 0;        // Bandera: Si es 1 se llego al final de la linea

    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        mostrarMensaje(6);
    }else{
        int j=0;            // Contador para controlar los caracteres leidos por linea.
        int k=0;            // Contador para controlar la cadena para cada palabra o dato
        int contComas = 0;  // Contador de comas para controlar los campos en la tabla.
        char linea[1000];   // Contendra cada linea leida del archivo
        char dato[1000];    // Contendra cada dato que corresponde a una linea y campo especifico

        while (fgets(linea, sizeof(linea), archivo)){
        
            // Eliminar el salto de línea final
            if (linea[strlen(linea) - 1] == '\n')
                linea[strlen(linea) - 1] = '\0';

            // Creamos el nuevo nodo
            nv = (costos *) malloc(sizeof(costos));
            if (nv != NULL){
                // Recorremos la linea hasta el final
                while (bandEnd != 1){
                    if (linea[j] != '|' && linea[j] != '\0'){
                        dato[k] = linea[j];
                        k++;
                    }else{
                        contComas++;      // Aumentar el contador para identificar el campo correspondiente

                        valueSave = atoi(dato);

                        switch (contComas){
                        case 1:
                            nv->idCostos = valueSave;
                            break;
                        case 2:
                            nv->mtsDesde = valueSave;
                            break;
                        case 3:
                            nv->mtsHasta = valueSave;
                            break;
                        case 4:
                            nv->valorMetro = valueSave;       
                            nv->sgte = NULL;
                            break;
                        default:
                            mostrarMensaje(2);  // Error
                            break;
                        }

                        limpiarCadena(dato, sizeof(dato)); 

                        k = 0;          // Reiniciar contador para controlar la cadena dato
                    }
                    if (linea[j] == '\0') bandEnd = 1; // Salir del bucle, dejar de recorrer la cadena
                    j++;
                }

                insertarCostosLES(nv, &(*lCostos));

                nv = NULL;
            }
            // Limpiar la cadena y leer el archivo
            limpiarCadena(linea, sizeof(linea));

            bandEnd = 0;    // Reiniciar bandera para finalizar el bucle que recorre la linea
            contComas = 0;  // Reiniciar el contador de comas, que se utiliza para identificar los datos
            j = 0;          // Reiniciar el contador para controlar los caracteres leidos.
        }

        printf("\nArchivo de costos leido y lista creada correctamente. :)\n\n");
    }
    fclose(archivo);
}

/**
 * @brief Leer los nodos de la lista y escribirlos en el archivo CSV de costos
 * 
 * Se puede abrir el archivo en modo de escritura de anexado "a" y asi el nuevo 
 * contenido se agregará al final del archivo.
 * 
 * @param nombreArchivo Cadena de caracteres. Nombre para el archivo
 * @param tipo Caracter. Tipo de operacion: Escritura y creacion (w) o Añadir al final (a)
 * @param lCostos Lista de costos
 */
void escribirDatosCSVCostos(char *nombreArchivo, char *tipo, costos *lCostos){
    int resultadoUltimoCaracter;

    // Verificamos el tipo de operacion. [a] - Actualizar  |  [w] - Crear nuevo
    int comparacion = strcmp("a", tipo);

    // Verificar si el último carácter es un salto de línea, solo si tipo es "a"
    if (comparacion == 0) resultadoUltimoCaracter = verificarUltimoCaracter(nombreArchivo);
    else resultadoUltimoCaracter = 1;   // En caso de que se trate de operacion [w] entonces no se realiza salto de linea
    
    FILE* archivo = fopen(nombreArchivo, tipo);
    if (archivo == NULL) {
        mostrarMensaje(6);  // Error al abrir el archivo
    }else{
        if (lCostos == NULL){
            mostrarMensaje(7);  // Lista vacia
        }else{
            // Si el resultado es 0, entonces realizamos salto de linea
            if (resultadoUltimoCaracter == 0 && comparacion == 0) {
                fprintf(archivo, "\n%d|%d|%d|%d\n",lCostos->idCostos, lCostos->mtsDesde, lCostos->mtsHasta, lCostos->valorMetro);
                lCostos = lCostos->sgte;
            }
            while (lCostos != NULL){
                fprintf(archivo, "%d|%d|%d|%d\n",lCostos->idCostos, lCostos->mtsDesde, lCostos->mtsHasta, lCostos->valorMetro);
                lCostos = lCostos->sgte;
            }
            mostrarMensaje(9); // Cargado correctamente
        }
    }
    fclose(archivo);
}

/*
::::::::::::::::::::::::::::::::::::::: Facturas :::::::::::::::::::::::::::::::::::::::
*/

/**
 * @brief Leer los datos del archivo CSV de Facturas. Donde cada linea representa
 * un registro y necesita ser pasada a nodos.
 * 
 * @param lFacturas lista de facturas, para insertar los nodos creados.
 */
void leerDatosCSVFacturas(facturas **lFacturas){
    facturas *nv = NULL;
    char nombreArchivo[] = "Facturas.csv";
    int valueSave = 0;
    double valueFloatSave = 0;
    int bandEnd = 0;        // Bandera: Si es 1 se llego al final de la linea

    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        mostrarMensaje(6);
    }else{
        int j=0;            // Contador para controlar los caracteres leidos por linea.
        int k=0;            // Contador para controlar la cadena para cada palabra o dato
        int contComas = 0;  // Contador de comas para controlar los campos en la tabla.
        char linea[1000];   // Contendra cada linea leida del archivo
        char dato[1000];    // Contendra cada dato que corresponde a una linea y campo especifico

        while (fgets(linea, sizeof(linea), archivo)){
            
            // Eliminar el salto de línea final
            if (linea[strlen(linea) - 1] == '\n')
                linea[strlen(linea) - 1] = '\0';

            // Creamos el nuevo nodo
            nv = (facturas *) malloc(sizeof(facturas));
            if (nv != NULL){
                // Recorremos la linea hasta el final
                while (bandEnd != 1){
                    if (linea[j] != '|' && linea[j] != '\0'){
                        dato[k] = linea[j];
                        k++;
                    }else{
                        contComas++;      // Aumentar el contador para identificar el campo correspondiente

                        valueSave = atoi(dato);

                        switch (contComas){
                        case 1:
                            nv->idCuenta = valueSave;
                            break;
                        case 2:
                            nv->periodo = valueSave;
                            break;
                        case 3:
                            nv->fechaEmision = valueSave;
                            break;
                        case 4:
                            valueFloatSave = strtod(dato, NULL);        // Convertir a double
                            nv->consumo = valueFloatSave;       
                            break;
                        case 5:
                            valueFloatSave = strtod(dato, NULL);        // Convertir a double
                            nv->totalAPagar = valueFloatSave;       
                            break;
                        case 6:
                            nv->pagado = valueSave;       
                            nv->sgte = NULL;
                            break;
                        default:
                            mostrarMensaje(2);  // Error
                            break;
                        }

                        limpiarCadena(dato, sizeof(dato)); 

                        k = 0;          // Reiniciar contador para controlar la cadena dato
                    }
                    if (linea[j] == '\0') bandEnd = 1; // Salir del bucle, dejar de recorrer la cadena
                    j++;
                }

                insertarFacturasLES(nv, &(*lFacturas));

                nv = NULL;
            }
            // Limpiar la cadena y leer el archivo
            limpiarCadena(linea, sizeof(linea));

            bandEnd = 0;   // Reiniciar bandera para finalizar el bucle que recorre la linea
            contComas = 0; // Reiniciar el contador de comas, que se utiliza para identificar los datos
            j = 0; // Reiniciar el contador para controlar los caracteres leidos.
        }

        printf("\nArchivo de facturas leido y lista creada correctamente. :)\n\n");
    }
    fclose(archivo);
}

/**
 * @brief Leer los nodos de la lista y escribirlos en el archivo CSV de facturas
 * 
 * Se puede abrir el archivo en modo de escritura de anexado "a" y asi el nuevo 
 * contenido se agregará al final del archivo.
 * 
 * @param nombreArchivo Cadena de caracteres. Nombre para el archivo
 * @param tipo Caracter. Tipo de operacion: Escritura y creacion (w) o Añadir al final (a)
 * @param lFacturas Lista de facturas
 */
void escribirDatosCSVFacturas(char *nombreArchivo, char *tipo, facturas *lFacturas){
    int resultadoUltimoCaracter;

    // Verificamos el tipo de operacion. [a] - Actualizar  |  [w] - Crear nuevo
    int comparacion = strcmp("a", tipo);

    // Verificar si el último carácter es un salto de línea, solo si tipo es "a"
    if (comparacion == 0) resultadoUltimoCaracter = verificarUltimoCaracter(nombreArchivo);
    else resultadoUltimoCaracter = 1;   // En caso de que se trate de operacion [w] entonces no se realiza salto de linea

    FILE* archivo = fopen(nombreArchivo, tipo);
    if (archivo == NULL) {
        mostrarMensaje(6);  // Error al abrir el archivo
    }else{
        if (lFacturas == NULL){
            mostrarMensaje(7);  // Lista vacia
        }else{
            // Si el resultado es 0, entonces realizamos salto de linea
            if (resultadoUltimoCaracter == 0 && comparacion == 0) {
                fprintf(archivo, "\n%d|%d|%d|%.2f|%.2f|%d\n",lFacturas->idCuenta, lFacturas->periodo, lFacturas->fechaEmision, lFacturas->consumo, lFacturas->totalAPagar, lFacturas->pagado);
                lFacturas = lFacturas->sgte;
            }
            while (lFacturas != NULL){
                fprintf(archivo, "%d|%d|%d|%.2f|%.2f|%d\n",lFacturas->idCuenta, lFacturas->periodo, lFacturas->fechaEmision, lFacturas->consumo, lFacturas->totalAPagar, lFacturas->pagado);
                lFacturas = lFacturas->sgte;
            }
            mostrarMensaje(9); // Cargado correctamente
        }
    }
    fclose(archivo);
}

/*
::::::::::::::::::::::::::::::::::::::: Mediciones :::::::::::::::::::::::::::::::::::::::
*/

/**
 * @brief Leer los datos del archivo CSV de mediciones. Donde cada linea representa
 * un registro y necesita ser pasada a nodos.
 * 
 * @param lMediciones lista de mediciones, para insertar los nodos creados. Lectura y escritura
 * @param lMedxUsu lista de Medidoes x Usuarios, control de baja. Lectura
 */
void leerDatosCSVMediciones(mediciones **lMediciones, MedxUsu *lMedxUsu){
    mediciones *nv = NULL;
    char nombreArchivo[] = "Mediciones.csv";
    int valueSave = 0;
    double valueFloatSave = 0;
    int bandEnd = 0;        // Bandera: Si es 1 se llego al final de la linea
    int verificarBaja = 0;        // Verificar estado de la cuenta

    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        mostrarMensaje(6);
    }else{
        int j=0;            // Contador para controlar los caracteres leidos por linea.
        int k=0;            // Contador para controlar la cadena para cada palabra o dato
        int contComas = 0;  // Contador de comas para controlar los campos en la tabla.
        char linea[1000];   // Contendra cada linea leida del archivo
        char dato[1000];    // Contendra cada dato que corresponde a una linea y campo especifico

        while (fgets(linea, sizeof(linea), archivo)){
            
            // Eliminar el salto de línea final
            if (linea[strlen(linea) - 1] == '\n')
                linea[strlen(linea) - 1] = '\0';

            // Creamos el nuevo nodo
            nv = (mediciones *) malloc(sizeof(mediciones));
            if (nv != NULL){
                // Recorremos la linea hasta el final
                while (bandEnd != 1){
                    if (linea[j] != '|' && linea[j] != '\0'){
                        dato[k] = linea[j];
                        k++;
                    }else{
                        contComas++;      // Aumentar el contador para identificar el campo correspondiente

                        valueSave = atoi(dato);

                        switch (contComas){
                        case 1:
                            nv->idCuenta = valueSave;
                            break;
                        case 2:
                            nv->periodo = valueSave;
                            break;
                        case 3:
                            nv->fechaLectura = valueSave;
                            break;
                        case 4:
                            valueFloatSave = strtod(dato, NULL);        // Convertir a double
                            nv->lectura = valueFloatSave;       
                            nv->ant = NULL;
                            nv->sgte = NULL;
                            break;
                        default:
                            mostrarMensaje(2);  // Error
                            break;
                        }

                        limpiarCadena(dato, sizeof(dato)); 

                        k = 0;          // Reiniciar contador para controlar la cadena dato
                    }
                    if (linea[j] == '\0') bandEnd = 1; // Salir del bucle, dejar de recorrer la cadena
                    j++;
                }

                // Verificar si esta dado de baja
                verificarBaja = verificarFechaBaja(nv->idCuenta, lMedxUsu);

                if (verificarBaja == 0){   // Si es cero, no se ha dado de baja
                    insertarMedicionesLDE(nv, &(*lMediciones));
                }
                
                nv = NULL;
            }
            // Limpiar la cadena y leer el archivo
            limpiarCadena(linea, sizeof(linea));

            bandEnd = 0;   // Reiniciar bandera para finalizar el bucle que recorre la linea
            contComas = 0; // Reiniciar el contador de comas, que se utiliza para identificar los datos
            j = 0; // Reiniciar el contador para controlar los caracteres leidos.
        }

        printf("\nArchivo de mediciones leido y lista creada correctamente. :)\n\n");
    }
    fclose(archivo);
}

/**
 * @brief Leer los nodos de la lista y escribirlos en el archivo CSV de mediciones
 * 
 * Se puede abrir el archivo en modo de escritura de anexado "a" y asi el nuevo 
 * contenido se agregará al final del archivo.
 * 
 * @param nombreArchivo Cadena de caracteres. Nombre para el archivo
 * @param tipo Caracter. Tipo de operacion: Escritura y creacion (w) o Añadir al final (a)
 * @param lMediciones Lista de mediciones
 */
void escribirDatosCSVMediciones(char *nombreArchivo, char *tipo, mediciones *lMediciones){
    int resultadoUltimoCaracter;

    // Verificamos el tipo de operacion. [a] - Actualizar  |  [w] - Crear nuevo
    int comparacion = strcmp("a", tipo);

    // Verificar si el último carácter es un salto de línea, solo si tipo es "a"
    if (comparacion == 0) resultadoUltimoCaracter = verificarUltimoCaracter(nombreArchivo);
    else resultadoUltimoCaracter = 1;   // En caso de que se trate de operacion [w] entonces no se realiza salto de linea

    FILE* archivo = fopen(nombreArchivo, tipo);
    if (archivo == NULL) {
        mostrarMensaje(6);  // Error al abrir el archivo
    }else{
        if (lMediciones == NULL){
            mostrarMensaje(7);  // Lista vacia
        }else{
            // Si el resultado es 0, entonces realizamos salto de linea
            if (resultadoUltimoCaracter == 0 && comparacion == 0) {
                fprintf(archivo, "\n%d|%d|%d|%.2f\n", lMediciones->idCuenta, lMediciones->periodo, lMediciones->fechaLectura, lMediciones->lectura);
                lMediciones = lMediciones->sgte;
            }
            while (lMediciones != NULL){
                fprintf(archivo, "%d|%d|%d|%.2f\n", lMediciones->idCuenta, lMediciones->periodo, lMediciones->fechaLectura, lMediciones->lectura);
                lMediciones = lMediciones->sgte;
            }
            mostrarMensaje(9); // Cargado correctamente
        }
    }
    fclose(archivo);
}

/*
::::::::::::::::::::::::::::::::::::::: MEDxUSU :::::::::::::::::::::::::::::::::::::::
*/

/**
 * @brief Leer los datos del archivo CSV de MedxUsu. Donde cada linea representa
 * un registro y necesita ser pasada a nodos.
 * 
 * @param lMedxUsu lista de MedxUsu, para insertar los nodos creados.
 */
void leerDatosCSVMedxUsu(MedxUsu **lMedxUsu){
    MedxUsu *nv = NULL;
    char nombreArchivo[] = "MedXUsuario.csv";
    int valueSave = 0;
    int bandEnd = 0;        // Bandera: Si es 1 se llego al final de la linea

    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        mostrarMensaje(6);
    }else{
        int j=0;            // Contador para controlar los caracteres leidos por linea.
        int k=0;            // Contador para controlar la cadena para cada palabra o dato
        int contComas = 0;  // Contador de comas para controlar los campos en la tabla.
        char linea[1000];   // Contendra cada linea leida del archivo
        char dato[1000];    // Contendra cada dato que corresponde a una linea y campo especifico

        while (fgets(linea, sizeof(linea), archivo)){

            // Eliminar el salto de línea final
            if (linea[strlen(linea) - 1] == '\n')
                linea[strlen(linea) - 1] = '\0';

            // Creamos el nuevo nodo
            nv = (MedxUsu *) malloc(sizeof(MedxUsu));
            if (nv != NULL){
                // Recorremos la linea hasta el final
                while (bandEnd != 1){
                    if (linea[j] != '|' && linea[j] != '\0'){
                        dato[k] = linea[j];
                        k++;
                    }else{
                        contComas++;      // Aumentar el contador para identificar el campo correspondiente

                        valueSave = atoi(dato);

                        switch (contComas){
                        case 1:
                            nv->idUsuario = valueSave;
                            break;
                        case 2:
                            nv->idMedidor = valueSave;
                            break;
                        case 3:
                            nv->idCuenta = valueSave;
                            break;
                        case 4:
                            nv->fechaAlta = valueSave;
                            break;
                        case 5:
                            nv->fechaBaja = valueSave;
                            nv->sgte = NULL;
                            break;
                        default:
                            mostrarMensaje(2);  // Error
                            break;
                        }

                        limpiarCadena(dato, sizeof(dato)); 

                        k = 0;          // Reiniciar contador para controlar la cadena dato
                    }
                    if (linea[j] == '\0') bandEnd = 1; // Salir del bucle, dejar de recorrer la cadena
                    j++;
                }

                insertarMedxUsuLES(nv, &(*lMedxUsu));

                nv = NULL;
            }
            // Limpiar la cadena y leer el archivo
            limpiarCadena(linea, sizeof(linea));

            bandEnd = 0;   // Reiniciar bandera para finalizar el bucle que recorre la linea
            contComas = 0; // Reiniciar el contador de comas, que se utiliza para identificar los datos
            j = 0; // Reiniciar el contador para controlar los caracteres leidos.
        }

        printf("\nArchivo MedxUsu leido y lista creada correctamente. :)\n\n");
    }
    fclose(archivo);
}

/**
 * @brief Leer los nodos de la lista y escribirlos en el archivo CSV de MedxUsu
 * 
 * Se puede abrir el archivo en modo de escritura de anexado "a" y asi el nuevo 
 * contenido se agregará al final del archivo.
 * 
 * @param nombreArchivo Cadena de caracteres. Nombre para el archivo
 * @param tipo Caracter. Tipo de operacion: Escritura y creacion (w) o Añadir al final (a)
 * @param lMedxUsu Lista de MedxUsu
 */
void escribirDatosCSVMedxUsu(char *nombreArchivo, char *tipo, MedxUsu *lMedxUsu){
    int resultadoUltimoCaracter;

    // Verificamos el tipo de operacion. [a] - Actualizar  |  [w] - Crear nuevo
    int comparacion = strcmp("a", tipo);

    // Verificar si el último carácter es un salto de línea, solo si tipo es "a"
    if (comparacion == 0) resultadoUltimoCaracter = verificarUltimoCaracter(nombreArchivo);
    else resultadoUltimoCaracter = 1;   // En caso de que se trate de operacion [w] entonces no se realiza salto de linea

    FILE* archivo = fopen(nombreArchivo, tipo);
    if (archivo == NULL) {
        mostrarMensaje(6);  // Error al abrir el archivo
    }else{
        if (lMedxUsu == NULL){
            mostrarMensaje(7);  // Lista vacia
        }else{
            // Si el resultado es 0, entonces realizamos salto de linea
            if (resultadoUltimoCaracter == 0 && comparacion == 0) {
                fprintf(archivo, "\n%d|%d|%d|%d|%d\n", lMedxUsu->idUsuario, lMedxUsu->idMedidor, lMedxUsu->idCuenta, lMedxUsu->fechaAlta, lMedxUsu->fechaBaja);
                lMedxUsu = lMedxUsu->sgte;
            }
            while (lMedxUsu != NULL){
                fprintf(archivo, "%d|%d|%d|%d|%d\n", lMedxUsu->idUsuario, lMedxUsu->idMedidor, lMedxUsu->idCuenta, lMedxUsu->fechaAlta, lMedxUsu->fechaBaja);
                lMedxUsu = lMedxUsu->sgte;
            }
            mostrarMensaje(9); // Cargado correctamente
        }
    }
    fclose(archivo);
}

/*
::::::::::::::::::::::::::::::::::::::: USUARIOS :::::::::::::::::::::::::::::::::::::::
*/

/**
 * @brief Leer los datos del archivo CSV de usuarios. Donde cada linea representa
 * un registro y necesita ser pasada a nodos.
 * 
 * @param lUsuarios lista de usuarios, para insertar los nodos creados.
 */
void leerDatosCSVUsuarios(usuarios **lUsuarios){
    usuarios *nv = NULL;
    char nombreArchivo[] = "usuarios.csv";
    int valueSave = 0;
    int bandEnd = 0;        // Bandera: Si es 1 se llego al final de la linea

    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        mostrarMensaje(6);
    }else{
        int j=0;            // Contador para controlar los caracteres leidos por linea.
        int k=0;            // Contador para controlar la cadena para cada palabra o dato
        int contComas = 0;  // Contador de comas para controlar los campos en la tabla.
        char linea[1000];   // Contendra cada linea leida del archivo
        char dato[1000];    // Contendra cada dato que corresponde a una linea y campo especifico

        while (fgets(linea, sizeof(linea), archivo)){

            // Eliminar el salto de línea final
            if (linea[strlen(linea) - 1] == '\n')
                linea[strlen(linea) - 1] = '\0';

            // Creamos el nuevo nodo
            nv = (usuarios *) malloc(sizeof(usuarios));
            if (nv != NULL){
                // Recorremos la linea hasta el final
                while (bandEnd != 1){
                    if (linea[j] != '|' && linea[j] != '\0'){
                        dato[k] = linea[j];
                        k++;
                    }else{
                        contComas++;      // Aumentar el contador para identificar el campo correspondiente

                        valueSave = atoi(dato);

                        switch (contComas){
                        case 1:
                            nv->idUsuario = valueSave;
                            break;
                        case 2:
                            strcpy(nv->apellidoNombre, dato);
                            break;
                        case 3:
                            nv->fechaAlta = valueSave;
                            nv->sgte = NULL;
                            break;
                        default:
                            mostrarMensaje(2);  // Error
                            break;
                        }

                        limpiarCadena(dato, sizeof(dato)); 

                        k = 0;          // Reiniciar contador para controlar la cadena dato
                    }
                    if (linea[j] == '\0') bandEnd = 1; // Salir del bucle, dejar de recorrer la cadena
                    j++;
                }

                insertarUsuariosLES(nv, &(*lUsuarios));

                nv = NULL;
            }
            // Limpiar la cadena y leer el archivo
            limpiarCadena(linea, sizeof(linea));

            bandEnd = 0;   // Reiniciar bandera para finalizar el bucle que recorre la linea
            contComas = 0; // Reiniciar el contador de comas, que se utiliza para identificar los datos
            j = 0; // Reiniciar el contador para controlar los caracteres leidos.
        }

        printf("\nArchivo de usuarios leido y lista creada correctamente. :)\n\n");
    }
    fclose(archivo);
}

/**
 * @brief Leer los nodos de la lista y escribirlos en el archivo CSV de usuarios
 * 
 * Se puede abrir el archivo en modo de escritura de anexado "a" y asi el nuevo 
 * contenido se agregará al final del archivo.
 * 
 * @param nombreArchivo Cadena de caracteres. Nombre para el archivo
 * @param tipo Caracter. Tipo de operacion: Escritura y creacion (w) o Añadir al final (a)
 * @param lUsuarios Lista de usuarios
 */
void escribirDatosCSVUsuarios(char *nombreArchivo, char *tipo, usuarios *lUsuarios){
    int resultadoUltimoCaracter;

    // Verificamos el tipo de operacion. [a] - Actualizar  |  [w] - Crear nuevo
    int comparacion = strcmp("a", tipo);

    // Verificar si el último carácter es un salto de línea, solo si tipo es "a"
    if (comparacion == 0) resultadoUltimoCaracter = verificarUltimoCaracter(nombreArchivo);
    else resultadoUltimoCaracter = 1;   // En caso de que se trate de operacion [w] entonces no se realiza salto de linea

    FILE* archivo = fopen(nombreArchivo, tipo);
    if (archivo == NULL) {
        mostrarMensaje(6);  // Error al abrir el archivo
    }else{
        if (lUsuarios == NULL){
            mostrarMensaje(7);  // Lista vacia
        }else{
            // Si el resultado es 0, entonces realizamos salto de linea
            if (resultadoUltimoCaracter == 0 && comparacion == 0) {
                fprintf(archivo, "\n%d|%s|%d\n",lUsuarios->idUsuario, lUsuarios->apellidoNombre, lUsuarios->fechaAlta);
                lUsuarios = lUsuarios->sgte;
            }
            while (lUsuarios != NULL){
                fprintf(archivo, "%d|%s|%d\n",lUsuarios->idUsuario, lUsuarios->apellidoNombre, lUsuarios->fechaAlta);
                lUsuarios = lUsuarios->sgte;
            }
            mostrarMensaje(9); // Cargado correctamente
        }
    }
    fclose(archivo);
}


/*
::::::::::::::::::::::::::::::::::::::: MEDIDORES :::::::::::::::::::::::::::::::::::::::
*/

/**
 * @brief Leer los datos del archivo CSV de medidores. Donde cada linea representa
 * un registro y necesita ser pasada a nodos.
 * 
 * @param lMedidores lista de medidores, para insertar los nodos creados.
 */
void leerDatosCSVMedidores(medidores **lMedidores){
    medidores *nv = NULL;
    char nombreArchivo[] = "medidores.csv";
    int valueSave = 0;
    int bandEnd = 0;        // Bandera: Si es 1 se llego al final de la linea

    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        mostrarMensaje(6);
    }else{
        int j=0;            // Contador para controlar los caracteres leidos por linea.
        int k=0;            // Contador para controlar la cadena para cada palabra o dato
        int contComas = 0;  // Contador de comas para controlar los campos en la tabla.
        char linea[1000];   // Contendra cada linea leida del archivo
        char dato[1000];    // Contendra cada dato que corresponde a una linea y campo especifico

        while (fgets(linea, sizeof(linea), archivo)){

            // Eliminar el salto de línea final
            if (linea[strlen(linea) - 1] == '\n')
                linea[strlen(linea) - 1] = '\0';    

            // Creamos el nuevo nodo
            nv = (medidores *) malloc(sizeof(medidores));
            if (nv != NULL){
                // Recorremos la linea hasta el final
                while (bandEnd != 1){
                    if (linea[j] != '|' && linea[j] != '\0'){
                        dato[k] = linea[j];
                        k++;
                    }else{
                        contComas++;      // Aumentar el contador para identificar el campo correspondiente

                        switch (contComas){
                        case 1:
                            valueSave = atoi(dato);
                            nv->idMedidor = valueSave;
                            break;
                        case 2:
                            strcpy(nv->numero, dato);
                            break;
                        case 3:
                            strcpy(nv->modelo, dato);
                            nv->sgte = NULL;
                            break;
                        default:
                            mostrarMensaje(2);  // Error
                            break;
                        }

                        limpiarCadena(dato, sizeof(dato)); 

                        k = 0;          // Reiniciar contador para controlar la cadena dato
                    }
                    if (linea[j] == '\0') bandEnd = 1; // Salir del bucle, dejar de recorrer la cadena
                    j++;
                }

                insertarMedidorLEC(nv, &(*lMedidores));

                nv = NULL;
            }
            // Limpiar la cadena y leer el archivo
            limpiarCadena(linea, sizeof(linea));

            bandEnd = 0;   // Reiniciar bandera para finalizar el bucle que recorre la linea
            contComas = 0; // Reiniciar el contador de comas, que se utiliza para identificar los datos
            j = 0; // Reiniciar el contador para controlar los caracteres leidos.
        }

        printf("\nArchivo de medidores leido y lista creada correctamente. :)\n\n");
    }
    fclose(archivo);
}

/**
 * @brief Leer los nodos de la lista y escribirlos en el archivo CSV de medidores
 * 
 * Se puede abrir el archivo en modo de escritura de anexado "a" y asi el nuevo 
 * contenido se agregará al final del archivo.
 * 
 * @param nombreArchivo Cadena de caracteres. Nombre para el archivo
 * @param tipo Caracter. Tipo de operacion: Escritura y creacion (w) o Añadir al final (a)
 * @param lMedidores Lista de medidores
 */
void escribirDatosCSVMedidores(char *nombreArchivo, char *tipo, medidores *lMedidores){
    int resultadoUltimoCaracter;

    // Verificamos el tipo de operacion. [a] - Actualizar  |  [w] - Crear nuevo
    int comparacion = strcmp("a", tipo);

    // Verificar si el último carácter es un salto de línea, solo si tipo es "a"
    if (comparacion == 0) resultadoUltimoCaracter = verificarUltimoCaracter(nombreArchivo);
    else resultadoUltimoCaracter = 1;   // En caso de que se trate de operacion [w] entonces no se realiza salto de linea

    medidores *aux = NULL;
    aux = lMedidores->sgte;

    FILE* archivo = fopen(nombreArchivo, tipo);
    if (archivo == NULL) {
        mostrarMensaje(6);  // Error al abrir el archivo
    }else{
        if (lMedidores == NULL){
            mostrarMensaje(7);  // Lista vacia
        }else{
            // Si el resultado es 0, entonces realizamos salto de linea
            if (resultadoUltimoCaracter == 0 && comparacion == 0) {
                fprintf(archivo, "\n%d|%s|%s\n",lMedidores->idMedidor, lMedidores->numero, lMedidores->modelo);
            }else{
                fprintf(archivo, "%d|%s|%s\n",lMedidores->idMedidor, lMedidores->numero, lMedidores->modelo);
            }
            while (aux != lMedidores){
                fprintf(archivo, "%d|%s|%s\n", aux->idMedidor, aux->numero, aux->modelo);
                aux = aux->sgte;
            }
            mostrarMensaje(9); // Cargado correctamente
        }
    }
    aux = NULL;
    fclose(archivo);
}

#endif
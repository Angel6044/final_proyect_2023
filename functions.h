/**TERMINOS
 *  Registros: filas de la tabla  / lineas del archivo csv / nodos de una lista
 *  Campos: titulo o nombre que representa las columnas de la tabla 
*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Metodos para la facturacion
void cargarListaFacturar(mediciones **facturar, facturas *lFacturas, mediciones *lMediciones);
void mostrarPeriodosDisponibles(mediciones *lFacturar);
void seleccionarPeriodoFacturacion(mediciones *lMediciones, costos *lCostos, facturas **lFacturas);
void facturar(int periodo, mediciones **lFacturar, facturas **lFacturas, mediciones *lMediciones, costos *costos);

// Metodos para calcular datos especificos
double determinarTotalAPagar(double buscar, costos *lista);
double calcularConsumo(int buscarCuenta, int periodoActual, mediciones *rc);
int calcularPeriodoAnterior(int periodoActual);

// Metodos de control
int controlarFacturacion(mediciones *buscar, facturas *rc);
int controlarListadoFacturar(mediciones *buscar, mediciones *rc);
int controlarMesFacturar(int buscarPeriodo, mediciones *rc);

/**
 * @brief Se encarga de la facturacion que corresponde con un periodo en especifico, 
 * para ello realiza las siguientes funciones:
 *      1. Recorre la lista de mediciones a facturar buscando el periodo a facturar
 *      2. Si lo encuentra, crea el nodo tipo facturas para todas las mediciones
 *      3. Inserta en la lista de facturas y actualiza el archivo csv de facturas
 *      4. Al final, borra el nodo de la lista de mediciones (medicion ya facturada)
 * @param periodo Entero. Periodo a facturar
 * @param lFacturar Lista de Mediciones a Facturar. Lectura y escritura. 
 * @param lFacturas Lista de Facturas. Lectura y escritura. Para actualizar
 * @param lMediciones Lista de Mediciones. Lectura. Para calcular consumo
 * @param costos Lista de Costos. Lectura. Para determinar total a pagar
 */
void facturar(int periodo, mediciones **lFacturar, facturas **lFacturas, mediciones *lMediciones, costos *costos){
    mediciones *rcFacturar = NULL;  // Auxiliar para la lista de mediciones a facturar
    facturas *nv = NULL;
    //int bandBorrar = 0;
    rcFacturar = (*lFacturar);

    char nameFileFacturas[] = "Facturas.csv";
    int mes;

    // Recorremos la lista de mediciones a facturar
    while (rcFacturar != NULL){
        // Convertimos el periodo de rcFacturar "202305" a "5" para comparar solo el mes
        mes = rcFacturar->periodo % 100;

        // Si encontramos el periodo creamos el nodo
        if (periodo == mes){
            nv = (facturas *) malloc(sizeof(facturas));
            if (nv != NULL){
                nv->idCuenta = rcFacturar->idCuenta;
                nv->periodo = rcFacturar->periodo;
                nv->fechaEmision = obtenerFechaEnEntero();

                nv->consumo = calcularConsumo(rcFacturar->idCuenta, rcFacturar->periodo, lMediciones);

                nv->totalAPagar = determinarTotalAPagar(nv->consumo, costos);
                nv->pagado = 0;
                nv->sgte = NULL;


                if (nv->consumo != 0 && nv->totalAPagar != 0){
                    // Actualizar el archivo
                    escribirDatosCSVFacturas(nameFileFacturas, "a", nv);   // Copia de seguridad o respaldo

                    //Insertar en la lista de facturas
                    insertarFacturasLES(nv, &(*lFacturas));
                } else {
                    printf("No se ha podido realizar la factura de la cuenta %d y periodo %d\n", nv->idCuenta, nv->periodo);
                    free(nv);
                }
                //bandBorrar = 1;
            }else mostrarMensaje(404);
        }
        rcFacturar = rcFacturar->sgte;

        // Borramos nodo (medicion ya facturada) de la lista mediciones a facturar (lFacturar) 
        /*if (bandBorrar == 1){
            freeMedicionLDE(nv->idCuenta, nv->periodo, &(*lFacturar));
            bandBorrar = 0;
        }*/
        
        nv = NULL;
    }
    free(nv);
}

/**
 * @brief Cargamos la lista de mediciones a facturar, siempre y cuando ya no este en la lista 
 * de facturas realizadas y ni en esta misma lista de facturas a realizar
 * 
 * @param facturar Lista a cargar con mediciones a facturar (vacio al inicio), para escritura
 * @param lFacturas Lista de Facturas, para lectura 
 * @param lMediciones Lista de mediciones, para lectura 
 */
void cargarListaFacturar(mediciones **facturar, facturas *lFacturas, mediciones *lMediciones){
    mediciones *nv = NULL; 
 
    int controlFacturacion = 0;     // Nos indica si la medicion se encuntra ya facturada 
    int controlListadoFacturar = 0; // Nos indica si la medicion se encontra ya en el listado para facturacion

    /* Recorrer lista de mediciones y guardar en una nueva lista los nodos que hayan pasado
    todos los controles. */
    while(lMediciones != NULL){
        controlFacturacion = controlarFacturacion(lMediciones, lFacturas);
        if (controlFacturacion == 0){ 
            controlListadoFacturar = controlarListadoFacturar(lMediciones, (*facturar)); 
        }
        
        if (controlFacturacion == 0 && controlListadoFacturar == 0){ 
            nv = (mediciones *) malloc(sizeof(mediciones));
            if (nv != NULL){
                nv->idCuenta = lMediciones->idCuenta;
                nv->periodo = lMediciones->periodo;
                nv->lectura = lMediciones->lectura;
                nv->fechaLectura = lMediciones->fechaLectura;
                nv->ant = NULL;
                nv->sgte = NULL;
                insertarMedicionesLDE(nv, &(*facturar));
            } else mostrarMensaje(404);
        }

        controlFacturacion = 0;         
        controlListadoFacturar = 0;
        lMediciones = lMediciones->sgte;
    }
}

/**
 * @brief Mostrar las opciones de meses que estan disponibles segun la lista de mediciones
 * a facturar.
 * 
 * @param lFacturar Lista de mediciones a facturar, solo lectura
 */
void mostrarPeriodosDisponibles(mediciones *lFacturar){
    system("cls");
    char fechaActual[11];
    int i = 0;
    int mes = 0;
    int controlMesFacturar = 0; // Indica si el mes, se encuentra en la lista de mediciones a facturar
    char *meses[12] = {"1. Enero", "2. Febrero", "3. Marzo", "4. Abril", "5. Mayo", "6. Junio", 
    "7. Julio", "8. Agosto", "9. Septiembre", "10. Octubre", "11. Noviembre", "12. Diciembre"};

    // Mostrar la fecha actual
    obtenerFecha("%Y/%m/%d", fechaActual);
    printf("Fecha Actual: %s\n", fechaActual);
    printf("\n");
    printf("============================================================================================================================================\n");
    printf("                                                         MENU DE FACTURACION\n");
    printf("============================================================================================================================================\n");
    printf("\n");

    // Mostrar las opciones de meses disponibles para facturar
    printf("\n======= MESES DISPONIBLES =======\n");
    for (i=0; i<12; i++){
        mes = i + 1;    // Para buscar el mes correctamente incrementamos i
        controlMesFacturar = controlarMesFacturar(mes, lFacturar);

        // Si se encuentra el mes entonces esta disponible
        if (controlMesFacturar == 1){
            printf("%s\n",meses[i]);
        }else{
            printf("%s >> NO DISPONIBLE\n",meses[i]);
        }
        controlMesFacturar = 0;
    }
    printf("0. SALIR\n");
    printf("================================\n");
}

/**
 * @brief Funcion principal que se encarga de controlar la facturacion.
 *      1. Carga lista de mediciones
 *      2. Muestra los periodos disponibles para facturar
 *      3. Control de periodo y generar factura (carga archivo csv y lista de facturas)
 * @param lMediciones Lista de mediciones, para lectura
 * @param lCostos Lista de costos, para lectura
 * @param lFacturas Lista de facturas, para lectura y escritura
 */
void seleccionarPeriodoFacturacion(mediciones *lMediciones, costos *lCostos, facturas **lFacturas){
    int opcion;
    int valueEnd = 0;
    int ErrorNoNumeric = 0;
    int controlMesFacturar = 0;

    mediciones *listaFacturar = NULL;
    
    // FeedBack con el usuario
    do {
        if (listaFacturar != NULL) freeMedicionesLDE(&listaFacturar);

        // Cargar la lista con mediciones a facturar
        cargarListaFacturar(&listaFacturar, (*lFacturas), lMediciones); 
        
        if (listaFacturar != NULL){
            // Mostrar las opciones al usuario, con los periodos disponibles
            mostrarPeriodosDisponibles(listaFacturar);

            valueEnd = 0;
            ErrorNoNumeric = 0;
            
            printf("Ingrese el numero del mes, entre los disponibles: ");
            while(valueEnd == 0){
                fflush(stdin);
                if (scanf("%d", &opcion) != 1) ErrorNoNumeric = 1;
                if (opcion < 0 || ErrorNoNumeric == 1 || opcion > 12 ){
                    if (ErrorNoNumeric == 1) mostrarMensajeError(1);    // Error Caracter ingresado
                    if (opcion < 0) mostrarMensajeError(2);             // Error Numero ingresado < 0
                    ErrorNoNumeric = 0;
                    mostrarPeriodosDisponibles(listaFacturar);
                    printf ("ERROR: Ingrese nuevamente una opcion: ");
                }else{
                    valueEnd = 1;
                    if (opcion == 0) printf("Saliendo... :(\n");    // No es necesario
                }   
            }

            // Controlamos la opcion seleccionada
            if (opcion > 0 && opcion < 13){
                controlMesFacturar = controlarMesFacturar(opcion, listaFacturar);
                if (controlMesFacturar == 1){
                    // Facturar. Escribir en archivo de facturas y lista de archivos
                    printf("Facturando...\n");
                    facturar(opcion, &listaFacturar, &(*lFacturas), lMediciones, lCostos);
                }else{
                    printf("Opcion no disponible. Por favor, seleccione una opcion disponible.\n");
                }
            }else{
                if (opcion != 0) printf("Opcion invalida. Por favor, seleccione una opcion valida.\n");
            }    
        }else{
            printf("No hay mediciones para facturar.!! :(\n"); opcion = 0;
        }

        system("pause");
    } while (opcion != 0);
}


/**
 * @brief Su funcion es determinar el total a pagar, buscando la lectura recibida como 
 * parametro en la lista de costos.
 * No se encontrara esta lectura concreta en la lista sino dentro de un rango. 
 * 
 * @param buscar Lectura o cantidad de metros cubicos que buscamos en la lista 
 * @param lista Lista donde se realizara la busqueda (Costos)
 * @return double Total a pagar, que se mostrara en la factura
 */
double determinarTotalAPagar(double buscar, costos *lista){
    double resultado = 0;
    while (lista != NULL){
        if ((buscar >= lista->mtsDesde) && (buscar <= lista->mtsHasta)){
            resultado = lista->valorMetro;
            lista = NULL;
        }
        if (lista != NULL) lista = lista->sgte;
    }
    if (resultado == 0) printf("No se ha podido calcular el total a pagar.!\n");

    return resultado;
}

/**
 * @brief Calcular el consumo para la facturacion que corresponde con el id de una 
 * cuenta en especifico. Para ello, buscamos el periodo anterior en la lista de mediciones 
 * para obtener el consumo del mes anterior y poder calcular el actual.
 * Calcular el consumo solo si el periodo actual es distinto de 1 (enero)
 * 
 * @param buscarCuenta Id de la cuenta a buscar 
 * @param periodoActual Periodo Actual, necesario para encontrar el periodo anterior
 * @param rc Lista de mediciones para buscar el periodo anterior
 * @return double Retorna el resultado final (consumo para la facturacion)
 */
double calcularConsumo(int buscarCuenta, int periodoActual, mediciones *rc){
    double resultado = 0;
    double lecturaAnterior = 0;
    double lecturaActual = 0;
    int periodoAnterior = calcularPeriodoAnterior(periodoActual);

    // Buscar el lectura que corresponde con el periodo anterior
    while (rc != NULL && (lecturaAnterior == 0 || lecturaActual == 0)){
        if (buscarCuenta == rc->idCuenta){
            if (periodoAnterior == rc->periodo && lecturaAnterior == 0){
                lecturaAnterior = rc->lectura;
            }
            if (periodoActual == rc->periodo && lecturaActual == 0){
                lecturaActual = rc->lectura;
            }
        }
        rc = rc->sgte;
    }

    // Calcular el consumo actual
    if (lecturaAnterior != 0 && lecturaActual != 0){
        resultado = lecturaActual - lecturaAnterior;
    }

    if (lecturaAnterior == 0) printf ("No se ha encontrado el periodo anterior %d.!\n", periodoAnterior);
    if (lecturaActual == 0) printf ("No se ha encontrado el periodo actual %d.!\n", periodoActual); 

    return resultado;
}

/**
 * @brief Calcula el periodo anterior, teniendo en cuenta el periodo actual
 * 
 * @param periodoActual Entero. Periodo Actual "202305"
 * @return int Retorna entero con Periodo Anterior "202304"
 */
int calcularPeriodoAnterior(int periodoActual){
    // Extraer el año y el mes
    int anio = periodoActual / 100;
    int mes = periodoActual % 100;
    
    // Calcular el mes anterior
    if (mes == 1) {     // Si el mes es enero se debe restar el año
        anio--;
        mes = 12;
    } else mes--;
    
    // Formatear el año y el mes en formato "YYYYMM"
    int periodoAnterior = (anio * 100) + mes;

    return periodoAnterior;
}

/**
 * @brief Buscar un periodo especifico y informar si se encuentra en lista de mediciones
 * a facturar.
 * 
 * @param buscarPeriodo Entero del Mes o periodo a buscar
 * @param rc Puntero a la lista de mediciones a facturar
 * @return int Devuelve un 1 si se encuentra, sino 0
 */
int controlarMesFacturar(int buscarPeriodo, mediciones *rc){
    int resultado = 0;
    int mes;
    
    while (rc != NULL && resultado == 0){
        // Convertir el periodo "202305" a  "5"
        mes = rc->periodo % 100;

        // Comparamos si el mes de la lista de mediciones es igual al buscado
        if (mes == buscarPeriodo){
            resultado = 1;
        }
        rc = rc->sgte;
    }

    return resultado;
}

/**
 * @brief Buscar una medicion especifica y informar si se encuentra en lista de mediciones
 * a facturar.
 * Controlamos el idCuenta y periodo de mediciones con las facturas
 * 
 * @param buscar Nodo de medicion a buscar
 * @param rc Puntero a la lista de mediciones a facturar
 * @return int Devuelve un 1 si se encuentra, sino 0
 */
int controlarListadoFacturar(mediciones *buscar, mediciones *rc){
    int resultado = 0;
    
    while (rc != NULL && resultado == 0){
        if (rc->idCuenta == buscar->idCuenta){
            if (rc->periodo == buscar->periodo){
                resultado = 1;
            }
        }
        rc = rc->sgte;
    }

    return resultado;
}

/**
 * @brief Buscar una factura especifica y informar si se encuentra en lista de facturas
 * Controlamos el idCuenta y periodo de mediciones con las facturas
 * 
 * @param buscar Nodo de medicion a buscar
 * @param rc Puntero a la lista de facturas, para lectura
 * @return int Devuelve un 1 si se encuentra, sino 0
 */
int controlarFacturacion(mediciones *buscar, facturas *rc){
    int resultado = 0;
    
    while (rc != NULL && resultado == 0){
        if (rc->idCuenta == buscar->idCuenta){
            if (rc->periodo == buscar->periodo){
                resultado = 1;
            }
        }
        rc = rc->sgte;
    }

    return resultado;
}

#endif

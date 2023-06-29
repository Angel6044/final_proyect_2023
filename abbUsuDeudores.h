/*
    1. Identificar a los usuarios deudores de un mes, con la lista de facturas
    2. Buscar al usuario en la lista de usuarios, con el id de cuenta accedemos al MedXUsu
        ahi obtenemos el id del usuario
    3. Insertar los nodos de los usuarios ordenada por apellido y nombre
*/

void crearAbbUsuariosDeudores(usuariosDeudores **abbUsuDeudores, MedxUsu *lMedxUsu, usuarios *lUsuarios, facturas *lFacturas, int mes);
int buscarIdUsuario(int idCuenta, MedxUsu *lMedxUsu);
usuarios * buscarUsuario(int idUsuario, usuarios *lUsuarios);
void insertarArbolUsuOrdenado(char *apellidoBuscar, char *nombreBuscar, usuariosDeudores *nv, usuariosDeudores **raiz);

void mostrarMesesDisponibles(facturas *lFacturas);
void seleccionarMesGenerarABB(usuariosDeudores **abbUsuDeudores, MedxUsu *lMedxUsu, usuarios *lUsuarios, facturas *lFacturas);

int controlarMesUsuDeudor(int mesBuscar, facturas *rc);
void separarApellidoNombre(const char *apellidoNombre, char *apellido, char *nombre);

void mostrarArbolUsuarios(usuariosDeudores *abbUsuarios);
void limpiarArbol(usuariosDeudores **raiz);


/* :::::::::::::::::::::::::::::::::::::::::: FUNCIONES :::::::::::::::::::::::::::::::::::::::::: */

/**
 * @brief Recorre la lista de facturas, buscando aquellas facturas que no esten pagadas y con el 
 * id de la cuenta busca en la lista de MedxUsu el id del usuario. 
 * Luego con el id del usuario, busca al usuario en lista de usuarios.
 * Una vez que lo encuentre, crea el nodo para insertarlo en el arbol.
 * 
 * @param abbUsuDeudores 
 * @param lMedxUsu 
 * @param lUsuarios 
 * @param lFacturas 
 * @param mes 
 */
void crearAbbUsuariosDeudores(usuariosDeudores **abbUsuDeudores, MedxUsu *lMedxUsu, usuarios *lUsuarios, facturas *lFacturas, int mes){
    usuarios *usuario = NULL;
    usuariosDeudores *nv = NULL;

    int mesActual;
    int idUsuario = 0;

    char apellido[50];
    char nombre[50];

    // Recorrer la lista de facturas y buscar el mes
    while (lFacturas != NULL){
        mesActual = lFacturas->periodo % 100;

        limpiarCadena(apellido, sizeof(apellido));
        limpiarCadena(nombre, sizeof(nombre));
        
        // El mes es el seleccionado por el usuario y mesActual del bucle
        if (mesActual == mes){
            if (lFacturas->pagado == 0){  
                idUsuario = buscarIdUsuario(lFacturas->idCuenta, lMedxUsu);

                if (idUsuario != 0){  
                    usuario = buscarUsuario(idUsuario, lUsuarios); 

                    if (usuario != NULL){  
                        // Creamos el nodo usuarios deudores e insertamos en el abb
                        nv = (usuariosDeudores *) malloc(sizeof(usuariosDeudores)); 
                        if (nv != NULL){ 
                            strcpy(nv->apellidoNombre, usuario->apellidoNombre);
                            nv->idUsuario = usuario->idUsuario;
                            nv->fechaAlta = usuario->fechaAlta;
                            nv->izq = NULL;
                            nv->der = NULL;

                            separarApellidoNombre(nv->apellidoNombre, apellido, nombre);

                            insertarArbolUsuOrdenado(apellido, nombre, nv, &(*abbUsuDeudores)); 

                            nv = NULL;
                        }else mostrarMensaje(404);

                        usuario = NULL;
                    }else{
                        printf("No se encontro al usuario.!\n");
                    }
                }else{
                    printf("No se encontro el id del usuario.!\n");
                }
            }

            mesActual = 0;
        }
        
        lFacturas = lFacturas->sgte;    
    }
}

void limpiarArbol(usuariosDeudores **raiz){
    if (*raiz != NULL){
        limpiarArbol(&(*raiz)->izq);
        limpiarArbol(&(*raiz)->der);
        free(*raiz);
        (*raiz) = NULL;
    }
}

/**
 * @brief Busca el id del usuario, con el id de la cuenta, en la lista de Medidores x Usuarios
 * 
 * @param idCuenta Entero. Id de la cuenta a buscar
 * @param lMedxUsu Lista de Medidores x Usuarios. Lectura
 * @return int Retorna 1 si lo encuentra, 0 si no.
 */
int buscarIdUsuario(int idCuenta, MedxUsu *lMedxUsu){
    int idUsuario = 0;

    if (lMedxUsu == NULL) mostrarMensaje(7);
    while (lMedxUsu != NULL){
        if (lMedxUsu->idCuenta == idCuenta){
            idUsuario = lMedxUsu->idUsuario;
        }
        lMedxUsu = lMedxUsu->sgte;
    }

    return idUsuario;
}

/**
 * @brief Busca a un usuario especifico, con el id del usuario, en la lista de usuarios
 * 
 * @param idUsuario Entero. Id del usuario
 * @param lUsuarios Lista de Usuarios. Lectura
 * @return usuarios* Retorna la posicion del nodo usuario buscado. NULL si no lo encuentra.
 */
usuarios * buscarUsuario(int idUsuario, usuarios *lUsuarios){
    usuarios *usuario = NULL;

    if (lUsuarios == NULL) mostrarMensaje(7);
    while (lUsuarios != NULL){
        if (lUsuarios->idUsuario == idUsuario){
            usuario = lUsuarios;
        }
        lUsuarios = lUsuarios->sgte;
    }

    return usuario;
}

/**
 * @brief Insertar usuarios deudores, en el arbol ordenado por apellido y nombre
 * 
 * @param apellidoBuscar Char. Apellido del nuevo nodo, para comparar
 * @param nombreBuscar Char. Nombre del nuevo nodo, para comparar
 * @param nv Nuevo nodo usuario
 * @param abbUsuDeudores Puntero Arbol Binario Busqueda. Lectura y escritura
 */
void insertarArbolUsuOrdenado(char *apellidoBuscar, char *nombreBuscar, usuariosDeudores *nv, usuariosDeudores **raiz){
    if ((*raiz) == NULL){
        (*raiz) = nv;
    }else{
        char apellido[50];
        char nombre[50];
        int comparacion;

        separarApellidoNombre((*raiz)->apellidoNombre, apellido, nombre); 

        comparacion = strcmp(apellidoBuscar, apellido);

        if (comparacion < 0){
            insertarArbolUsuOrdenado(apellidoBuscar, nombreBuscar, nv, &(*raiz)->izq);
        }else{
            if (comparacion > 0){
                insertarArbolUsuOrdenado(apellidoBuscar, nombreBuscar, nv, &(*raiz)->der);
            }else{
                comparacion = strcmp(nombreBuscar, nombre);

                if (comparacion < 0){
                    insertarArbolUsuOrdenado(apellidoBuscar, nombreBuscar, nv, &(*raiz)->izq);
                }else{
                    if (comparacion > 0){
                        insertarArbolUsuOrdenado(apellidoBuscar, nombreBuscar, nv, &(*raiz)->der);
                    }
                }
            }
        } 
    }
}


/**
 * @brief Mostrar el abb de usuarios deudores
 * 
 * @param abbUsuarios Puntero ABB Usuarios Deudores
 */
void mostrarArbolUsuarios(usuariosDeudores *abbUsuarios){
    if (abbUsuarios != NULL){
        mostrarArbolUsuarios (abbUsuarios->izq);
        printf(">> Id Usuario: %d | Apellido y Nombre: %s | Fecha Alta: %d\n",abbUsuarios->idUsuario, abbUsuarios->apellidoNombre, abbUsuarios->fechaAlta);
        mostrarArbolUsuarios (abbUsuarios->der);
    }
}

/**
 * @brief Permite al usuario elegir el mes especifico, para generar el abb de usuarios deudores
 * 
 * @param abbUsuDeudores Puntero Arbol Binario de Busqueda. Lectura y Escritura
 * @param lMedxUsu Lista de Medidores x Usuarios. Lectura
 * @param lUsuarios Lista de Usuarios. Lectura
 * @param lFacturas Lista de Facturas. Lectura
 */
void seleccionarMesGenerarABB(usuariosDeudores **abbUsuDeudores, MedxUsu *lMedxUsu, usuarios *lUsuarios, facturas *lFacturas){
    int opcion;
    int valueEnd = 0;
    int ErrorNoNumeric = 0;
    int controlMesUsuDeudores = 0;
    
    // FeedBack con el usuario
    do {
        // Mostrar las opciones al usuario, con los periodos disponibles
        mostrarMesesDisponibles(lFacturas);

        valueEnd = 0;
        ErrorNoNumeric = 0;
        
        printf("Ingrese el numero del mes, entre los disponibles: ");
        while(valueEnd == 0){
            fflush(stdin);
            if (scanf("%d", &opcion) != 1) ErrorNoNumeric = 1;
            if ((opcion < 0 || ErrorNoNumeric == 1) && opcion > 12 ){
                if (ErrorNoNumeric == 1) mostrarMensajeError(1);    // Error Caracter ingresado
                if (opcion < 0) mostrarMensajeError(2);             // Error Numero ingresado < 0
                ErrorNoNumeric = 0;
                mostrarMesesDisponibles(lFacturas);
                printf ("ERROR: Ingrese nuevamente una opcion: ");
            }else{
                valueEnd = 1;
                if (opcion == 0) printf("Saliendo... :(\n");    // No es necesario
            }   
        }

        // Controlamos la opcion seleccionada
        if (opcion > 0 && opcion < 13){
            controlMesUsuDeudores = controlarMesUsuDeudor(opcion, lFacturas);   // Si existe algun usuario deudor retorna 1.         
            if (controlMesUsuDeudores == 1){
                crearAbbUsuariosDeudores(&(*abbUsuDeudores), lMedxUsu, lUsuarios, lFacturas, opcion);
                if ((*abbUsuDeudores) != NULL){
                    // Imprimir el arbol creado
                    printf("\n");
                    mostrarArbolUsuarios(*abbUsuDeudores);
                    printf("\n");

                    // Limpiar Arbol
                    limpiarArbol(&(*abbUsuDeudores));

                }else printf("Error al intentar crear el arbol.! \n");
            
            } else printf("No hay usuarios deudores en el mes seleccionado.! \n");
        }else{
            if (opcion != 0) printf("Opcion invalida. Por favor, seleccione una opcion valida.\n");
        } 

        system("pause");
        
    } while (opcion != 0);
}

/**
 * @brief Muestra todas las opciones de meses donde existan usuarios deudores
 * 
 * @param lFacturas Lista de facturas. Control de usuario deudor. Lectura
 */
void mostrarMesesDisponibles(facturas *lFacturas){
    system("cls");
    char fechaActual[11];
    int i = 0;
    int mes = 0;
    int controlMesUsuDeudor = 0; // Indica si el mes, se encuentra en la lista de mediciones a facturar
    char *meses[12] = {"1. Enero", "2. Febrero", "3. Marzo", "4. Abril", "5. Mayo", "6. Junio", 
    "7. Julio", "8. Agosto", "9. Septiembre", "10. Octubre", "11. Noviembre", "12. Diciembre"};

    // Mostrar la fecha actual
    obtenerFecha("%Y/%m/%d", fechaActual);
    printf("Fecha Actual: %s\n", fechaActual);
    printf("\n");
    printf("============================================================================================================================================\n");
    printf("                                                  MENU CREACION DE ABB PARA USUARIOS DEUDORES\n");
    printf("============================================================================================================================================\n");
    printf("\n");

    // Mostrar las opciones de meses disponibles para facturar
    printf("\n======= MESES DISPONIBLES =======\n");
    for (i=0; i<12; i++){
        mes = i + 1;    // Para buscar el mes correctamente incrementamos i
        controlMesUsuDeudor = controlarMesUsuDeudor(mes, lFacturas);

        // Si se encuentra el mes entonces esta disponible
        if (controlMesUsuDeudor == 1){
            printf("%s\n",meses[i]);
        }else{
            printf("%s >> NO DISPONIBLE\n",meses[i]);
        }
        controlMesUsuDeudor = 0;
    }
    printf("0. SALIR\n");
    printf("================================\n");
}

/**
 * @brief Controla si existen usuarios deudores en un mes especifico
 * 
 * @param mesBuscar Entero, mes a buscar 
 * @param rc Lista de facturas, para saber si adeuda. Lectura
 * @return int Retorna 1 si encuentra alguno, 0 sino
 */
int controlarMesUsuDeudor(int mesBuscar, facturas *rc){
    int resultado = 0;
    int mes;
    
    while (rc != NULL && resultado == 0){
        // Convertir el periodo "202305" a  "5"
        mes = rc->periodo % 100;

        // Comparamos si el mes de la lista de mediciones es igual al buscado
        if (mes == mesBuscar){
            if (rc->pagado == 0){
                resultado = 1;
            }
        }
        rc = rc->sgte;
    }

    return resultado;
}

/**
 * @brief Separa el apellido y el nombre de una cadena de caracteres.
 * Lo utilizamos para poder ordenar el abb de usuarios deudores.
 * 
 * @param apellidoNombre Cadena con apellido y nombre
 * @param apellido Cadena con apellido
 * @param nombre Cadena con nombre
 */
void separarApellidoNombre(const char *apellidoNombre, char *apellido, char *nombre) {
    char copia[60];
    strcpy(copia, apellidoNombre);

    char *token = strtok(copia, " ");
    if (token != NULL) {
        strcpy(apellido, token);
        token = strtok(NULL, " ");
        if (token != NULL) {
            strcpy(nombre, token);
        } else {
            nombre[0] = '\0';  // Si no se encuentra el nombre, asignar una cadena vacía
        }
    } else {
        apellido[0] = '\0';  // Si no se encuentra el apellido, asignar una cadena vacía
        nombre[0] = '\0';    // Si no se encuentra el nombre, asignar una cadena vacía
    }
}
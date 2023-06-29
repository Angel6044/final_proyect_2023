#ifndef FUNCTIONS_LISTAS_H
#define FUNCTIONS_LISTAS_H

void insertarCostosLES(costos *nv, costos **ini);
costos * buscarAnteriorCostosLES(int buscar, costos *rc);
void mostrarCostosLES(costos *rc);
void freeCostosLES(costos **rc);

void insertarFacturasLES(facturas *nv, facturas **ini);
facturas * buscarAnteriorFacturasLES(int buscar, facturas *rc);
void mostrarFacturasLES(facturas *rc);
void freeFacturasLES(facturas **rc);

void insertarMedicionesLDE(mediciones *nv, mediciones **ini);
mediciones * buscarAnteriorMedicionesLDE(int buscar, mediciones *rc);
void mostrarMedicionesLDE(mediciones *rc);
void freeMedicionesLDE(mediciones **rc);
mediciones * buscarAnteriorMedicionLDE(int idBuscar, int periodoBuscar, mediciones *rc);
void freeMedicionLDE(int idBuscar, int periodoBuscar, mediciones **rc);

void insertarMedxUsuLES(MedxUsu *nv, MedxUsu **ini);
MedxUsu * buscarAnteriorMedxUsuLES(int buscar, MedxUsu *rc);
void mostrarMedxUsuLES(MedxUsu *rc);
void freeMedxUsuLES(MedxUsu **rc);

void insertarUsuariosLES(usuarios *nv, usuarios **ini);
usuarios * buscarAnteriorUsuariosLES(int buscar, usuarios *rc);
void mostrarUsuariosLES(usuarios *rc);
void freeUsuariosLES(usuarios **rc);

void insertarMedidorLEC(medidores *nv, medidores **ini);
medidores * buscarAnteriorMedidorLEC(int buscar, medidores **rc);
void mostrarMedidoresLEC(medidores *rc);
void freeMedidoresLEC(medidores **rc);

void freeAllLists(usuarios **l1, medidores **l2, MedxUsu **l3, mediciones **l4, facturas **l5, costos **l6);
void showAllLists(usuarios *l1, medidores *l2, MedxUsu *l3, mediciones *l4, facturas *l5, costos *l6);

/*
	::::::::::::::::::::::::::::::::::: ALL :::::::::::::::::::::::::::::::::::
*/

/**
 * @brief Su funcion es liberar el espacio en memoria de todos los punteros que se 
 * utilizaron para direccionar a las listas del sistema.  
 * 
 * @param l1 lista de Usuarios 
 * @param l2 lista de Medidores
 * @param l3 lista de Medidores x Usuario
 * @param l4 lista de Mediciones
 * @param l5 lista de Facturas
 * @param l6 lista de Costos
 */
void freeAllLists(usuarios **l1, medidores **l2, MedxUsu **l3, mediciones **l4, facturas **l5, costos **l6){
    if ((*l1) == NULL && (*l2) == NULL && (*l3) == NULL && (*l4) == NULL && (*l5) == NULL && (*l6) == NULL)
        printf ("Memoria no utilizada, no es necesario liberar.! :)\n");
    else{
        if ((*l1) != NULL) freeUsuariosLES(&(*l1));
        if ((*l2) != NULL) freeMedidoresLEC(&(*l2));
        if ((*l3) != NULL) freeMedxUsuLES(&(*l3));
        if ((*l4) != NULL) freeMedicionesLDE(&(*l4));
        if ((*l5) != NULL) freeFacturasLES(&(*l5));
        if ((*l6) != NULL) freeCostosLES(&(*l6));
    }
}

/**
 * @brief Mostrar todas las listas
 * 
 * @param l1 lista de Usuarios 
 * @param l2 lista de Medidores
 * @param l3 lista de Medidores x Usuario
 * @param l4 lista de Mediciones
 * @param l5 lista de Facturas
 * @param l6 lista de Costos
 */
void showAllLists(usuarios *l1, medidores *l2, MedxUsu *l3, mediciones *l4, facturas *l5, costos *l6){
    if (l1 != NULL || l2 != NULL || l3 != NULL || l4 != NULL || l5 != NULL || l6 != NULL){
        system("cls");
        printf("\nIMPRIMIENDO LISTA DE USUARIOS...\n"); pause(1);
        mostrarUsuariosLES(l1);
        printf("\nIMPRIMIENDO LISTA DE MEDIDORES...\n"); pause(1);
        mostrarMedidoresLEC(l2);
        printf("\nIMPRIMIENDO LISTA DE MEDIDORESxUSUARIOS...\n"); pause(1);
        mostrarMedxUsuLES(l3);
        printf("\nIMPRIMIENDO LISTA DE MEDICIONES...\n"); pause(1);
        mostrarMedicionesLDE(l4);
        printf("\nIMPRIMIENDO LISTA DE FACTURAS...\n"); pause(1);
        mostrarFacturasLES(l5);
        printf("\nIMPRIMIENDO LISTA DE COSTOS...\n\n"); pause(1);
        mostrarCostosLES(l6);
        mostrarMensaje(1);
    }else printf("\nTodas las listas estan vacias.! :(\n");
}

/*
	::::::::::::::::::::::: UTILIDADES PARA LES COSTOS :::::::::::::::::::::::::::
*/

costos * buscarAnteriorCostosLES(int buscar, costos *rc) {
    costos *ant = rc;

    // Buscamos el anterior, realizando recorrido con rc  
    while(rc != NULL) {   // buscamos el ultimo nodo con rc
        if (rc->idCostos > buscar){
            rc = NULL;
        }else{
            ant = rc;
            rc = rc->sgte;
        }
    }
    return ant;
}

void insertarCostosLES(costos *nv, costos **ini) {
    costos *ant = NULL;

    if ((*ini) == NULL){
        (*ini) = nv;
    }else{
        int numNV = nv->idCostos;     // Dato del nuevo nodo
        int numIni = (*ini)->idCostos;   // Dato de la lista original
        
        if(numNV < numIni) {
            nv->sgte = (*ini)->sgte;
            (*ini) = nv;
        }else{
            ant = buscarAnteriorCostosLES(numNV, (*ini));
            nv->sgte = ant->sgte;
            ant->sgte = nv;
        }
    }
    ant = NULL;
    nv = NULL;
}

void mostrarCostosLES(costos *rc){
    int i = 1;

    while (rc != NULL){
        printf(">> Costo: #%d | Id Costos: %d | Metros Desde: %d | Metros Hasta: %d | Valor Metro: %d\n", i, rc->idCostos, rc->mtsDesde, rc->mtsHasta, rc->valorMetro);
        rc = rc->sgte;
        i++;
    }
    if (rc == NULL) mostrarMensaje(7);
}

void freeCostosLES(costos **rc){
    costos *aux = NULL;
    while ((*rc) != NULL){
        aux = (*rc)->sgte;
        free((*rc));
        (*rc) = aux;
    }
    free((*rc));
    printf("Lista de Costos liberada correctamente.. :)\n");
}

/*
	::::::::::::::::::::::: UTILIDADES PARA LES FACTURAS :::::::::::::::::::::::::::
*/

facturas * buscarAnteriorFacturasLES(int buscar, facturas *rc){
    facturas *ant = NULL;

    // Buscamos el anterior, realizando recorrido con rc  
    while(rc != NULL) {   // buscamos el ultimo nodo con rc
        if (rc->idCuenta > buscar){
            rc = NULL;
        }else{
            ant = rc;
            rc = rc->sgte;
        }
    }
    return ant;
}

void insertarFacturasLES(facturas *nv, facturas **ini) {
    facturas *ant = NULL;

    if ((*ini) == NULL){
        (*ini) = nv;
    }else{
        int numNV = nv->idCuenta;     // Dato del nuevo nodo
        int numIni = (*ini)->idCuenta;   // Dato de la lista original
        
        if(numNV < numIni) {
            nv->sgte = (*ini)->sgte;
            (*ini) = nv;
        }else{
            ant = buscarAnteriorFacturasLES(numNV, (*ini));
            nv->sgte = ant->sgte;
            ant->sgte = nv;
        }
    }
    ant = NULL;
    nv = NULL;
}

void mostrarFacturasLES(facturas *rc){
    int i = 1;

    while (rc != NULL){
        printf(">> Factura: #%d | Id Cuenta: %d | Periodo: %d | Fecha Emision: %d | Consumo: %.2f | Total a Pagar: %.2f | Pagado: %d\n", i, rc->idCuenta, rc->periodo, rc->fechaEmision, rc->consumo, rc->totalAPagar, rc->pagado);
        rc = rc->sgte;
        i++;
    }
    if (rc == NULL) mostrarMensaje(7);
}

void freeFacturasLES(facturas **rc){
    facturas *aux = NULL;
    while ((*rc) != NULL){
        aux = (*rc);
        (*rc) = (*rc)->sgte;
        aux->sgte = NULL;
        free(aux);
    }
    printf("Lista de Facturas liberada correctamente.. :)\n");
}

/*
	::::::::::::::::::::::: UTILIDADES PARA LDE MEDICIONES :::::::::::::::::::::::::::
*/

mediciones * buscarAnteriorMedicionesLDE(int buscar, mediciones *rc) {
    mediciones *ant = NULL;

    // Buscamos el anterior, realizando recorrido con rc  
    while(rc != NULL) {   // buscamos el ultimo nodo con rc
        if (rc->idCuenta > buscar){
            rc = NULL;
        }else{
            ant = rc;
            rc = rc->sgte;
        }
    }
    return ant;
}

void insertarMedicionesLDE(mediciones *nv, mediciones **ini) {
    mediciones *anterior = NULL;

    if ((*ini) == NULL){
        (*ini) = nv;
    }else{
        int numNV = nv->idCuenta;     // Dato del nuevo nodo
        int numIni = (*ini)->idCuenta;   // Dato de la lista original
        
        if(numNV < numIni) {
            nv->sgte = (*ini);
            nv->ant = NULL;
            (*ini)->ant = nv;
            (*ini) = nv;
        }else{
            anterior = buscarAnteriorMedicionesLDE(numNV, (*ini));
            nv->sgte = anterior->sgte;
            nv->ant = anterior;
            if (anterior->sgte != NULL) (anterior->sgte)->ant = nv;
            anterior->sgte = nv;
        }
    }
    anterior = NULL;
    nv = NULL;
}

void mostrarMedicionesLDE(mediciones *rc){
    int i = 1;

    while (rc != NULL){
        printf(">> Medicion: #%d | Id Cuenta: %d | Periodo: %d | Fecha de Lectura: %d | Lectura: %.2f\n", i, rc->idCuenta, rc->periodo, rc->fechaLectura, rc->lectura);
        rc = rc->sgte;
        i++;
    }
    if (rc == NULL) mostrarMensaje(7);
}

void freeMedicionesLDE(mediciones **rc){
    mediciones *aux = NULL;
    while ((*rc) != NULL){
        aux = (*rc);
        aux->sgte = NULL;
        aux->ant = NULL;
        (*rc) = (*rc)->sgte;
        free(aux);
    }
    printf("Lista de Mediciones liberada correctamente.. :)\n");
}

/**
 * @brief Se encarga de buscar una medicion (nodo) especifica por id de cuenta y periodo
 * y retornar la posicion del nodo anterior al que buscamos.
 * 
 * @param idBuscar Entero. Id de la cuenta a buscar
 * @param periodoBuscar Entero. Periodo de la medicion a buscar
 * @param rc Lista de mediciones
 * @return mediciones* Posicion del nodo anterior
 */
mediciones * buscarAnteriorMedicionLDE(int idBuscar, int periodoBuscar, mediciones *rc){
    mediciones *ant = NULL;
    int band = 0;

    // Buscamos el anterior, realizando recorrido con rc  
    while(rc != NULL && band == 0) {   // buscamos el ultimo nodo con rc 
        if (idBuscar == rc->idCuenta){
            if (periodoBuscar == rc->periodo){
                band = 1;
            }else{
                // Si rc->sgte es NULL entonces se ha llegado al final y no se encontro
                if (rc->sgte == NULL){
                    ant = NULL;
                } else ant = rc;
            }
        }
        
        rc = rc->sgte;
    }

    return ant;
}

/**
 * @brief Se encarga de buscar una medicion (nodo) especifica por id de cuenta y periodo
 * y borrarlo.
 * 
 * @param idBuscar Entero. Id de la cuenta a buscar
 * @param periodoBuscar Entero. Periodo de la medicion a buscar
 * @param rc Lista de mediciones
 */
void freeMedicionLDE(int idBuscar, int periodoBuscar, mediciones **rc){
    mediciones *anterior = NULL;
    mediciones *borrar = NULL;
    
    if ((*rc) != NULL){
        if ((*rc)->sgte == NULL){
            if (idBuscar == (*rc)->idCuenta && periodoBuscar == (*rc)->periodo){
                borrar = (*rc);
            }
        }else{
            anterior = buscarAnteriorMedicionLDE(idBuscar, periodoBuscar, (*rc));
            if (anterior != NULL){
                borrar = anterior->sgte;
                borrar->sgte->ant = anterior;
                anterior->sgte = borrar->sgte;
                borrar->ant = NULL;
                borrar->sgte = NULL;
            }
        }
    }else mostrarMensaje(7);

    if (borrar != NULL){
        free(borrar); 
        printf("Nodo borrado correctamente.. :)\n");
    }else printf("Nodo a borrar no encontrado.!\n");
}

/*
	::::::::::::::::::::::: UTILIDADES PARA LES MedxUsu :::::::::::::::::::::::::::
*/

MedxUsu * buscarAnteriorMedxUsuLES(int buscar, MedxUsu *rc) {
    MedxUsu *ant = rc;

    // Buscamos el anterior, realizando recorrido con rc  
    while(rc != NULL) {   // buscamos el ultimo nodo con rc
        if (rc->idUsuario > buscar){
            rc = NULL;
        }else{
            ant = rc;
            rc = rc->sgte;
        }
    }
    return ant;
}

void insertarMedxUsuLES(MedxUsu *nv, MedxUsu **ini) {
    MedxUsu *ant = NULL;

    if ((*ini) == NULL){
        (*ini) = nv;
    }else{
        int numNV = nv->idUsuario;     // Dato del nuevo nodo
        int numIni = (*ini)->idUsuario;   // Dato de la lista original
        
        if(numNV < numIni) {
            nv->sgte = (*ini)->sgte;
            (*ini) = nv;
        }else{
            ant = buscarAnteriorMedxUsuLES(numNV, (*ini));
            nv->sgte = ant->sgte;
            ant->sgte = nv;
        }
    }
    ant = NULL;
    nv = NULL;
}

void mostrarMedxUsuLES(MedxUsu *rc){
    int i = 1;

    while (rc != NULL){
        printf(">> MedxUsu: #%d | Id Usuario: %d | Id Medidor: %d | Id Cuenta: %d | Fecha Alta: %d | Fecha Baja: %d\n", i, rc->idUsuario, rc->idMedidor, rc->idCuenta, rc->fechaAlta, rc->fechaBaja);
        rc = rc->sgte;
        i++;
    } 
    if (rc == NULL) mostrarMensaje(7); 
}

void freeMedxUsuLES(MedxUsu **rc){
    MedxUsu *aux = NULL;
    while ((*rc) != NULL){
        aux = (*rc);
        aux->sgte = NULL;
        (*rc) = (*rc)->sgte;
        free(aux);
    }
    printf("Lista de MedxUsu liberada correctamente.. :)\n");
}

/*
	::::::::::::::::::::::: UTILIDADES PARA LES USUARIOS :::::::::::::::::::::::::::
*/

usuarios * buscarAnteriorUsuariosLES(int buscar, usuarios *rc) {
    usuarios *ant = rc;

    // Buscamos el anterior, realizando recorrido con rc  
    while(rc != NULL) {   // buscamos el ultimo nodo con rc
        if (rc->idUsuario > buscar){
            rc = NULL;
        }else{
            ant = rc;
            rc = rc->sgte;
        }
    }
    return ant;
}

void insertarUsuariosLES(usuarios *nv, usuarios **ini) {
    usuarios *ant = NULL;

    if ((*ini) == NULL){
        (*ini) = nv;
    }else{
        int numNV = nv->idUsuario;     // Dato del nuevo nodo
        int numIni = (*ini)->idUsuario;   // Dato de la lista original
        
        if(numNV < numIni) {
            nv->sgte = (*ini)->sgte;
            (*ini) = nv;
        }else{
            ant = buscarAnteriorUsuariosLES(numNV, (*ini));
            nv->sgte = ant->sgte;
            ant->sgte = nv;
        }
    }
    ant = NULL;
    nv = NULL;
}

void mostrarUsuariosLES(usuarios *rc){
    int i = 1;

    while (rc != NULL){
        printf(">> USUARIO: #%d | Id: %d | Apellido y Nombre: %s | Modelo: %d\n", i, rc->idUsuario, rc->apellidoNombre, rc->fechaAlta);
        rc = rc->sgte;
        i++;
    }
    if (rc == NULL){
        mostrarMensaje(7);
    }
}

void freeUsuariosLES(usuarios **rc){
    usuarios *aux = NULL;
    while ((*rc) != NULL){
        aux = (*rc);
        aux->sgte = NULL;
        (*rc) = (*rc)->sgte;
        free(aux);
    }
    printf("Lista de Usuarios liberada correctamente.. :)\n");
}

/*
	::::::::::::::::::::::: UTILIDADES PARA LEC MEDIDORES :::::::::::::::::::::::::::
*/

medidores * buscarAnteriorMedidorLEC(int buscar, medidores **rc) {
    medidores *ant = (*rc);
    medidores *aux = (*rc)->sgte;     // Para poder consultar si es != rc

    int primero = (*rc)->idMedidor;

    // Buscamos el anterior, realizando recorrido con aux  
    if (primero > buscar){
        while(aux != (*rc)) {   // buscamos el ultimo nodo con aux
            ant = aux;
            aux = aux->sgte;
        }
    }else{
        while(aux != (*rc)) {   // buscamos el ultimo nodo con aux
            if (aux->idMedidor > buscar){
                aux = (*rc);
            }else{
                ant = aux;
                aux = aux->sgte;
            }
        }
    }
    return ant;
}

void insertarMedidorLEC(medidores *nv, medidores **ini){
    medidores *ant = NULL;

    if ((*ini) == NULL){
        (*ini) = nv;
        (*ini)->sgte = nv;
    }else{
        int numNV = nv->idMedidor;     // Dato del nuevo nodo
        int numIni = (*ini)->idMedidor;   // Dato de la lista original
        
        ant = buscarAnteriorMedidorLEC(numNV, &(*ini));
        
        nv->sgte = ant->sgte;
        ant->sgte = nv;
        if(numIni > numNV) {
            (*ini) = nv;
        }
    }
    ant = NULL;
    nv = NULL;
}

/**
 * Funcion para mostrar la lista de medidores
*/
void mostrarMedidoresLEC(medidores *rc){
    int i = 2;
    medidores *aux = NULL;
    
    if (rc != NULL){
        aux = rc->sgte;
        printf(">> MEDIDOR: #1 | Id: %d | Numero: %s | Modelo: %s\n", rc->idMedidor, rc->numero, rc->modelo);
        while (rc != aux){
            printf(">> MEDIDOR: #%d | Id: %d | Numero: %s | Modelo: %s\n", i, aux->idMedidor, aux->numero, aux->modelo);
            aux = aux->sgte;
            i++;
        }
        if (rc == NULL) mostrarMensaje(7);
    }else{
        mostrarMensaje(7);
    }
}

void freeMedidoresLEC(medidores **rc){
    medidores *aux = NULL;
    medidores *borrar = NULL;

    aux = (*rc);
    (*rc) = (*rc)->sgte;

    while ((*rc) != aux){
        borrar = (*rc);
        (*rc) = (*rc)->sgte;
        borrar->sgte = NULL;
        free(borrar);
        borrar = NULL;
    }
    if ((*rc) == aux){
        free((*rc));
        (*rc) = NULL;
    }
    aux = NULL;

    printf("Lista de Medidores liberada correctamente.. :)\n");
}

#endif
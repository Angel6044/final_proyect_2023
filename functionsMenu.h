#ifndef FUNCTIONS_MENU_H
#define FUNCTIONS_MENU_H

// Definición de códigos de escape ANSI para colores de texto
#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void showMainOptions();
void showListOptions();
void menuListOptions(usuarios *l1, medidores *l2, MedxUsu *l3, mediciones *l4, facturas *l5, costos *l6);


void showMainOptions(){
    system("cls");
    char fechaActual[11]; 
    obtenerFecha("%Y/%m/%d", fechaActual);
    printf("Fecha Actual: %s\n", fechaActual);
    printf("\n");
    printf("============================================================================================================================================\n");
    printf("                                                                 MENU PRINCIPAL\n");
    printf("============================================================================================================================================\n");
    printf("\n=============== MENU DE OPCIONES ===============\n");
    printf("1. LEER TODOS LOS ARCHIVOS\n");
    printf("2. MOSTRAR LISTAS\n");
    printf("3. GENERAR FACTURAS\n");
    printf("4. MOSTRAR USUARIOS DEUDORES POR MES\n");
    printf("5. CARGAR ARCHIVOS Y LIBERAR LAS LISTAS\n");
    printf("6. CREAR COPIA DE SEGURIDAD DE LOS ARCHIVOS\n");
    printf("7. SALIR\n");
    printf("================================================\n");
}

void showListOptions(){
    system("cls");
    char fechaActual[11]; 
    obtenerFecha("%Y/%m/%d", fechaActual);
    printf("Fecha Actual: %s\n", fechaActual);
    printf("\n");
    printf("============================================================================================================================================\n");
    printf("                                                                 MENU DE LISTAS\n");
    printf("============================================================================================================================================\n");
    printf("\n================ MOSTRAR LISTAS ================\n");
    printf("1. Usuarios\n");
    printf("2. Medidores\n");
    printf("3. MedXUsu\n");
    printf("4. Mediciones\n");
    printf("5. Facturas\n");
    printf("6. Costos\n");
    printf("7. Mostrar Todos\n");
    printf("8. Salir\n");
    printf("\n=================================================\n");
}

void menuListOptions(usuarios *l1, medidores *l2, MedxUsu *l3, mediciones *l4, facturas *l5, costos *l6){
    int opcion;
    int valueEnd = 0;
    int ErrorNoNumeric = 0;
    int next = 0;

    do {
        showListOptions();
        printf("Ingrese una opcion: ");
        while(valueEnd == 0 && next != 1){
            fflush(stdin);
            if (scanf("%d", &opcion) != 1) ErrorNoNumeric = 1;
            if ((opcion < 0 || ErrorNoNumeric == 1) && opcion != 0 ){
                if (ErrorNoNumeric == 1) mostrarMensajeError(1);    // Error Caracter ingresado
                if (opcion < 0) mostrarMensajeError(2);             // Error Numero ingresado < 0
                ErrorNoNumeric = 0;
                showListOptions();
                printf ("Ingrese nuevamente una opcion: ");
            }else{
                if (opcion == 8) valueEnd = 1; else next = 1;
            }   
        }
        next = 0;

        switch (opcion) {
            case 1:
                printf("\nMOSTRANDO LISTA DE USUARIOS\n\n");
                mostrarUsuariosLES(l1);
                break;
            case 2:
                printf("\nMOSTRANDO LISTA DE MEDIDORES\n\n");
                mostrarMedidoresLEC(l2);
                break;
            case 3:
                printf("\nMOSTRANDO LISTA DE MEDIDORESxUSUARIOS\n\n");
                mostrarMedxUsuLES(l3);
                break;
            case 4:
                printf("\nMOSTRANDO LISTA DE MEDICIONES\n\n");
                mostrarMedicionesLDE(l4);
                break;
            case 5:
                printf("\nMOSTRANDO LISTA DE FACTURAS\n\n");
                mostrarFacturasLES(l5);
                break;
            case 6:
                printf("\nMOSTRANDO LISTA DE COSTOS\n\n");
                mostrarCostosLES(l6);
                break;
            case 7:
                printf("\nMOSTRANDO TODAS LAS LISTAS\n\n");
                showAllLists(l1, l2, l3, l4, l5, l6);
                break;
            case 8:
                break;
            default:
                printf("Opcion invalida. Por favor, seleccione una opcion valida.\n");
                break;
        }

        mostrarMensaje(500);
    } while (opcion != 8);
}

void caraLoco(){
    printf("  .-\"\"\"-.\n");
    printf(" /       \\\n");
    printf("|  o   o  |\n");
    printf("|    ^    |\n");
    printf("|   '-'   |\n");
    printf(" \\_______/\n");
}

void mostrarMensajeInicial() {
    // Establece el color de fondo y el color del texto
    system("color FA");  // El código "0A" representa un fondo negro y texto verde. Puedes elegir otros colores según tu preferencia.

    // Muestra el mensaje llamativo
    printf(ANSI_COLOR_BLACK);
    printf("\n");
    printf("============================================================================================================================================\n");
    printf("                                                       BIENVENIDO AL PROGRAMA\n");
    printf("============================================================================================================================================\n");
    printf("\n");
    printf(ANSI_COLOR_RED); 
    printf("QUE PROGRAMON CHABAL.!!\n");
    printf("Pero que realiza este programa?\n");
    printf("\n");
    printf(ANSI_COLOR_BLUE);
    printf(">> 1. Te permito leer todos los archivos csv del sistema las veces que se quiera.\n");
    printf(">> 2. Realizo la facturacion dependiendo del mes seleccionado.\n");
    printf(">> 3. Ademas realizo un arbol binario de busqueda de todos los usuarios deudores por mes seleccionado.\n");
    printf(">> 4. Como si fuera poco, ademas como soy muy meticuloso, podes realizar una copia de seguridad de todos tus archivos.\n");
    printf(">> Asi que ya no te preocupes mas y ponte a trabajar seguro y comodo.\n");
    printf(">> Recuerda que siempre estoy observando lo que haces.!!\n");
    printf(ANSI_COLOR_MAGENTA);
    printf(">> Porque yo soy, YO SOY\n");
    printf("\n");
    printf(ANSI_COLOR_RED);
    printf("Pues gracias crack.!!\n");
    printf("\n");
    printf(ANSI_COLOR_BLACK);
    printf("Presiona cualquier tecla para salir...\n");
    getch();  // Espera a que se presione cualquier tecla
}

#endif
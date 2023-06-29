#include "../proyect_final_2023/structs.h"
#include "../proyect_final_2023/functionsCommons.h"
#include "../proyect_final_2023/functionsListas.h"
#include "../proyect_final_2023/functionsCSV.h"
#include "../proyect_final_2023/functions.h"
#include "../proyect_final_2023/abbUsuDeudores.h"
#include "../proyect_final_2023/settings.h"
#include "../proyect_final_2023/functionsMenu.h"

int main(){
    usuariosDeudores *AbbUsuariosDeudores = NULL; 
    usuarios *listaUsuarios = NULL; 
	medidores *listaMedidores = NULL; 
	MedxUsu *listaMedxUsu = NULL; 
	mediciones *listaMediciones = NULL;         
	facturas *listaFacturas = NULL;         
	costos *listaCostos = NULL; 

    int opcion;
    int valueEnd = 0;
    int ErrorNoNumeric = 0;

    // Al iniciar la ejecucion del programa 

    setConsoleFontSize(20);     // Tamaño de la letra
    sizeConsole();              // Tamaño de la consola

    mostrarMensajeInicial();    // Mensaje inicio
    
    colorBackground();          // Color de fondo
    
    system("cls"); pause(1);

    // Leer todos los archivos y crear las listas
    readAllFilesCSV(&listaUsuarios, &listaMedidores, &listaMedxUsu, &listaMediciones, &listaFacturas, &listaCostos);
    
    do {
        valueEnd = 0;
        showMainOptions();
        printf("Ingrese una opcion: ");
        while(valueEnd == 0){
            fflush(stdin);
            if (scanf("%d", &opcion) != 1) ErrorNoNumeric = 1;
            if ((opcion < 0 || ErrorNoNumeric == 1) && opcion != 0 ){
                if (ErrorNoNumeric == 1) mostrarMensajeError(1);    // Error Caracter ingresado
                if (opcion < 0) mostrarMensajeError(2);             // Error Numero ingresado < 0
                ErrorNoNumeric = 0;
                showMainOptions();
                printf ("Ingrese nuevamente una opcion: ");
            }else{
                valueEnd = 1;
            }   
        }

        switch (opcion) {
            case 1:
                showOptionsReadAll(&listaUsuarios, &listaMedidores, &listaMedxUsu, &listaMediciones, &listaFacturas, &listaCostos);
                break;
            case 2:
                menuListOptions(listaUsuarios, listaMedidores, listaMedxUsu, listaMediciones, listaFacturas, listaCostos);
                break;
            case 3:
                seleccionarPeriodoFacturacion(listaMediciones, listaCostos, &listaFacturas);
                break;
            case 4:
                seleccionarMesGenerarABB(&AbbUsuariosDeudores, listaMedxUsu, listaUsuarios, listaFacturas);
                break;
            case 5:
                writeAllFilesCSV(listaUsuarios, listaMedidores, listaMedxUsu, listaMediciones, listaFacturas, listaCostos);
                freeAllLists(&listaUsuarios, &listaMedidores, &listaMedxUsu, &listaMediciones, &listaFacturas, &listaCostos);
                break;
            case 6:
                backupFilesCSV(listaUsuarios, listaMedidores, listaMedxUsu, listaMediciones, listaFacturas, listaCostos);
                break;
            case 7:
                printf("Saliendo del programa...\n");
                writeAllFilesCSV(listaUsuarios, listaMedidores, listaMedxUsu, listaMediciones, listaFacturas, listaCostos);
                freeAllLists(&listaUsuarios, &listaMedidores, &listaMedxUsu, &listaMediciones, &listaFacturas, &listaCostos);
                pause(2);
                break;
            default:
                printf("Opcion invalida. Por favor, seleccione una opcion valida.\n");
                break;
        }

    } while (opcion != 7);
    
    return 0;
}   




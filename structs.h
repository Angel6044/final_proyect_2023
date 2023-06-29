#ifndef STRUCTS_H
#define STRUCTS_H

#include<stdio.h>
#include<stdlib.h>	 // malloc
#include<stdbool.h>  // bool
#include<string.h>
#include<time.h>
#include<conio.h>
#include <windows.h>

typedef struct usuariosDeudores{	
	int idUsuario;
	char apellidoNombre[60];
	int fechaAlta;
	struct usuariosDeudores *izq;	
	struct usuariosDeudores *der;	
}usuariosDeudores;

typedef struct usuarios{	
	int idUsuario;
	char apellidoNombre[60];
	int fechaAlta;
	struct usuarios *sgte;	
}usuarios;

typedef struct medidores{
	int idMedidor;
	char numero[20];	
	char modelo[30];		
	struct medidores *sgte;	
}medidores;

typedef struct MedxUsu{
	int idUsuario;
	int idMedidor;
	int idCuenta;
	int fechaAlta;
	int fechaBaja;
	struct MedxUsu *sgte;	
}MedxUsu;

typedef struct mediciones{
	int idCuenta;
	int periodo;
	int fechaLectura;
	double lectura;
	struct mediciones *ant;	
	struct mediciones *sgte;	
}mediciones;

typedef struct facturas{
	int idCuenta;
	int periodo;
	int fechaEmision;
	double consumo;
	double totalAPagar;
	int pagado;
	struct facturas *sgte;	
}facturas;

typedef struct costos{
	int idCostos;
	int mtsDesde;
	int mtsHasta;
	int valorMetro;
	struct costos *sgte;	
}costos;

#endif

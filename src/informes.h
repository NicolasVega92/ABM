/*
 * informes.h
 *
 *  Created on: 11 oct. 2020
 *      Author: Nico
 */

#ifndef INFORMES_H_
#define INFORMES_H_
static const char TXT_TIPOS[2][LONG_NAME]={"Pausado", "Activo"};
static const char TXT_RUBROS[10][LONG_NAME]={"Cerrajería", "Cochera", "Food Trucks", "Gimnasio", "Locutorio", "Salón", "Hoteles", "Educación", "Veterinaria", "Recreación"};
	typedef struct
	{
		int idCliente;
		char cuit[LONG_NAME];
		int cantidad;
		int rubros;
		int isEmpty;
	}Auxiliar;
	int info_searchIdClienteByIdAviso(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente, int idAvisoBuscar);
	int info_printClienteById(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente, int idClienteRef);
	int info_printClienteWithAvisos(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente);
	int info_calcularMaxAvisosByCuit(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente);
	int info_calcularAvisosPausados(Avisos* pArray, int length);
	int info_calcularMaxRubro(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente);
	int info_printClienteWithCantidadAvisos(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente, char cuit[]);
	int aux_init(Auxiliar* pArray, int length);
#endif /* INFORMES_H_ */

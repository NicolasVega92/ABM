/*
 * cliente.h
 *
 *  Created on: 1 oct. 2020
 *      Author: Nico
 */
#ifndef CLIENTE_H_
#define CLIENTE_H_
	#include "utn.h"
	#define QTY_CLIENTE 100
	typedef struct
	{
		int id;
		char nameCliente[LONG_NAME];
		char lastName[LONG_NAME];
		char cuit[LONG_NAME];
		int isEmpty;
	}Cliente;
	int cliente_init(Cliente* pArray, int length);
	int cliente_addForzada(Cliente* pArray, int length, char name[], char lastName[], char cuit[]);
	int cliente_findFirstValidPosition(Cliente* pArray, int length);
	int cliente_findById(Cliente* pArray, int length, int id);
	int cliente_create(Cliente* pArray, int length);
	int cliente_altaCliente(int length, int* pId, char aName[], char aLastName[], char aCuit[]);
	int cliente_add(Cliente* pArray, int length, int id, char name[], char lastName[], char cuit[]);
	int cliente_modifyAll(Cliente* pArray, int length, int indice); //MODIFICA TODO
	int cliente_modifyClienteByIndex(Cliente* pArray, int length, int indice); //MODIFICA POR OPCIONES
	int cliente_remove(Cliente* pArray, int length, int indice);
	int cliente_print(Cliente* pArray, int length);
	int cliente_sortByLastName(Cliente* pArray, int length, int order);
	int cliente_sumaSalary(Cliente* pArray, int length, float* pResultado);
	int cliente_averageSalary(Cliente* pArray, int length, int* contadorEmpleadosCargados, float* pAverageSalary);
	int cliente_gainMoreThanAverage(Cliente* pArray, int length, float average, int* pClienteGainMore);
	int cliente_printClienteById(Cliente* pArrayCliente, int lengthCliente, int idClienteRef);
	void cliente_menuOptions();
#endif /* CLIENTE_H_ */


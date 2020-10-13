/*
 * avisos.h
 */
#ifndef AVISOS_H_
#define AVISOS_H_
	#include "cliente.h"
	#include "utn.h"
	#define QTY_AVISOS 1000
	#define TEXT_LONG 64
	#define MAX_RUBROS 10
	typedef struct
	{
		int id;
		int idCliente;
		int numeroRubro;
		char texto[TEXT_LONG];
		int estado;
		int isEmpty;
	}Avisos;
	int avisos_init(Avisos* pArray, int length);
	int avisos_addForzada(Avisos* pArray, int length, char texto[], int idCliente, int numRubro, int estado);
	int avisos_create(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente);
	int avisos_add(Avisos* pArray, int length, int id, char texto[], int idCliente, int numRubro, int auxestado);
	int avisos_findFirstValidPosition(Avisos* pArray, int length);
	int avisos_remove(Avisos* pArray, int length, int indice);
	int avisos_print(Avisos* pArray, int length);
	int avisos_modifyAvisosByIndex(Avisos* pArray, int length, int indice);
	int avisos_findById(Avisos* pArray, int length, int id);
	int avisos_altaAvisos(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente, int* pId, char aText[], int* pIdCliente, int* pRubro, int* pEstado);
	int avisos_countActiveByIdCliente(Avisos* pArray, int length, int id);
	int avisos_estadoPause(Avisos* pArray, int length, int indice);
	int avisos_estadoActive(Avisos* pArray, int length, int indice);
	int avisos_printByIdCliente(Avisos* pArray, int length, int idBuscar);
	int avisos_removeByIdCliente(Avisos* pArray, int length, int idClienteARemover);
	//int avisos_findByIdCliente(Avisos* pArray, int length, int id);
	//int avisos_printClienteByCuit(Cliente* pArrayCliente, int lengthCliente, Avisos* pArray, char cuit[], int length);
#endif /* AVISOS_H_ */

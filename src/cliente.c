/*
 * cliente.c
 *
 *  Created on: 1 oct. 2020
 *      Author: Nico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cliente.h"
#include "utn.h"


static int cliente_generarIdNuevo(void);
/*
* \brief	Inicializa todas las posiciones del array en empty (TRUE).
* \param Cliente* pArray puntero al array recibido
* \param int length limite del array
* \return int Retorna (-1) si se encuentra un error / (0)  Ok
*/
int cliente_init(Cliente* pArray, int length)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && length > 0)
	{
		for(i=0;i<length ;i++)
		{
			pArray[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Busca dentro de los indices del array Cliente el primer indice donde el valor de isEmpty == TRUE para
 * 			retornar ese valor de (i) como espacio valido para dar un alta
 * \param Cliente* pArray puntero al array
 * \param int limite, es el limite del array
 * \return retorna el valor de ( i ) OK / devuelve (-1) para indicar que no hay espacio a completar
 */
int cliente_findFirstValidPosition(Cliente* pArray, int length)
{
	int i;
	int retorno = -1;
	if(pArray!=NULL && length > 0)
	{
		for(i=0; i < length;i++)
		{
			if(pArray[i].isEmpty == TRUE)
			{
				retorno = i;
				return retorno;
			}
		}
	}
	return retorno;
}
/**
* \brief 	Agrega en el array de la estructura los valores pasados como parametros dentro del indice devuelto por la funcion searchFirstValidPosition
* 			E imprime los valores finales del cliente agregado.
* \param 	Cliente* pArray puntero al array recibida
* \param 	int length limite del array
* \param 	int id Id recibido
* \param 	char name[], array que contiene chars
* \param 	char lastName[], array que contiene chars
* \param 	float salary salario recibido
* \param 	int sector sector recibido
* \return 	int Return (-1) Error / (0) Ok
*/
int cliente_add(Cliente* pArray, int length, int id, char name[], char lastName[], char cuit[])
{
	int retorno = -1;
	int indiceLibre;
	if(pArray!=NULL && length > 0 && id >= 0 && name != NULL && lastName != NULL && cuit != NULL)
	{
		indiceLibre = cliente_findFirstValidPosition(pArray, QTY_CLIENTE);
		if(indiceLibre == -1)
		{
			printf("Ya no quedan espacios libres.\n");
		}
		else
		{
			pArray[indiceLibre].id = id;
			pArray[indiceLibre].isEmpty = FALSE;
			strncpy(pArray[indiceLibre].nameCliente, name, sizeof(pArray[indiceLibre].nameCliente)-1);
			strncpy(pArray[indiceLibre].lastName, lastName, sizeof(pArray[indiceLibre].lastName)-1);
			strncpy(pArray[indiceLibre].cuit, cuit, sizeof(pArray[indiceLibre].cuit)-1);
			printf("Id: %d - Cliente:%s %s - CUIT:%s \n", pArray[indiceLibre].id, pArray[indiceLibre].nameCliente, pArray[indiceLibre].lastName, pArray[indiceLibre].cuit);
		}
		retorno = 0;
	}
	return retorno;
}
/**
* \brief Crea valores predeterminados en el array de la estructura
* \param Cliente* pArray puntero al array recibida
* \param int length limite del array
* \param int id Id recibido
* \param char name[], array que contiene chars
* \param char lastName[], array que contiene chars
* \param float salary salario recibido
* \param int sector sector recibido
* \return int Return (-1) Error / (0) Ok
*/
int cliente_addForzada(Cliente* pArray, int length, char name[], char lastName[], char cuit[])
{
	int retorno = -1;
	int indiceLibre;
	if(pArray!=NULL && length > 0 && name != NULL && lastName != NULL && cuit != NULL)
	{
		indiceLibre = cliente_findFirstValidPosition(pArray, QTY_CLIENTE);
		if(indiceLibre == -1)
		{
			printf("Ya no quedan espacios libres.\n");
		}
		else
		{
			pArray[indiceLibre].id = cliente_generarIdNuevo();
			pArray[indiceLibre].isEmpty = FALSE;
			strncpy(pArray[indiceLibre].nameCliente, name, sizeof(pArray[indiceLibre].nameCliente)-1);
			strncpy(pArray[indiceLibre].lastName, lastName, sizeof(pArray[indiceLibre].lastName)-1);
			strncpy(pArray[indiceLibre].cuit, cuit, sizeof(pArray[indiceLibre].cuit)-1);
		}
		retorno = 0;
	}
	return retorno;
}
/**
* \brief Imprime el array pasado como parametro, si el campo isEmpty == FALSE
* \param Cliente* pArray puntero al array recibida
* \param int length limite del array
* \return int Return (-1) Error / (0) Ok
 */
int cliente_print(Cliente* pArray, int length)
{
	int retorno = -1;
	int i;
	if(pArray!=NULL && length > 0)
	{
		printf("\n Id          Nombre        Apellido            CUIT\n");
		for(i=0; i< length; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				printf("%3d %15s %15s %15s \n", pArray[i].id, pArray[i].nameCliente, pArray[i].lastName, pArray[i].cuit);
			}
		}
		retorno = 0;
	}
	return retorno;
}
/*
* \brief Devuelve como retorno el indice del ID pasado como parametro.
* \param Cliente* pArray puntero al array recibida
* \param int length limite del array
* \param int idValue ID recibido a buscar
* \return int Return (-1) Error / (0) Ok
* */
int cliente_findById(Cliente* pArray, int length, int id)
{
	int retorno = -1;
	int i;
	if(pArray!=NULL && length > 0 && id > 0)
	{
		for(i=0; i < length; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				if(pArray[i].id == id)
				{
					retorno = i;
					break;
				}
			}
		}
	}
	return retorno;
}
/**
* \brief 	Modifica un campo de un Cliente, dicho empleado es el indicado por el Indice pasado como parametro
* 			Da la opcion de que campo se desea modificar.
* \param 	Cliente* pArray puntero al array recibida
* \param 	int length limite del array
* \param 	int indice Int buscado en el array para modificar algún campo
* \return 	int Return (-1) Error / (0) Ok
 */
int cliente_modifyClienteByIndex(Cliente* pArray, int length, int indice)
{
	int retorno = -1;
	int opcionModificar;
	Cliente bufferCliente = pArray[indice];
	if(pArray != NULL && length > 0  && indice >= 0 && indice < length)
	{
		if(utn_getNumberInt("Que desea modificar en el Cliente:\n1- Nombre\n2- Apellido\n3- Cuit\n4- Salir\n", "Error, ingrese una opción correcta. (1 - 4)", &opcionModificar, 3, 1, 4)==0)
		{
			switch(opcionModificar)
			{
				case 1:
					if(utn_getName("Ingrese el nuevo Nombre del empleado:\n", "Error, ingrese un nombre válido\n", bufferCliente.nameCliente, 3, LONG_NAME)==0)
					{
						printf("Nombre modificado correctamente\n");
					}
					break;
				case 2:
					if(utn_getName("Ingrese el nuevo Nombre del empleado:\n", "Error, ingrese un nombre válido\n", bufferCliente.lastName, 3, LONG_NAME)==0)
					{
						printf("Nombre modificado correctamente\n");
					}
					break;
				case 3:
					if(utn_getCuit("Ingrese el nuevo cuit del empleado:\n", "Error, ingrese un cuit válido\n", bufferCliente.cuit, 3, LONG_NAME)==0)
					{
						printf("cuit modificado correctamente\n");
					}
					break;
				case 4:
					break;
			}
			bufferCliente.isEmpty = FALSE;
			bufferCliente.id = pArray[indice].id;
			pArray[indice] = bufferCliente;
			retorno = 0;
		}
	}
	return retorno;
}
/**
* \brief Modifica todos los campos de un Cliente, dicho empleado es el indicado por el Indice pasado como parametro
* \param Cliente* pArray puntero al array recibida
* \param int length limite del array
* \param int indice Int buscado en el array para modificar algún campo
* \return int Return (-1) Error / (0) Ok
 */
int cliente_modifyClienteAll(Cliente* pArray, int length, int id)
{
	int retorno = -1;
	Cliente bufferCliente = pArray[id];
	if(pArray != NULL && length > 0  && id >= 0 && id < length)
	{
		if(	(utn_getName("Ingrese el nuevo Nombre de la Cliente:\n", "Error, ingrese un nombre válido\n", bufferCliente.nameCliente, 3, LONG_NAME)==0) &&
			(utn_getName("Ingrese el nuevo Apellido:\n", "Error, ingrese un apellido válido\n", bufferCliente.lastName, 3, LONG_NAME)==0) &&
			(utn_getCuit("Ingrese el nuevo CUIT del cliente:\n", "Error, ingrese un Cuit válido\n", bufferCliente.cuit, 3, LONG_NAME)==0))
		{
			bufferCliente.isEmpty = FALSE;
			bufferCliente.id = pArray[id].id;
			pArray[id] = bufferCliente;
			retorno = 0;
		}
	}
	return retorno;
}
/**
* \brief pide al usuario los valores para los campos del cliente, que luego se sumaran al array por la funcion addCliente
* \param Cliente* pArray puntero al array recibida
* \param int length limite del array
* \param int* pId puntero de Id
* \param char aName[], array que contiene chars
* \param char aLastName[], array que contiene chars
* \param float* pSalary puntero al salario recibido
* \param int* pSector puntero al sector recibido
* \return int Return (-1) Error / (0) Ok
 */
int cliente_altaCliente(int length, int* pId, char aName[], char aLastName[], char aCuit[])
{
	int retorno = -1;
	if(pId!= NULL && aName!=NULL  && aLastName != NULL && aCuit != NULL && length > 0)
	{
		if(	(utn_getName("Ingresa el Nombre del cliente:\n", "Error, por favor reintentelo con un nombre válido\n", aName , 3, LONG_NAME)==0) &&
			(utn_getName("Ingresa el Apellido del cliente:\n", "Error, por favor reintentelo con un Apellido válido\n", aLastName , 3, LONG_NAME)==0) &&
			(utn_getCuit("Ingresa el CUIT:\n", "ERROR CUIT\n",  aCuit, 3, LONG_NAME)==0))
		{
			*pId = cliente_generarIdNuevo();
			retorno = 0;
		}
	}
	return retorno;
}
/*
 *	\brief Cada vez que es llamada devuelve un ID nuevo. Que nunca devolvio antes.
 */
static int cliente_generarIdNuevo(void)
{
	static int id=0;
	id = id + 1;
	return id;
}
/*
* \brief Remueve un cliente del array poniendo a isEmpty == TRUE
* \param Cliente* pArray puntero al array recibida
* \param int length limite del array
* \param int indice indice recibido a buscar en el array
* \return int Return (-1) Error / (0) Ok
*/
int cliente_remove(Cliente* pArray, int length, int indice)
{
	int retorno = -1;
	if(pArray != NULL && length > 0 && indice >= 0)
	{
		pArray[indice].isEmpty = TRUE;
		retorno = 0;
	}
	return retorno;
}
/**
* \brief 	Utilizando las funciones "alta" y "add", para crear un cliente valido en el array de la structura.
* 			Devuelve mensajes de error, si alguno de dichas funciones no se pudo obtener lo deseado.
* \param 	Cliente* pArray, array recibida para crear el cliente
* \param 	int length limite del array
* \return 	int Return (-1) Error / (0) Ok
 */
int cliente_createCliente(Cliente* pArray, int length)
{
	int retorno = -1;
	int id;
	char nameCliente[LONG_NAME];
	char lastName[LONG_NAME];
	char cuit[LONG_NAME];
	if(pArray != NULL && length > 0)
	{
		if(cliente_altaCliente(length, &id, nameCliente, lastName, cuit)==0)
		{
			if(cliente_add(pArray, length, id, nameCliente, lastName, cuit)==0)
			{
				printf("Carga del empleado exitosa!\n\n");
				retorno = 0;
			}
			else
			{
				printf("No se pudo cargar el empleado\n\n");
			}
		}
		else
		{
			printf("No se pudieron obterner los datos del empleado de manera correcta\n");
		}
	}
	return retorno;
}
/*
* \brief 	Ordena las filas del array de dos maneras: order = 1 -> de forma ascendente. order = 2 -> de forma descendente
* 			Compara por lastName y luego por name.
* \param 	Cliente* pArray, array recibida para crear el cliente
* \param 	int length limite del array
* \param 	order parametro que determina el orden del array
* \return 	int Return (-1) Error / (0) Ok
 */
int cliente_sortByLastName(Cliente* pArray, int length, int order)
{
	int retorno = -1;
	int i;
	int flagSwap;
	int nuevoLimite = length - 1;
	Cliente buffer;
	if(pArray!=NULL && length > 0 && (order == 1 || order == 2))
	{
		do
		{
			flagSwap = 0;
			for(i=0; i < nuevoLimite; i++)
			{
					if(	(order == 1 && strncmp(pArray[i].lastName, pArray[i+1].lastName, sizeof(pArray[i].lastName)) > 0)
							||
						(order == 2 && strncmp(pArray[i].lastName, pArray[i+1].lastName, sizeof(pArray[i].lastName)) < 0)
							||
						((order == 1 && strncmp(pArray[i].lastName, pArray[i+1].lastName, sizeof(pArray[i].lastName)) == 0)
						&& (strncmp(pArray[i].nameCliente, pArray[i+1].nameCliente, sizeof(pArray[i].nameCliente)) > 0))
							||
						((order == 2 && strncmp(pArray[i].lastName, pArray[i+1].lastName, sizeof(pArray[i].lastName)) == 0)
						&& (strncmp(pArray[i].nameCliente, pArray[i+1].nameCliente, sizeof(pArray[i].nameCliente)) < 0)))
					{
						buffer = pArray[i];
						pArray[i] = pArray[i+1];
						pArray[i+1] = buffer;
						flagSwap = 1;
					}
			}
			nuevoLimite--;
		}while(flagSwap);
		retorno = 0;
	}
	return retorno;
}
/*
* \brief calcula el salario promedio de todos los empleados en el array, obteniendo la suma de la funcion calculateSumaSalary
* \param Cliente* pArray, array recibida para crear el cliente
* \param int length limite del array
* \param int* contadorEmpleadosCargados, punteor al valor de la cantidad de empleados que tienen isEmpty=FALSE
* \param float* pAverageSalary puntero al promedio de los salarios
* \return int Return (-1) Error / (0) Ok
 */
int cliente_averageSalary(Cliente* pArray, int length, int* contadorEmpleadosCargados, float* pAverageSalary)
{
	int retorno = -1;
	float sumaTotal;
	float promedio;
	int bufferContador;
	if(pArray != NULL && length > 0)
	{
		bufferContador = (int)*contadorEmpleadosCargados;
		if(cliente_sumaSalary(pArray, length, &sumaTotal)==0)
		{
			promedio = sumaTotal / bufferContador;
		}
		*pAverageSalary = promedio;
		retorno = 0;
	}
	return retorno;
}
/*
* \brief calcula la suma de SALARIOS de los empleados validando el isEmpty==FALSE.
* \param Cliente* pArray, array recibida para crear el cliente
* \param int length limite del array
* \param float* pResultado, puntero a devolver el valor de los salarios
* \return int Return (-1) Error / (0) Ok
 */
int cliente_sumaSalary(Cliente* pArray, int length, float* pResultado)
{
	int retorno = -1;
	int i;
	float sumaSalary = 0;
	if(pArray != NULL && length > 0)
	{
		for(i=0; i < length; i++)
		{
			if(pArray[i].isEmpty == 0)
			{
	//			sumaSalary += pArray[i].precio;
			}
		}
		*pResultado = sumaSalary;
		printf("\n- El \"total de los salarios\" es: $ %.2f\n", *pResultado);
		retorno = 0;
	}
	return retorno;
}
/*
* \brief calcula la cantidad de empleados que ganan más del promedio y valida el flag isEmpty==FALSE
* \param Cliente* pArray, array recibida para crear el cliente
* \param int length limite del array
* \param float average recibe el promedio de salarios a evaluar
* \param int* pClienteGainMore puntero de la cantidad de empleados que ganan mas
* \return int Return (-1) Error / (0) Ok
 */
int cliente_gainMoreThanAverage(Cliente* pArray, int length, float average, int* pClienteGainMore)
{
	int retorno = -1;
	int i;
	int contador = 0;
	if(pArray != NULL && length > 0 && average > MIN_SALARY && average < MAX_SALARY && pClienteGainMore != NULL)
	{
		for(i=0; i < length; i++)
		{
			//if(pArray[i].precio > average && pArray[i].isEmpty == 0)
			{
				contador++;
			}
		}
		*pClienteGainMore = contador;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Imprime un menú al usuario
 * \return void
 */
void cliente_menuOptions()
{
	printf(	"Ingrese una de las siguientes opciones:\n"
			"1- Dar de alta una Cliente\n"
			"2- Modificar algúna cliente por ID\n"
			"3- Dar de baja una cliente\n"
			"4- CONTRATAR AVISOS\n"
			"5- Pausar Aviso de publicacion\n"
			"6- Reanudar Aviso de publicacion\n"
			"7- Imprimir clientes COMPLETAS AVISOS\n"
			"8- INFORMES\n"
			"9- Salir\n");
}

/*
 * informes.c
 *
 *  Created on: 11 oct. 2020
 *      Author: Nico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "avisos.h"
#include "utn.h"
#include "informes.h"


/*
* \brief Recibe un ID para comparar con los id de los avisos para retornar el idCliente de ese aviso
* \param Avisos* pArray puntero al array recibida
* \param int length limite del array
* \param Cliente* pArrayCliente puntero al array recibida
* \param int lengthCliente limite del array
* \param int idAvisoBuscar sector recibido
* \return int Return (-1) Error / numero de ID cliente en caso de Ok
 */
int info_searchIdClienteByIdAviso(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente, int idAvisoBuscar)
{
	int retorno = -1;
	int i;
	int auxIdCliente;
	if(pArray != NULL && pArrayCliente != NULL && length > 0 && lengthCliente > 0 && idAvisoBuscar > 0)
	{
		for(i=0; i < length; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				if(pArray[i].id == idAvisoBuscar)
				{
					auxIdCliente = pArray[i].idCliente;
					retorno = auxIdCliente;
					break;
				}
			}
		}
	}
	return retorno;
}
/*
* \brief 	Recibe un idCliente de un aviso y lo compara con el array Cliente para imprimir las coincidencias
* 			del idCliente recibido y el id de los Clientes que estan cargados.
* \param 	Avisos* pArray puntero al array recibida
* \param 	int length limite del array
* \param 	Cliente* pArrayCliente puntero al array recibida
* \param 	int lengthCliente limite del array
* \param 	int idClienteRef sector recibido
* \return int Return (-1) Error / (0) Ok
 */
int info_printClienteById(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente, int idClienteRef)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && pArrayCliente != NULL && idClienteRef > 0 && length > 0 && lengthCliente > 0)
	{
		for(i=0; i < lengthCliente; i++)
		{
			if(pArrayCliente[i].isEmpty == FALSE)
			{
				if(pArrayCliente[i].id == idClienteRef)
				{
					printf("El cliente al que pertenece la publicacion es: %s %s con el Cuit: %s\n", pArrayCliente[i].nameCliente, pArrayCliente[i].lastName, pArrayCliente[i].cuit);
					break;
				}
			}
		}
		retorno = 0;
	}
	return retorno;
}
/*
* \brief 	Imprime los valores del Cliente y le agrega al print la cantidad de avisos buscados por la funcion
* 			avisos_countActiveByIdCliente()
* \param 	Avisos* pArray puntero al array recibida
* \param 	int length limite del array
* \param 	Cliente* pArrayCliente puntero al array recibida
* \param 	int lengthCliente limite del array
* \param 	int idClienteRef sector recibido
* \return int Return (-1) Error / (0) Ok
*/
int info_printClienteWithAvisos(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente)
{
	int retorno = -1;
	int i;
	int contadorActivos;
	if(pArray != NULL && pArrayCliente != NULL && length > 0 && lengthCliente > 0)
	{
		printf(" ID|         Nombre|       Apellido|           CUIT|  Cantidad de avisos activos\n");
		for(i=0; i < lengthCliente; i++)
		{
			if(pArrayCliente[i].isEmpty == FALSE)
			{
				contadorActivos = avisos_countActiveByIdCliente(pArray, QTY_AVISOS, pArrayCliente[i].id);
				//printf("Este cliente tiene %d avisos ACTIVOS\n\n", contadorActivos);
				printf("%3d|%15s|%15s|%15s|%15d\n", pArrayCliente[i].id, pArrayCliente[i].nameCliente, pArrayCliente[i].lastName, pArrayCliente[i].cuit, contadorActivos);
			}
		}
		retorno = 0;
	}
	return retorno;
}
/*
 *
 */
int info_punto8_1(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente)
{
	int retorno = -1;
	char listaClientes[QTY_CLIENTE][LONG_NAME];
	int i;
	int j;
	int flagExiste;
	int indiceCuitLibre = 0;
	if(pArray != NULL && pArrayCliente != NULL && length > 0 && lengthCliente > 0)
	{
		for(i=0; i < QTY_CLIENTE;i++)
		{
			strncpy(listaClientes[i], "", LONG_NAME);
		}
		for(i=0; i < lengthCliente; i++)
		{
			if(pArrayCliente[i].isEmpty == FALSE)
			{
				flagExiste = 0;
				for(j=0; j < indiceCuitLibre; j++)
				{
					if(strncmp(pArrayCliente[i].cuit, listaClientes[j], LONG_NAME)==0)
					{
						flagExiste = 1;
						break;
					}
				}
				if(flagExiste == 0)
				{
					strncpy(listaClientes[indiceCuitLibre], pArrayCliente[i].cuit, LONG_NAME);
					indiceCuitLibre++;
				}
			}
		}

		for(i=0; i< indiceCuitLibre;i++)
		{
			printf("cliente con CUIT: %s\n", listaClientes[i]);
		}

		retorno = 0;
	}
	return retorno;
}
/*
*/
int info_printClienteWithCantidadAvisos(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente, char cuit[])
{
	int retorno = -1;
	int i;
	int indiceArrayCliente;
	int contadorAvisos=0;
	if(pArray != NULL && pArrayCliente != NULL && cuit != NULL && length > 0 && lengthCliente > 0)
	{
		for(i=0; i < length; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
			//	if(strncmp(pArrayCliente[i].cuit, cuit, LONG_NAME)==0)
			//	{
					indiceArrayCliente = cliente_findById(pArrayCliente, QTY_CLIENTE, pArray[i].idCliente);
					if(indiceArrayCliente != -1)
					{
						contadorAvisos++;
					}
					printf("Id:%d  - Nombre: %s  -  Apellido: %s  -   Cuit: %s  - Cantidad de avisos contratados: %d \n",
																													pArrayCliente[i].id,
																													pArrayCliente[i].nameCliente,
																													pArrayCliente[i].lastName,
																													pArrayCliente[i].cuit,
																													contadorAvisos);
			//	}
			}
		}
		retorno = 0;
	}
	return retorno;
}
/*
* \brief	Inicializa todas las posiciones del array en empty (TRUE).
* \param Cliente* pArray puntero al array recibido
* \param int length limite del array
* \return int Retorna (-1) si se encuentra un error / (0)  Ok
*/
int aux_init(Auxiliar* pArray, int length)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && length > 0)
	{
		for(i=0;i<length ;i++)
		{
			pArray[i].isEmpty = TRUE;
			pArray[i].cantidad = 0;
		}
		retorno = 0;
	}
	return retorno;
}

/*
 *
 */
int info_aux(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente)
{
	int retorno = -1;
	Auxiliar arrayAux[lengthCliente];
	int i;
	int j;
	int flagExiste;
	int indiceCuitLibre = 0;
	int maxAvisos;
	int indiceMax;
	if(pArray != NULL && pArrayCliente != NULL && length > 0 && lengthCliente > 0)
	{
		aux_init(arrayAux, lengthCliente);
		for(i=0; i < lengthCliente; i++)
		{
			if(pArrayCliente[i].isEmpty == FALSE)
			{
				flagExiste = 0;
				for(j=0; j < indiceCuitLibre; j++)
				{
					if(arrayAux[j].isEmpty == FALSE && (arrayAux[j].idCliente == pArrayCliente[i].id))
					{
						flagExiste = 1;
						break;
					}
				}
				if(flagExiste == 0)
				{
					arrayAux[indiceCuitLibre].idCliente = pArrayCliente[i].id;
					arrayAux[indiceCuitLibre].isEmpty = FALSE;
					indiceCuitLibre++;
				}
			}
		}
		/*
		for(i=0; i< indiceCuitLibre;i++)
		{
			printf("cliente con ID: %d\n", arrayAux[i].idCliente);
		}
		 */
		for(i = 0; i < lengthCliente;i++)
		{
			if(arrayAux[i].isEmpty == FALSE)
			{
				for(j=0; j < length;j++)
				{
					if(pArray[j].isEmpty == FALSE && arrayAux[i].idCliente == pArray[j].idCliente)
					{
						arrayAux[i].cantidad++;
					}
				}

			}
		}
		for(i=0; i< indiceCuitLibre;i++)
		{
			printf("cliente con ID: %d tiene %d avisos\n", arrayAux[i].idCliente, arrayAux[i].cantidad);
			if(arrayAux[i].cantidad > maxAvisos || i==0)
			{
				maxAvisos = arrayAux[i].cantidad;
				indiceMax = arrayAux[i].idCliente;
			}
		}
		printf("El cliente con mas Avisos es el del ID %d con %d avisos\n\n", indiceMax, maxAvisos);
		retorno = 0;
	}
	return retorno;
}

/*
* \brief 	Imprime el id del cliente con la cantidad de avisos que posee
* 			Imprime el cliente con su cuit y el que tiene mas Avisos
* \param 	Avisos* pArray puntero al array recibida
* \param 	int length limite del array
* \param 	Cliente* pArrayCliente puntero al array recibida
* \param 	int lengthCliente limite del array
* \return int Return (-1) Error / (0) Ok
 */
int info_calcularMaxAvisosByCuit(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente)
{
	int retorno = -1;
	Auxiliar arrayAux[lengthCliente];
	int i;
	int j;
	int flagExiste;
	int indiceCuitLibre = 0;
	int maxAvisos;
	int indiceMax;
	char maxCuit[LONG_NAME];
	if(pArray != NULL && pArrayCliente != NULL && length > 0 && lengthCliente > 0)
	{
		aux_init(arrayAux, lengthCliente);
		for(i=0; i < lengthCliente; i++)
		{
			if(pArrayCliente[i].isEmpty == FALSE)
			{
				flagExiste = 0;
				for(j=0; j < indiceCuitLibre; j++)
				{
					if(arrayAux[j].isEmpty == FALSE && strncmp(arrayAux[j].cuit, pArrayCliente[i].cuit, LONG_NAME)==0)
					{
						flagExiste = 1;
						break;
					}
				}
				if(flagExiste == 0)
				{
					strncpy(arrayAux[indiceCuitLibre].cuit, pArrayCliente[i].cuit, LONG_NAME);
					arrayAux[indiceCuitLibre].idCliente = pArrayCliente[i].id;
					arrayAux[indiceCuitLibre].isEmpty = FALSE;
					indiceCuitLibre++;
				}
			}
		}
		/*
		for(i=0; i< indiceCuitLibre;i++)
		{
			printf("cliente con ID: %d\n", arrayAux[i].idCliente);
		}
		 */
		for(i = 0; i < lengthCliente;i++)
		{
			if(arrayAux[i].isEmpty == FALSE)
			{
				for(j=0; j < length;j++)
				{
					if(pArray[j].isEmpty == FALSE && arrayAux[i].idCliente == pArray[j].idCliente)
					{
						arrayAux[i].cantidad++;
					}
				}

			}
		}
		for(i=0; i< indiceCuitLibre;i++)
		{
			printf("cliente con ID: %d tiene %d avisos\n", arrayAux[i].idCliente, arrayAux[i].cantidad);
			if(arrayAux[i].cantidad > maxAvisos || i==0)
			{
				maxAvisos = arrayAux[i].cantidad;
				indiceMax = arrayAux[i].idCliente;
				strncpy(maxCuit, arrayAux[i].cuit,sizeof(maxCuit)-1);
			}
		}
		printf("El cliente con mas Avisos es el del ID %d con CUIT: %s con %d avisos\n\n", indiceMax, maxCuit,maxAvisos);
		retorno = 0;
	}
	return retorno;
}
/*
* \brief 	Devuelve como retorno la cantidad de avisos pausados recorriendo el struct de Avisos
* \param 	Avisos* pArray puntero al array recibida
* \param 	int length limite del array
* \return int Return (-1) Error / numero de avisos pausados Ok
 */
int info_calcularAvisosPausados(Avisos* pArray, int length)
{
	int retorno = -1;
	int cantAvisosPausados = 0;
	int i;
	if(pArray!= NULL && length > 0)
	{
		for(i=0; i < length; i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].estado == 0)
			{
				cantAvisosPausados++;
			}
		}
		retorno = cantAvisosPausados;
	}
	return retorno;
}
/*
* \brief 	Imprime el rubro con la cantidad de avisos que posee
* 			Imprime el rubro que tiene mas Avisos
* \param 	Avisos* pArray puntero al array recibida
* \param 	int length limite del array
* \param 	Cliente* pArrayCliente puntero al array recibida
* \param 	int lengthCliente limite del array
* \return int Return (-1) Error / (0) Ok
 */
int info_calcularMaxRubro(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente)
{
	int retorno = -1;
	Auxiliar arrayAux[lengthCliente];
	int i;
	int j;
	int flagExiste;
	int indiceCuitLibre = 0;
	int maxAvisos;
	int rubroMax;
	if(pArray != NULL && pArrayCliente != NULL && length > 0 && lengthCliente > 0)
	{
		aux_init(arrayAux, lengthCliente);
		for(i=0; i < lengthCliente; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				flagExiste = 0;
				for(j=0; j < indiceCuitLibre; j++)
				{
					if(arrayAux[j].isEmpty == FALSE && pArray[i].numeroRubro == arrayAux[j].rubros)
					{
						flagExiste = 1;
						break;
					}
				}
				if(flagExiste == 0)
				{
					arrayAux[indiceCuitLibre].rubros = pArray[i].numeroRubro;
					arrayAux[indiceCuitLibre].isEmpty = FALSE;
					indiceCuitLibre++;
				}
			}
		}
/*
		for(i=0; i< indiceCuitLibre;i++)
		{
			printf("rubros: %d\n", arrayAux[i].rubros);
		}
*/
		for(i = 0; i < indiceCuitLibre;i++)
		{
			if(arrayAux[i].isEmpty == FALSE)
			{
				for(j=0; j < length;j++)
				{
					if(pArray[j].isEmpty == FALSE && arrayAux[i].rubros == pArray[j].numeroRubro)
					{
						arrayAux[i].cantidad++;
					}
				}

			}
		}
		for(i=0; i< indiceCuitLibre;i++)
		{
			printf("El rubro: %s tiene %d avisos\n", TXT_RUBROS[arrayAux[i].rubros], arrayAux[i].cantidad);
			if(arrayAux[i].cantidad > maxAvisos || i==0)
			{
				maxAvisos = arrayAux[i].cantidad;
				rubroMax = arrayAux[i].rubros;
			}
		}
		printf("El rubro con mas Avisos es el de %s con %d avisos\n\n", TXT_RUBROS[rubroMax], maxAvisos);
		retorno = 0;
	}
	return retorno;
}



/*
 ============================================================================
 Author      : Nicolás Martín Vega Gangemi
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "avisos.h"
#include "informes.h"


int main(void) {
	setbuf(stdout, NULL);
	int opcion;
	int indiceById;
	int idSearch;
	int contadorClientes=4;
	int auxId;
	int auxContador;
	Cliente arrayClientes[QTY_CLIENTE];
	Avisos arrayAvisos[QTY_AVISOS];
	cliente_init(arrayClientes, QTY_CLIENTE);
	avisos_init(arrayAvisos, QTY_AVISOS);

	cliente_addForzada(arrayClientes, QTY_CLIENTE, "Juan", "Perez", "1111");
	cliente_addForzada(arrayClientes, QTY_CLIENTE, "Rosa", "Polz", "2222");
	cliente_addForzada(arrayClientes, QTY_CLIENTE, "Federico", "Cumbi", "3333");
	cliente_addForzada(arrayClientes, QTY_CLIENTE, "Azul", "Arrosi", "4444");
	avisos_addForzada(arrayAvisos, QTY_AVISOS, "Para desarrollar los músculos del cuerpo", 2, 3, 1);
	avisos_addForzada(arrayAvisos, QTY_AVISOS, "Lugar para poder comunicarse con los demás", 1, 4, 1);
	avisos_addForzada(arrayAvisos, QTY_AVISOS, "Sitio de instrucción para los adolescentes", 3, 7, 1);
	avisos_addForzada(arrayAvisos, QTY_AVISOS, "Comida para llevar de aca para alla con mucho glamour", 1, 2, 1);
	avisos_addForzada(arrayAvisos, QTY_AVISOS, "Transporte que brinda alimentos a los civiles", 3, 2, 1);
	//info_punto8_1(arrayAvisos, QTY_AVISOS, arrayClientes, QTY_CLIENTE);
	//info_aux(arrayAvisos, QTY_AVISOS, arrayClientes, QTY_CLIENTE);
	do
	{
		cliente_menuOptions();
		if(utn_getNumberInt("\n", "ERROR\n", &opcion, 3, 1, 11)==0)
		{
			switch(opcion)
			{
			case 1:
				if(cliente_createCliente(arrayClientes, QTY_CLIENTE)==0)
				{
					printf("Cliente cargado\n");
					contadorClientes++;
				}
				else
				{
					printf("No funca el createCliente\n");
				}
				break;
			case 2:
				if(contadorClientes > 0)
				{
					if(utn_getNumberInt("Id a modificar:\n", "ERRROR Ingrese un id válido\n", &idSearch, 3, 1, 100)==0)
					{
						indiceById = cliente_findById(arrayClientes, QTY_CLIENTE, idSearch);
						if(indiceById == -1)
						{
							printf("No existe el ID buscado para modificar\n");
						}
						else
						{
							if(cliente_modifyClienteAll(arrayClientes, QTY_CLIENTE, indiceById)==0)
							{
								printf("Cliente modificado\n");
							}
						}
					}
				}
				else
				{
					printf("Ingrese un cliente en opcion 1 \n");
				}
				break;
			case 3:
				if(contadorClientes > 0)
				{
					if(utn_getNumberInt("Id a buscar:\n", "ERRROR Ingrese un id válido\n", &idSearch, 3, 1, 100)==0)
					{
						//IdSearch es el idCLIENTE RELACIONARLO CON LOS AVISOS E IMPRIMIRLOS
						avisos_printByIdCliente(arrayAvisos, QTY_AVISOS, idSearch);
						//indiceByIdCliente = avisos_findByIdCliente(arrayAvisos, QTY_AVISOS, idSearch);
						indiceById = cliente_findById(arrayClientes, QTY_CLIENTE, idSearch);
						if(indiceById == -1)
						{
							printf("No existe el ID buscado para modificar\n");
						}
						else
						{
							/*
							 FALTA IMPRIMIR LOS AVISOS DE ESE CLIENTE
							 */
							if(utn_getNumberInt("Desea Confirmar la baja del cliente:\n"
												"1- Si\n"
												"2- No\n", "ERROR\n", &opcion, 3, 1, 2)==0)
							{
								if(opcion == 1)
								{
									if(	cliente_remove(arrayClientes, QTY_CLIENTE, indiceById)==0 &&
										avisos_removeByIdCliente(arrayAvisos, QTY_AVISOS, idSearch)==0)
									{
										printf("Cliente removido\n");
										contadorClientes--;
									}
								}
								else
								{
									printf("Se cancelo la baja del cliente\n");
								}
							}
						}
					}
				}
				else
				{
					printf("Ingrese un cliente en opcion 1 \n");
				}
				break;
			case 4:
				/*
				Permitirá crear un nuevo aviso. Se pedirán los siguientes datos: ID de cliente, número de rubro,
				texto del aviso (64 caracteres). Se generará automáticamente un identificador
				numérico para el aviso y se	imprimirá en pantalla.
				 */
				if(contadorClientes > 0)
				{
					if(avisos_createAvisos(arrayAvisos, QTY_AVISOS, arrayClientes, QTY_CLIENTE)==0)
					{
						printf("AVISO creado con exito\n");
						if(avisos_print(arrayAvisos, QTY_AVISOS)==0)
						{
							printf("--------------------\n");
						}
					}
					else
					{
						printf("No funco el create aviso\n");
					}
				}
				else
				{
					printf("Ingrese un cliente en opcion 1 \n");
				}
				break;
			case 5:
				/*
				 	Se pedirá el ID de la publicación y se imprimirá la información del cliente al que
					pertenece,
					luego se pedirá confirmación para cambiarse de estado y se cambiará al estado "pausada".
				 */
				if(contadorClientes > 0)
				{
					if(utn_getNumberInt("Ingrese el ID del aviso que quiere verificar:\n", "ERROR, ingrese un numero de id valido\n", &idSearch, 3, 1, 100)==0)
					{
						auxId = info_searchIdClienteByIdAviso(arrayAvisos, QTY_AVISOS, arrayClientes, QTY_CLIENTE, idSearch);
						if(auxId == -1)
						{
							printf("No se encontro el ID buscado en los avisos\n");
						}
						else
						{
							printf("vamos bien\n");
							if(info_printClienteById(arrayAvisos, QTY_AVISOS, arrayClientes, QTY_CLIENTE, auxId)==0)
							{
								printf("***********************\n\n");
								if(utn_getNumberInt("Desea pausar el AVISO\n1-SI\n2-NO\n", "ERROR, ingrese 1 o 2 según corresponda\n", &opcion, 3, 1, 2)==0)
								{
									if(opcion == 2)
									{
										printf("No se pauso NADA\n");
									}
									else
									{
										auxId = avisos_findById(arrayAvisos, QTY_AVISOS, idSearch);
										if(auxId != -1)
										{
											avisos_estadoPause(arrayAvisos, QTY_AVISOS, auxId);
											printf("Aviso pausado con exito\n");
										}
									}
								}
							}
						}
					}
				}
				else
				{
					printf("Ingrese un cliente en opcion 1 \n");
				}
				break;
			case 6:
				/*
				 Se pedirá el ID de la publicación y se imprimirá la información del cliente al que pertenece,
				 luego se pedirá confirmación para cambiarse de estado y se cambiará al estado "activa".
				 */
				if(contadorClientes > 0)
				{
					if(utn_getNumberInt("Ingrese el ID del aviso que quiere verificar:\n", "ERROR, ingrese un numero de id valido\n", &idSearch, 3, 1, 100)==0)
					{
						auxId = info_searchIdClienteByIdAviso(arrayAvisos, QTY_AVISOS, arrayClientes, QTY_CLIENTE, idSearch);
						if(auxId == -1)
						{
							printf("No se encontro el ID buscado en los avisos\n");
						}
						else
						{
							printf("vamos bien\n");
							if(info_printClienteById(arrayAvisos, QTY_AVISOS, arrayClientes, QTY_CLIENTE, auxId)==0)
							{
								printf("***********************\n\n");
								if(utn_getNumberInt("Desea activar el AVISO\n1-SI\n2-NO\n", "ERROR, ingrese 1 o 2 según corresponda\n", &opcion, 3, 1, 2)==0)
								{
									if(opcion == 2)
									{
										printf("No se ACTIVO NADA\n");
									}
									else
									{
										auxId = avisos_findById(arrayAvisos, QTY_AVISOS, idSearch);
										if(auxId != -1)
										{
											avisos_estadoActive(arrayAvisos, QTY_AVISOS, auxId);
											printf("Aviso ACTIVO con exito\n");
										}
									}
								}
							}
						}
					}
				}
				else
				{
					printf("Ingrese un cliente en opcion 1 \n");
				}
				break;
			case 7:
				if(contadorClientes > 0)
				{
					//if(cliente_print(arrayClientes, QTY_CLIENTE)==0)
					if(info_printClienteWithAvisos(arrayAvisos, QTY_AVISOS, arrayClientes, QTY_CLIENTE)==0)
					{
						printf("Clientes impresos\n");
					//	avisos_print(arrayAvisos, QTY_AVISOS);
					}
					else
					{
						printf("No funca el print clientes\n");
					}
				}
				else
				{
					printf("Ingrese un cliente en opcion 1 \n");
				}
				break;
			case 8:
				if(contadorClientes > 0)
				{
					do
					{
						if(utn_getNumberInt("Ingrese una opcion:\n"
											"1- Cliente con más avisos\n"
											"2- Cantidad de avisos pausados\n"
											"3- Rubro con más avisos\n"
											"4- SALIR\n", "Error, ingrese (1 - 4)\n", &opcion, 3, 1, 4)==0)
						{
							switch(opcion)
							{
							case 1:
								//info_aux(arrayAvisos, QTY_AVISOS, arrayClientes, QTY_CLIENTE);
								info_calcularMaxAvisosByCuit(arrayAvisos, QTY_AVISOS, arrayClientes, QTY_CLIENTE);
								break;
							case 2:
								auxContador = info_calcularAvisosPausados(arrayAvisos, QTY_AVISOS);
								printf("la cantidad de avisos pausados hasta el momento es de %d\n\n", auxContador);
								break;
							case 3:
								info_calcularMaxRubro(arrayAvisos, QTY_AVISOS, arrayClientes, QTY_CLIENTE);
								break;
							}
						}
					}while(opcion != 4);
				}
				else
				{
					printf("Ingrese un cliente en opcion 1 \n");
				}
				break;
			}
		}
		printf("***************************************************\n");
	}while(opcion != 9);
	return EXIT_SUCCESS;
}

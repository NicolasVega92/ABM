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

	cliente_addForzada(arrayClientes, QTY_CLIENTE, "Juan", "Perez", "11-11111111-1");
	cliente_addForzada(arrayClientes, QTY_CLIENTE, "Rosa", "Polz", "22-22222222-2");
	cliente_addForzada(arrayClientes, QTY_CLIENTE, "Federico", "Cumbi", "33-33333333-3");
	cliente_addForzada(arrayClientes, QTY_CLIENTE, "Azul", "Arrosi", "44-44444444-4");
	avisos_addForzada(arrayAvisos, QTY_AVISOS, "Para desarrollar los músculos del cuerpo", 2, 3, 1);
	avisos_addForzada(arrayAvisos, QTY_AVISOS, "Lugar para poder comunicarse con los demás", 1, 4, 1);
	avisos_addForzada(arrayAvisos, QTY_AVISOS, "Sitio de instrucción para los adolescentes", 3, 7, 1);
	avisos_addForzada(arrayAvisos, QTY_AVISOS, "Comida para llevar de aca para alla con mucho glamour", 1, 2, 0);
	avisos_addForzada(arrayAvisos, QTY_AVISOS, "Transporte que brinda alimentos a los civiles", 3, 2, 1);
	do
	{
		cliente_menuOptions();
		if(utn_getNumberInt("\n", "ERROR\n", &opcion, 3, 1, 11)==0)
		{
			switch(opcion)
			{
			case 1:
				if(cliente_create(arrayClientes, QTY_CLIENTE)==0)
				{
					printf("Cliente cargado\n");
					contadorClientes++;
				}
				else
				{
					printf("Error en createCliente\n");
				}
				break;
			case 2:
				if(contadorClientes > 0)
				{
					cliente_print(arrayClientes, QTY_CLIENTE);
					if(utn_getNumberInt("Id a modificar:\n", "ERRROR Ingrese un id válido (1 - 100)\n", &idSearch, 3, 1, 100)==0)
					{
						indiceById = cliente_findById(arrayClientes, QTY_CLIENTE, idSearch);
						if(indiceById == -1)
						{
							printf("No existe el ID buscado para modificar\n");
						}
						else
						{
							if(cliente_modifyAll(arrayClientes, QTY_CLIENTE, indiceById)==0)
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
					cliente_print(arrayClientes, QTY_CLIENTE);
					if(utn_getNumberInt("Id a buscar:\n", "ERRROR Ingrese un id válido (1 - 100)\n", &idSearch, 3, 1, 100)==0)
					{
						avisos_printByIdCliente(arrayAvisos, QTY_AVISOS, idSearch);
						indiceById = cliente_findById(arrayClientes, QTY_CLIENTE, idSearch);
						if(indiceById == -1)
						{
							printf("No existe el ID buscado para modificar\n");
						}
						else
						{
							if(utn_getNumberInt("Desea Confirmar la baja del cliente:\n"
												"1- Si\n"
												"2- No\n", "ERROR\n", &opcion, 3, 1, 2)==0)
							{
								if(opcion == 1)
								{
									if(	avisos_removeByIdCliente(arrayAvisos, QTY_AVISOS, idSearch)==0)
									{
										printf("Avisos del cliente removido\n");
										if(cliente_remove(arrayClientes, QTY_CLIENTE, indiceById)==0)
										{
											printf("Cliente removido\n");
											contadorClientes--;
										}
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
				if(contadorClientes > 0)
				{
					cliente_print(arrayClientes, QTY_CLIENTE);
					if(avisos_create(arrayAvisos, QTY_AVISOS, arrayClientes, QTY_CLIENTE)==0)
					{
						if(avisos_print(arrayAvisos, QTY_AVISOS)==0)
						{
							printf("\nAviso creado con exito\n");
						}
					}
					else
					{
						printf("Error en createAvisos\n");
					}
				}
				else
				{
					printf("Ingrese un cliente en opcion 1 \n");
				}
				break;
			case 5:
				if(contadorClientes > 0)
				{
					//avisos_print(arrayAvisos, QTY_AVISOS);
					if(avisos_printActivos(arrayAvisos, QTY_AVISOS)==0)
					{
						if(utn_getNumberInt("Ingrese el ID del aviso que quiere verificar:\n", "ERROR, ingrese un numero de id valido (1-100)\n", &idSearch, 3, 1, 100)==0)
						{
							auxId = avisos_searchIdClienteByIdAviso(arrayAvisos, QTY_AVISOS, idSearch);
							if(auxId == -1)
							{
								printf("No se encontro el ID buscado en los avisos\n");
							}
							else
							{
								if(cliente_printClienteById(arrayClientes, QTY_CLIENTE, auxId)==0)
								{
									if(utn_getNumberInt("Desea pausar el AVISO\n"
														"1-SI\n"
														"2-NO\n", "ERROR, ingrese 1 o 2 según corresponda\n", &opcion, 3, 1, 2)==0)
									{
										if(opcion == 2)
										{
											printf("No se PAUSO nada\n");
										}
										else
										{
											auxId = avisos_findById(arrayAvisos, QTY_AVISOS, idSearch);
											if(auxId != -1)
											{
												if(avisos_estadoPause(arrayAvisos, QTY_AVISOS, auxId)==0)
												{
													printf("Aviso PAUSADO con exito\n");
												}
											}
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
				if(contadorClientes > 0)
				{
					//avisos_print(arrayAvisos, QTY_AVISOS);
					if(avisos_printPausados(arrayAvisos, QTY_AVISOS)==0)
					{
						if(utn_getNumberInt("Ingrese el ID del aviso que quiere verificar:\n", "ERROR, ingrese un numero de id valido (1 - 100)\n", &idSearch, 3, 1, 100)==0)
						{
							auxId = avisos_searchIdClienteByIdAviso(arrayAvisos, QTY_AVISOS, idSearch);
							if(auxId == -1)
							{
								printf("No se encontro el ID buscado en los avisos\n");
							}
							else
							{
								if(cliente_printClienteById(arrayClientes, QTY_CLIENTE, auxId)==0)
								{
									if(utn_getNumberInt("Desea activar el AVISO\n1-SI\n2-NO\n", "ERROR, ingrese 1 o 2 según corresponda\n", &opcion, 3, 1, 2)==0)
									{
										if(opcion == 2)
										{
											printf("No se ACTIVO NADA\n");
										}
										else
										{
											auxId = avisos_findById(arrayAvisos, QTY_AVISOS, idSearch);
											if(auxId !=-1)
											{
												if(avisos_estadoActive(arrayAvisos, QTY_AVISOS, auxId)==0)
												{
													printf("Aviso ACTIVADO con exito\n");
												}
											}
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
					if(info_printClienteWithAvisos(arrayAvisos, QTY_AVISOS, arrayClientes, QTY_CLIENTE)==0)
					{
						printf("Clientes impresos\n");
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
						if(utn_getNumberInt("\nIngrese una opcion:\n"
											"1- Cliente con más avisos\n"
											"2- Cantidad de avisos pausados\n"
											"3- Rubro con más avisos\n"
											"4- SALIR\n", "Error, ingrese (1 - 4)\n", &opcion, 3, 1, 4)==0)
						{
							switch(opcion)
							{
							case 1:
								info_calcularMaxAvisosByCuit(arrayAvisos, QTY_AVISOS, arrayClientes, QTY_CLIENTE);
								break;
							case 2:
								auxContador = avisos_calcularAvisosPausados(arrayAvisos, QTY_AVISOS);
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
